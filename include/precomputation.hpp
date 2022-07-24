#include <iostream>
#include "cl_tentacle/src/DataTypes.hpp"

struct dfltValues{
    float len = 10e-3;
    float d = 2e-3;
    float E = 100e3;
    float v = 0.43;
};

MatrixXd StackDiagonals(std::vector<Matrix3d> matrices);
MatrixXd EvaluateK(std::vector<Link> &iLinks);


int main(int argc, char* argv[]);