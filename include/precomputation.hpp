#include <iostream>
#include "cl_tentacle/src/DataTypes.hpp"
#include <eigen3/Eigen/Geometry>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/QR>


struct dfltValues{
    float len = 10e-3;
    float d = 2e-3;
    float E = 100e3;
    float v = 0.43;
};

//Evaluation functions
MatrixXd EvaluateK(std::vector<Link> &iLinks);
void DirectKinematics(std::vector<PosOrientation> &iPosVec, std::vector<Joint> &iJoints, std::vector<Link> &iLinks);
MatrixXd EvaluateJacobian(std::vector<PosOrientation> &iPosVec);
Matrix3d SkewMagnetisation(std::vector<Joint> &iJoints);

//Utility functions
MatrixXd StackDiagonals(std::vector<Matrix3d> matrices);
Matrix3d RotationZYX(Matrix3d src, Vector3d jointAngles);



int main(int argc, char* argv[]);