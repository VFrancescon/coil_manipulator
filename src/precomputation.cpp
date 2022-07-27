#include "precomputation.hpp"


#define DIVIDER std::cout << "--------------------------\n"

int main(int argc, char* argv[]){

    int jointEff = 2;
    int jointNo = jointEff+1;
    //Sample number of max joints for development
    // int jointEff = 2;

    //timesteps are equal to joint no
    int timesteps = jointEff;  


    /* * * * * * * * * * * * * * * * * * * * * * * * *
     * PRECOMPUTATION FOR EACH TIMESTEP BEGINS HERE  *
     *                                               *
     *                                               *
     * * * * * * * * * * * * * * * * * * * * * * * * */
    std::vector<Vector3d> AppliedFields;

    std::vector<int> DesiredAngles(jointNo);
    DesiredAngles[0] = -10;
    DesiredAngles[1] = -20;
    // DesiredAngles[2] = 30;
    DesiredAngles[2] = 0;
    // DesiredAngles[2] = 20;
    // DesiredAngles[3] = 0;
    // DesiredAngles[4] = 10;


    std::vector<Vector3d> Magnetisations(jointNo);
    // Magnetisations[0] = Vector3d(0, 0, 0.003);
    // Magnetisations[1] = Vector3d(-0.003,0,0);
    // Magnetisations[2] = Vector3d(-0.003,0,0);
    // Magnetisations[3] = Vector3d(-0.0021,0,-0.0021);
    // Magnetisations[4] = Vector3d(0,0,-0.003);
    // Magnetisations[0] = Vector3d(-0.003,0,0);
    Magnetisations[0] = Vector3d(-0.0021,0,-0.0021);
    Magnetisations[1] = Vector3d(0,0,-0.003);
    Magnetisations[2] = Vector3d(0,0,0);

    std::vector<PosOrientation> iPosVec(jointNo);
    std::vector<Joint> iJoints(jointNo);
    //link joints position/orientation pointers to iPosVec's
    for(int i = 0; i < jointNo; i++){
        iJoints[i].assignPosOri(iPosVec[i]);
    }

    //create vector of links for properties
    std::vector<Link> iLinks(jointEff) ;
    dfltValues MechPpts;

    for(int i = 0; i < iLinks.size(); i++){
        iLinks[i].dL = MechPpts.len;
        iLinks[i].d = MechPpts.d;
        iLinks[i].E = MechPpts.E;
        iLinks[i].v = MechPpts.v;

    }

    for(int i = 0; i < jointNo; i++){
        iJoints[i].q = Vector3d(0,DesiredAngles[i],0);
        iJoints[i].LocMag = Magnetisations[i];
    }



    // for(int k = jointEff; k >= 1 ; --k){
        // DIVIDER;
        // std::cout << k << "\n";
        //setup position/orientation struct for later use
     
        VectorXd AnglesStacked;
        AnglesStacked = StackAngles(iJoints);
        // std::cout << "Angles Stacked:\n" << AnglesStacked << "\n";


        //Evalaute K
        MatrixXd KStacked;
        KStacked = EvaluateK(iLinks);
        

        DirectKinematics(iPosVec, iJoints, iLinks);
        MatrixXd Jacobian;
        Jacobian = EvaluateJacobian(iPosVec);
        
        Jacobian.transposeInPlace();
        MatrixXd JacobianINV(Jacobian.rows(), Jacobian.cols());
        JacobianINV = Jacobian.completeOrthogonalDecomposition().pseudoInverse();
        // std::cout << "Jacobian\n" << Jacobian.transpose() << "\n";

        MatrixXd FieldMap;
        FieldMap = MagtoFieldMap(iJoints);
        MatrixXd FieldMapINV;
        FieldMapINV = FieldMap.completeOrthogonalDecomposition().pseudoInverse();
        
        //Rationale for operations below. Assume A+ is the pseudo inverse of A

        // Given A+B+ = (AB)+
        // and given KQ = JSB
        // We have J+S+KQ = b
        // Therefore we call A = JS
        // And above Becomes A+.K.Q = B
        // We call A = RHS
        MatrixXd RHS, RHS_INV;
        std::cout << "Sizes of matrices:\n";
        DIVIDER;
        std::cout << "Size of jacobian: " << Jacobian.rows() << "x" <<Jacobian.cols() << "\n";
        std::cout << "Size of FieldMap: " << FieldMap.rows() << "x" <<FieldMap.cols() << "\n";
        std::cout << "Size of Kstacked: " << KStacked.rows() << "x" <<KStacked.cols() << "\n";
        std::cout << "Size of AnglesStacked: " << AnglesStacked.rows() << "x" <<AnglesStacked.cols() << "\n";
        DIVIDER;
        RHS = Jacobian * FieldMap;
        RHS_INV = RHS.completeOrthogonalDecomposition().pseudoInverse();
        Vector3d Field;
        Field = RHS_INV*KStacked*AnglesStacked;

        // DIVIDER;
        // // std::cout << "RHS_INV\n" << RHS_INV << "\n";

        // std::cout << "S(m)\n" << FieldMap << "\n";
        // std::cout << "JTinv =\n" << JacobianINV << "\n";

        // DIVIDER;

        // std::cout << "K* Q\n" << KStacked*AnglesStacked << "\n";
        // std::cout << "KStacked\n" << KStacked << "\n";
        // std::cout << "AnglesStacked\n" << AnglesStacked << "\n";
        // DIVIDER;

        std::cout << "Desired Joint angles:\n" << AnglesStacked << "\n";
        std::cout << "Applied Field requried (mT):\n" << Field*1000 << "\n";
        AppliedFields.push_back(Field*1000);
        // DIVIDER;
        // std::cout << "Angles:\n" << AnglesStacked << "\n";
        // std::cout << "Calculated field\n" << Field*1000 << "\n";
        // for(auto i: iPosVec) std::cout << "\n" << i.p << "\n";
        // for(auto i: iJoints) std::cout << "\n" << i.pLocal << "\n";

        // DIVIDER;
        // std::cout << "Before popping, sizes are:\n";
        // std::cout << "Angles: " <<DesiredAngles.size() << "\n";
        // std::cout << "Magnetisations: " << Magnetisations.size() << "\n";
        // std::cout << "Joints: " << iJoints.size() << "\n";
        // std::cout << "Links: " <<iLinks.size() << "\n";



        // DesiredAngles.pop_back();
        // Magnetisations.pop_back();
        // pop_front(iJoints);
        // pop_front(iPosVec);
        // pop_front(iLinks);
    // }
    
    
    /*ABOVE IS THE DECREASING FOR LOOP BRACE*/



    // DIVIDER;
    // std::reverse(AppliedFields.begin(), AppliedFields.end());
    // std::cout << "Size of fields " << AppliedFields.size() <<" fields in order\n";
    // for(auto i: AppliedFields){std::cout << i << "\n"; DIVIDER;}
    

    return 0;
}

/**
 * @brief Precomputation Function. Evaluates the stiffness Matrix of the system given the links
 * 
 * @param iLinks Vector of Link structs containing all Link mechanical properties
 * @return MatrixXd Diagonally Stacked 3.n x 3.n stiffness matrix
 */
MatrixXd EvaluateK(std::vector<Link> &iLinks){
	std::vector<Matrix3d> K_vec;

    for(int i = 0; i < iLinks.size(); i++){
		double lRadius = iLinks[i].d / 2;
		double I = M_PI_4 * lRadius * lRadius * lRadius * lRadius;
		double G = iLinks[i].E / (2* (iLinks[i].v + 1) );
		double J = M_PI_2 * lRadius * lRadius * lRadius * lRadius;
		double Kb = iLinks[i].E*I/iLinks[i].dL;
		double Kt = G*J/iLinks[i].dL;
		Matrix3d K = Matrix3d::Zero();
		K(0,0) = Kb;
		K(1,1) = Kb;
		K(2,2) = Kt;
		K_vec.push_back(K);
        // std::cout << "I " << i << "\nK\n" << K << "\n";
	}
	
	MatrixXd KDiagonal;
	KDiagonal = StackDiagonals(K_vec);
    return KDiagonal;
}


/**
 * @brief Precomputation Function. Precalculates axis unit vectors and positional vectors for Jacobian computation
 * 
 * @param iPosVec vector containing joint positions and axis orientation
 * @param iJoints vector containing the joint's Transform matrix and pointers to iPosVec
 * @param iLinks vector containing the links and their mechanical properties
 */
void DirectKinematics(std::vector<PosOrientation> &iPosVec, std::vector<Joint> &iJoints, std::vector<Link> &iLinks){
	iJoints[0].Rotation = Matrix3d::Identity();
	iJoints[0].pLocal = Vector3d::Zero();

    int jointEff = (int) iJoints.size();

	for(int i = 1; i < jointEff; i++){
		iJoints[i].Rotation = RotationZYX(iJoints[i-1].Rotation, iJoints[i-1].q);
		iJoints[i].pLocal = iJoints[i-1].pLocal + iJoints[i].Rotation * Vector3d(0,0, -iLinks[i-1].dL);
	}
    

    for(int i = 0; i < jointEff; i++){
		
		iPosVec[i].p = iJoints[i].pLocal;
		
		iPosVec[i].z(placeholders::all,0) = iJoints[i].Rotation * Vector3d::UnitX();
		
		iPosVec[i].z(placeholders::all,1) = AngleAxisd( iJoints[i].q(0) * M_PI / 180, Vector3d::UnitX() ) *  
							iJoints[i].Rotation * Vector3d::UnitY();
		
		iPosVec[i].z(placeholders::all,2) = AngleAxisd( iJoints[i].q(1) * M_PI / 180, Vector3d::UnitY() ) * 
							AngleAxisd( iJoints[i].q(0) * M_PI / 180, Vector3d::UnitX() ) * 
							iJoints[i].Rotation * Vector3d::UnitZ();	
	}
    return;
}

/**
 * @brief Precomputation Function. Evaluates the jacobian using orientations and positions containing in a vector of points
 * 
 * @param iPosVec vector contains Positions and Orientations
 * @param jointEff Number of effective joints (discount end effector basically)
 * @return MatrixXd size (joint)*6 x (jointEff)*3 containing the full Jacobian computed
 */
MatrixXd EvaluateJacobian(std::vector<PosOrientation> &iPosVec){
	/**
	 * @note
	 * 
	 * Given J = [ 	J00 J01
	 * 				J10 J11 	]
	 * Where J_xy = [Jp_xy
	 * 				Jo_xy]
	 * 
	 * In the loops below, 	i tracks y
	 * 						k tracks x
	 * 
	 * Also the 'stacking' of the full jacobian is actually done by 
	 * initialising an empty Mat of the correct size and filling in the blocks
	 * stacking in the Matrix algebra library we use is possible, but
	 * a pain, so filling is good enough, probably.
	 */
    
    int jointEff = (int) iPosVec.size() -1;
	Matrix3d Jp, Jo;
	MatrixXd Jacobian(jointEff*6, jointEff*3);
	for(int i = 0; i < jointEff; i++){
		//i goes vertically
		for(int k = 0; k < jointEff; k++){
			//k goes horizontally
			if( k > i ) {
				Jp = Matrix3d::Zero();
				Jo = Matrix3d::Zero();
			} else{
                try{
                    Vector3d pDiff = iPosVec[i+1].p - iPosVec[k].p;
                    std::vector<Vector3d> z1{iPosVec[k].z(placeholders::all,0), iPosVec[k].z(placeholders::all,1), iPosVec[k].z(placeholders::all,2)};
                    std::vector<Vector3d> ZcrossP{z1[0].cross(pDiff), z1[1].cross(pDiff), z1[2].cross(pDiff)};
                    Jp << ZcrossP[0] , ZcrossP[1], ZcrossP[2];
                    Jo << z1[0], z1[1], z1[2];	}
                catch(std::exception &e){
                    std::cout << "caught error at e: " << e.what() << "\n";
                    throw;
                }
			}
			MatrixXd Jn( Jp.rows() + Jo.rows(), Jp.cols());	
			Jn << Jp, 
				Jo;
			Jacobian(seq(0+i*6, 5+i*6), seq(0+k*3,2+k*3)) = Jn;
		}
	}
	return Jacobian;
}

/**
 * @brief Precomputation function. Calculates a Vertically stacked Map from Magnetisation to Field
 * 
 * @param iJoints ordered vector of joints, each containing the set magnetisation
 * @return MatrixXd 6*n x 3 matrix of vertically stacked 0(3x3) and maps. See Llyod 2020 and Salmanipour/Diller 2018
 */
MatrixXd MagtoFieldMap(std::vector<Joint> &iJoints){
    int jointEff = iJoints.size() - 1;
    MatrixXd Map;
    Map = VerticalStack(Matrix3d::Zero(), SkewMagnetisation(iJoints, 0));

    for(int i = 1; i < jointEff; i++){
        MatrixXd intermediateStack;
        intermediateStack = VerticalStack(Matrix3d::Zero(), SkewMagnetisation(iJoints, i));
        Map = VerticalStack(Map, intermediateStack);
    }  
    

    return Map;
}

/**
 * @brief Utility Function. Builds a skew matrix of a magnetised joint. This function acts on local magnetisation. Technically works on all skews.
 * 
 * @param j struct for a given joint, holding magnetisation. 
 * @return Matrix3d Skew matrix built of 3d magnetisations
 */
Matrix3d SkewMagnetisation(std::vector<Joint> &iJoints, int index){
    Matrix3d skewed;
    Vector3d ProcMag;
    ProcMag = iJoints[index+1].Rotation *  (iJoints[index].LocMag);
    skewed << 0, - ProcMag[2],  ProcMag[1],
             ProcMag[2], 0, - ProcMag[0],
            - ProcMag[1],  ProcMag[0], 0;
    return skewed;
}

VectorXd StackAngles(std::vector<Joint>& iJoints){
    int jointEff = iJoints.size();
    VectorXd stacked;

    if(jointEff == 1){
        stacked = iJoints[0].q;
    }
    else{
        stacked = VerticalStack(iJoints[0].q, iJoints[1].q);
        for(int i = 2; i < jointEff-1; i++){
            stacked = VerticalStack(stacked, iJoints[i].q);
        }
    }
    return stacked;
}



/**
 * @brief Utility Function. Vertically Stacks a 3x3 Matrix onto an existing Xx3 Matrix
 * 
 * @param M1 Matrix of any number of rows, but 3 columns
 * @param M2 3x3 Matrix to stack below
 * @return MatrixXd resultatant of stack
 */
MatrixXd VerticalStack(MatrixXd M1, MatrixXd M2){
    MatrixXd Stack(M1.rows() + M2.rows(), M1.cols());
    Stack << M1, M2;
    return Stack;
}


/**
 * @brief Utility Function. Creates a diagonal matrix by stacking 3x3 matrices contained in vector matrices
 * 
 * @param matrices vector containing n 3x3 matrices
 * @return MatrixXd - 3*n, 3*n Matrix containing the diagonal stack
 */
MatrixXd StackDiagonals(std::vector<Matrix3d> matrices){
	MatrixXd diagonal(matrices.size()*3, matrices.size()*3);
    diagonal = MatrixXd::Zero(diagonal.rows(), diagonal.cols());
	for(size_t i = 0; i < matrices.size(); i++){
		
		diagonal( seq(i*3, 2+i*3), seq(i*3, 2+i*3)) = matrices[i];
	
	}
	// std::cout << "Diagonal evaluated\n" << diagonal << "\n";
    return diagonal;
}


/**
 * @brief Utility Function. Rotates matrix src by angles in vector jointAngles in the ZYX order.
 * 
 * @param src matrix containing original position
 * @param jointAngles column vector containing rotations. (X,Y,Z) 
 * @return Matrix3d, Rotated matrix after being multiplied by angles jointAngles 
 */
Matrix3d RotationZYX(Matrix3d src, Vector3d jointAngles){
	double AngleZ = jointAngles(2) * M_PI / 180;
	double AngleY = jointAngles(1) * M_PI / 180;
	double AngleX = jointAngles(0) * M_PI / 180;
	
	return src * AngleAxisd(AngleZ, Vector3d::UnitZ())
		* AngleAxisd(AngleY, Vector3d::UnitY())
		* AngleAxisd(AngleX, Vector3d::UnitX());
}