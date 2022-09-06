#include <iostream>
#include "cl_tentacle/src/DataTypes.hpp"
#include "precomputation.hpp"
#include "nikita_utilities.hpp"
#include <eigen3/Eigen/Geometry>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/QR>
#include <eigen3/Eigen/Dense>
#include <math.h>
#include <cassert>
#include <vector>
#include <fstream>
#include <string>

#ifndef NIKITA_SETUP_HPP
#define NIKITA_SETUP_HPP

// Using
using namespace std;


// Function prototypes
MatrixXd get_Q_desired();
MatrixXd get_Q_initial(MatrixXd Q_desired);
MatrixXd compute_inertia(double diameter, unsigned int N);
MatrixXd StackDiagonals(vector<Matrix3d> matrices);
MatrixXd compute_stiffness(dfltValues props, unsigned int N);
MatrixXd compute_damping(MatrixXd I, MatrixXd K);
MatrixXd compute_A_matrix(MatrixXd I, MatrixXd C, MatrixXd K, unsigned int N);
MatrixXd read_optimisation_parameter(string fname);
std::vector<Vector3d> convert_to_vits_magnetisation(int jointEff, MatrixXd Mag);


/*** GLOBAL Constants ***/
MatrixXd get_Q_desired(){
    MatrixXd Q_desired(3, 4);
    Q_desired << 0, 0, 0, 0,
                -30, -17, -2, -35,
                0, 0, 0, 0;
    return Q_desired;
}
MatrixXd get_Q_initial(MatrixXd Q_desired){
    MatrixXd Q_initial(Q_desired.rows()+Q_desired.rows(), Q_desired.cols());
    Q_initial << Q_desired*0,
                Q_desired*0;
    return Q_initial;
}

/*** Function defintions ***/
MatrixXd compute_inertia(double diameter, unsigned int N){
    double Ib = M_PI / 4 * pow(diameter/2, 4);
    double It = M_PI / 2 * pow(diameter/2, 4);
    MatrixXd I = Matrix3d::Zero();
    I(0,0) = Ib;
    I(1,1) = Ib;
    I(2,2) = It;

    vector<Matrix3d> I_vec;
    for (int i=0; i < N; i++){
        I_vec.push_back(I);
    }
    return StackDiagonals(I_vec);
}

MatrixXd StackDiagonals(vector<Matrix3d> matrices){
	MatrixXd diagonal(matrices.size()*3, matrices.size()*3);
    diagonal = MatrixXd::Zero(diagonal.rows(), diagonal.cols());
	for(size_t i = 0; i < matrices.size(); i++){
		
		diagonal( seq(i*3, 2+i*3), seq(i*3, 2+i*3)) = matrices[i];
	
	}
	// std::cout << "Diagonal evaluated\n" << diagonal << "\n";
    return diagonal;
}

MatrixXd compute_stiffness(dfltValues props, unsigned int N){
    double Ib = M_PI / 4 * pow(props.d/2, 4);
    double It = M_PI / 2 * pow(props.d/2, 4);

    double G = props.E / (2 * (props.v + 1));
    double Kb = props.E * Ib / props.len;
    double Kt = G * It / props.len;

    MatrixXd K = Matrix3d::Zero();
    K(0,0) = Kb;
    K(1,1) = Kb;
    K(2,2) = Kt;
    
    vector<Matrix3d> K_vec;
    for (int i=0; i < N; i++){
        K_vec.push_back(K);
    }
    return StackDiagonals(K_vec);
}

MatrixXd compute_damping(MatrixXd I, MatrixXd K){
    MatrixXd prod = K.cwiseProduct(I);
    return 2 * prod.cwiseSqrt();
}

MatrixXd compute_A_matrix(MatrixXd I, MatrixXd C, MatrixXd K, unsigned int N){
    MatrixXd A_mat = MatrixXd::Zero(6*N, 6*N);
    A_mat(seq(0, 6*N/2 -1), seq(0, 6*N/2 -1)) = - C.cwiseProduct(I.cwiseInverse());                         // damping
    A_mat(seq(0, 6*N/2 -1), seq(6*N/2, Eigen::placeholders::last)) = - K.cwiseProduct(I.cwiseInverse());    // stiffness
    A_mat(seq(6*N/2, Eigen::placeholders::last), seq(0, 6*N/2 -1)) = MatrixXd::Identity(6*N/2, 6*N/2);;     // identity for theta_dot
    // replace NaNs with 0s
    A_mat = (A_mat.array().isFinite()).select(A_mat,0); 
    return A_mat;
}

MatrixXd compute_C_matrix(unsigned int N){
    MatrixXd C_mat = MatrixXd::Zero(3*N, 6*N);
    C_mat(Eigen::placeholders::all, seq(6*N/2, Eigen::placeholders::last)) = MatrixXd::Identity(3*N, 3*N); 
    return C_mat;
}

MatrixXd read_optimisation_parameter(string fname) {
    vector<vector<string>> content = read_file(fname);
    MatrixXd mat = MatrixXd::Zero(content.size(), content[0].size());

    for (int i=0; i<content.size(); i++) {
        for (int j=0; j<content[i].size(); j++)
        {
            // cout << content[i][j] << " ";
            double temp = ::atof(content[i][j].c_str()); // this converts from std::string to double
    
            mat(i, j) = temp;
        }
        // cout << "\n";
    }
    return mat;
}

// ==== Converting my variables to Vit's arhitecture ====

void convert_to_vits_field(){
    std::vector<Vector3d> AppliedFields;
}
// void convert_to_vits_desired_angles(int jointEff){
//     int jointNo = jointEff+1;
//     std::vector<int> DesiredAngles(jointNo);
//     // process my desired angles array into Vit's
//     DesiredAngles[0] = 10;
//     // DesiredAngles[1] = 20;
//     // DesiredAngles[2] = 30;
//     DesiredAngles[1] = 0;
//     // DesiredAngles[2] = 20;
//     // DesiredAngles[3] = 0;
//     // DesiredAngles[4] = 10;
// }
std::vector<Vector3d> convert_to_vits_magnetisation(int jointEff, MatrixXd Mag){
    int jointNo = jointEff+1;
    std::vector<Vector3d> Magnetisations(jointNo);
    for (int i=0; i < jointEff; i++){
        Magnetisations[i] = Mag(Eigen::placeholders::all, i);
    }
    Magnetisations[jointNo-1] = Vector3d(0,0,0);
    return Magnetisations;
}


#endif