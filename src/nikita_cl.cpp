#include <ctime>
#include <chrono>
#include <time.h>
#include <thread>
#include <functional>
#include <nikita_setup.hpp>
#include <nikita_cl_functions.hpp>
#include <segmentation.hpp>
#include <string>
#include <vector>
// Include MATLAB caller
#include <MatlabEngine.hpp>
#include <MatlabDataArray.hpp>

// Embedded coder
#include "dynamic_lungs_embed.h"       // Model header file
#include "rt_logging.h"

using Eigen::MatrixXd;

// Function prototypes
void timer_start(std::function<void(void)> func, unsigned int interval);
void control_loop();

const clock_t tStart = clock();
auto start = std::chrono::steady_clock::now();


/*** Fixed time step actuation ***/
bool ACTUATE_AT_FIXED_TIME_STEPS = false;
double time_step_in_ns = 100;

/*** Variables ***/
dfltValues MechPpts;
MatrixXd Q_desired = get_Q_desired();   // desired_Q
// get N and M from desired_Q
unsigned int M = Q_desired.rows();
unsigned int N = Q_desired.cols();

/*** Control variables ***/
MatrixXd I = compute_inertia(MechPpts.d, N);  // inertia matrix
MatrixXd K = compute_stiffness(MechPpts, N);  // stiffness matrix
double zeta = 1.0;                            // damping coefficient
MatrixXd C = compute_damping(I, K) * zeta;    // damping matrix
MatrixXd A_mat = compute_A_matrix(I, C, K, N);// A matrix
MatrixXd C_mat = compute_C_matrix(N);

/*** Optimisation parameters ***/
MatrixXd U = read_optimisation_parameter("/home/stormlab/Nikita/coil_manipulator/pete_optim/opt_u.csv");
MatrixXd Mag = read_optimisation_parameter("/home/stormlab/Nikita/coil_manipulator/pete_optim/opt_mag.csv");
MatrixXd qres = read_optimisation_parameter("/home/stormlab/Nikita/coil_manipulator/pete_optim/opt_qres.csv");

// void callMatlabSegmentation(){
//     // Start MATLAB engine synchronously
//     std::unique_ptr<MATLABEngine> matlabPtr = startMATLAB();

//     //Create MATLAB data array factory
//     matlab::data::ArrayFactory factory;

// 	// Define a typed array
// 	// matlab::data::TypedArray<double> const val = factory.createArray({1,1}, {5.0});
// 	// matlab::data::TypedArray<double> const argArray = 
//     //     factory.createArray({ 1,4 }, { -2.0, 2.0, 6.0, 8.0 });
// 	matlab::data::Array val = factory.createArray({2,2}, {1,1,1,1});

// 	// Call MATLAB custom function
//     matlab::data::Array const results = matlabPtr->feval(u"custom_func", val);
// 	// double t = results[0];
// 	// auto tmp = results[0][0 ];
// 	// ArrayType c = results.getType();
// 	// std::cout << c << "\n";

//     // Display results
//     // for (int i = 0; i < results.getNumberOfElements(); i++) {
//     //     double a = argArray[i];
//     //     std::complex<double> v = results[i];

// 	// 	auto v = results[i];
// 	// 	cout << v << "\n";
//     //     double realPart = v.real();
//     //     double imgPart = v.imag();
//     //     std::cout << "Value of " << a << " is now " << 
//     //         realPart << " + " << imgPart << "i" << std::endl;
//     // }
// }

// ========= Start MATLAB engine synchronously =========
std::unique_ptr<matlab::engine::MATLABEngine> matlabPtr = matlab::engine::startMATLAB();

//Create MATLAB data array factory
matlab::data::ArrayFactory factory;
matlab::data::Array P0 = factory.createArray({1,2}, {530.5337, 940.5933});

int main()
{
	matlab::data::Array norm_image = factory.createArray({ 1,4 }, { -2.0, 2.0, 6.0, 8.0 });
	// ========= Set the camera up =========
	Pylon::PylonInitialize();

	const int cFramesPerSecond = 20;
	const uint32_t cQuality = 90;
	Pylon::CInstantCamera camera(Pylon::CTlFactory::GetInstance().CreateFirstDevice() );
	std::cout << "Camera Model: " << camera.GetDeviceInfo().GetModelName() << " was created.\n";

	camera.Open();
	Pylon::CIntegerParameter width( camera.GetNodeMap() , "Width");
	Pylon::CIntegerParameter height( camera.GetNodeMap() , "Height" );
	Pylon::CIntegerParameter scale_factor( camera.GetNodeMap() , "BslScalingFactor" );
	Pylon::CEnumParameter pixelFormat(camera.GetNodeMap(), "PixelFormat");

	cv::Size frameSize = Size((int)width.GetValue(), (int)height.GetValue());
	int codec = cv::VideoWriter::fourcc('M', 'J', 'P', 'G');

	// width.TrySetValue(5000 , Pylon::IntegerValueCorrection_Nearest);
	// height.TrySetValue(5000, Pylon::IntegerValueCorrection_Nearest);
	width.TrySetToMaximum();
	height.TrySetToMaximum();

	Pylon::CPixelTypeMapper pixelTypeMapper( &pixelFormat);
	Pylon::EPixelType pixelType = pixelTypeMapper.GetPylonPixelTypeFromNodeValue(pixelFormat.GetIntValue());

	camera.StartGrabbing(Pylon::GrabStrategy_LatestImageOnly);
	cv::namedWindow("Display Window", WINDOW_NORMAL);
	cv::resizeWindow("Display Window", 500, 500);
	for (int i = 0; i < 10000; i++){
		std::cout << "Retrieving image #" << i << "\n";
		cv::Mat opencvImage = get_current_frame(camera);
		if (!opencvImage.empty()){
			matlab::data::Array norm_img = normalise_RGB_image(opencvImage, factory);
			matlab::data::Array const results = matlabPtr->feval(u"Segmentation", {norm_img, P0});
			auto res = results.getDimensions();
			cout << results.getNumberOfElements() << "\n";
			// cout << "Trying to print results.\n";
			// cout << (long uint) res[0] << "\n";
			// imshow("Display Window", opencvImage);
		}
		// Press ESC to quit the programm
		char k = cv::waitKey(15000);
		if (k == 27) {
			break;
		}
	}
	Pylon::PylonTerminate();

	// callSQRT();
	// callMatlabSegmentation();
//   return 0;






	// static dynamic_lungs_embed rtObj;      // Instance of model class
	// Initialize model
	// rtObj.initialize();

	// convert degrees to radians
	Q_desired = Q_desired * M_PI / 180;
	// reshape desired into columb vector and get initial Q
	MatrixXd Q_desired_column = Q_desired.reshaped(M*N, 1).eval();
	MatrixXd Q_initial = get_Q_initial(Q_desired_column);   // initial_Q

	// two versions of qres
	MatrixXd qres_column = qres;
	qres = qres.reshaped(3, N).eval();

	// convert my variables into Vit's architecture
	int jointNo = N + 1;
	std::vector<PosOrientation> iPosVec(N+1);
	std::vector<Vector3d> magnetisations = convert_to_vits_magnetisation(N, Mag);
	std::vector<Joint> iJoints(jointNo);
	// link joints position/orientation pointers to iPosVec's
	for(int i = 0; i < jointNo; i++){
	iJoints[i].assignPosOri(iPosVec[i]);
	}
	// create vector of links for properties
	std::vector<Link> iLinks(N) ;
	for(int i = 0; i < iLinks.size(); i++){
	iLinks[i].dL = MechPpts.len;
	iLinks[i].d = MechPpts.d;
	iLinks[i].E = MechPpts.E;
	iLinks[i].v = MechPpts.v;
	}
	for(int i = 0; i < jointNo; i++){
	if (i == jointNo - 1){
		iJoints[i].q = Vector3d(0,0,0);
	} else {
		iJoints[i].q = qres(Eigen::placeholders::all, i);
	
	iJoints[i].LocMag = magnetisations[i];
	}
	}


	// std::cout << Q_desired << std::endl;
	// std::cout << std::endl;
	// std::cout << Q_initial << std::endl;
	// std::cout << std::endl;
	// std::cout << M << N << std::endl;
	// std::cout << std::endl;

	if (ACTUATE_AT_FIXED_TIME_STEPS) {
	// TODO: develop below
	// Actuate at fixed frequency
	timer_start(control_loop, time_step_in_ns);
	// Infitite loop needed for timed iteration via threading
	while (true);
	} else {
	// MatrixXd JSU = compute_JSU(iPosVec, iJoints, iLinks, U);
	// cout << K*qres_column - JSU << "\n";

	// Actuate whenever next time step is computed
	// while (true) {
	//   break;
	// }
	}
	return 0;
}

void timer_start(std::function<void(void)> func, unsigned int interval){
	std::thread([func, interval]()
	{ 
	while (true)
	{ 
		auto x = std::chrono::steady_clock::now() + std::chrono::milliseconds(interval);
		func();
		std::this_thread::sleep_until(x);
	}
	}).detach();
}


void open_loop(int t_end){
	// dxdt_n0 = Q_initial * A + Bu
	cout << "open loop";
}


void control_loop()
{
	auto end = std::chrono::steady_clock::now();
	std::cout << "I am doing something" << std::endl;
	auto diff = end - start;
	std::this_thread::sleep_for(std::chrono::milliseconds(1100));
	std::cout << std::chrono::duration <double, std::milli> (diff).count() << " ms" << std::endl;
}
