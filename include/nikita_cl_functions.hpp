#include <iostream>
#include "cl_tentacle/src/DataTypes.hpp"
#include "precomputation.hpp"
#include <eigen3/Eigen/Geometry>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/QR>
#include <eigen3/Eigen/Dense>
#include <math.h>
#include <cassert>
#include <vector>
#include <fstream>
#include <string>

#ifndef NIKITA_CL_FUNCTIONS_HPP
#define NIKITA_CL_FUNCTIONS_HPP

using namespace Eigen;
using namespace std;

// Funtion prototypes
MatrixXd compute_JSU(std::vector<PosOrientation> *iPosVec, std::vector<Joint> *iJoints, std::vector<Link> *iLinks, MatrixXd &U);
void DirectKinematics(std::vector<PosOrientation> &iPosVec, std::vector<Joint> &iJoints, std::vector<Link> &iLinks);
Matrix3d RotationZYX(Matrix3d src, Vector3d jointAngles);
MatrixXd EvaluateJacobian(std::vector<PosOrientation> &iPosVec);
MatrixXd MagWrench(std::vector<Joint> &iJoints, int jointEff, MatrixXd &U);
MatrixXd MagWrenchMap(Vector3d &Mag);


// === Function definitions ===
MatrixXd compute_JSU(std::vector<PosOrientation> &iPosVec, std::vector<Joint> &iJoints, std::vector<Link> &iLinks, MatrixXd &U){
    DirectKinematics(iPosVec, iJoints, iLinks);

    MatrixXd Jacobian = EvaluateJacobian(iPosVec);
    Jacobian = Jacobian.transpose().eval();

    int jointEff = (int) iJoints.size() - 1;

    // Compute wrench
    MatrixXd wrench = MagWrench(iJoints, jointEff, U);
    wrench = wrench.reshaped(jointEff*6, 1).eval();

    // compute JSU
    MatrixXd JSU;
    JSU = Jacobian * wrench;
    return JSU;
}

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
		
		iPosVec[i].z(Eigen::placeholders::all,0) = iJoints[i].Rotation * Vector3d::UnitX();
		
		iPosVec[i].z(Eigen::placeholders::all,1) = AngleAxisd( iJoints[i].q(0) * M_PI / 180, Vector3d::UnitX() ) *  
							iJoints[i].Rotation * Vector3d::UnitY();
		
		iPosVec[i].z(Eigen::placeholders::all,2) = AngleAxisd( iJoints[i].q(1) * M_PI / 180, Vector3d::UnitY() ) * 
							AngleAxisd( iJoints[i].q(0) * M_PI / 180, Vector3d::UnitX() ) * 
							iJoints[i].Rotation * Vector3d::UnitZ();	
	}
    return;
}

Matrix3d RotationZYX(Matrix3d src, Vector3d jointAngles){
	double AngleZ = jointAngles(2);
	double AngleY = jointAngles(1);
	double AngleX = jointAngles(0);
	
	return src * AngleAxisd(AngleZ, Vector3d::UnitZ())
		* AngleAxisd(AngleY, Vector3d::UnitY())
		* AngleAxisd(AngleX, Vector3d::UnitX());
}

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
                    std::vector<Vector3d> z1{iPosVec[k].z(Eigen::placeholders::all,0), iPosVec[k].z(Eigen::placeholders::all,1), iPosVec[k].z(Eigen::placeholders::all,2)};
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

MatrixXd MagWrench(std::vector<Joint> &iJoints, int jointEff, MatrixXd &U){
	
	Vector3d Mag;
	MatrixXd Wrench(6, jointEff);
	for(int i = 0; i < jointEff; i++){
		Mag = iJoints[i+1].Rotation * iJoints[i].LocMag;
        // cout << iJoints[i+1].Rotation << "\n";
		Wrench(Eigen::placeholders::all, i) = MagWrenchMap(Mag) * U;	
	}

	return Wrench;
}

MatrixXd MagWrenchMap(Vector3d &Mag){
	MatrixXd forceMap(3, 5);
	Matrix3d torqueMap;


	forceMap << Mag(0), Mag(1), Mag(2),    0   ,   0   ,
				   0  , Mag(0),   0   ,  Mag(1), Mag(2),
			   -Mag(2),    0  , Mag(0), -Mag(2), Mag(1); 

	torqueMap << 0, -Mag(2), Mag(1),
				Mag(2), 0, -Mag(0),
				-Mag(1), Mag(0), 0;

	MatrixXd S(6 ,8);
	S = MatrixXd::Zero(6,8);
	S(seq(0,2), seq(0,4)) = forceMap;
	S(seq(3,5), seq(5,7)) = torqueMap;
	return S; 	

}

#endif