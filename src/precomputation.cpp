#include "precomputation.hpp"


int main(int argc, char* argv[]){
    
    int jointNo;
    /**
     * @todo 
     * 
     *Precomputation checklist

    Equation:
        KQ = J^T * S * B

    //TODAY (24/07/22)
        1. take care of calculating K
        2. Take a Q input
        3. Calculate J (and J^T) 

    //MONDAY (25/07/22)
        1. Figure out how to stack S 
        2. Use all that to precalculate B at each timestep

    */

    //Sample number of max joints for development
    jointNo = 4;

    //timesteps are equal to joint no
    int timesteps = jointNo;  

    //create vector of links for properties
    std::vector<Link> iLinks(jointNo) ;
    dfltValues MechPpts;
    for(auto i: iLinks){
        i.dL = MechPpts.len;
        i.d = MechPpts.d;
        i.E = MechPpts.E;
        i.v = MechPpts.v;
    }

    //Evalaute K
    MatrixXd StackedK;
    StackedK = EvaluateK(iLinks);


    std::vector<Joint> iJoints(jointNo);
    



    return 0;
}

/**
 * @brief Evaluates the stiffness Matrix o
 * 
 * @param iLinks Vector of Link structs containing all Link mechanical properties
 * @return MatrixXd Diagonally Stacked 3.n x 3.n stiffness matrix
 */
MatrixXd EvaluateK(std::vector<Link> &iLinks){
	std::vector<Matrix3d> K_vec;

    for(auto i:iLinks){
		double lRadius = i.d / 2;
		double I = M_PI_4 * lRadius * lRadius * lRadius * lRadius;
		double G = i.E / (2* (i.v + 1) );
		double J = M_PI_2 * lRadius * lRadius * lRadius * lRadius;
		double Kb = i.E*I/i.dL;
		double Kt = G*J/i.dL;
		Matrix3d K = Matrix3d::Zero();
		K(0,0) = Kb;
		K(1,1) = Kb;
		K(2,2) = Kt;
		K_vec.push_back(K);
	}
	
	MatrixXd KDiagonal;
	KDiagonal = StackDiagonals(K_vec);
    return KDiagonal;
}


/**
 * @brief Creates a diagonal matrix by stacking 3x3 matrices contained in vector matrices
 * 
 * @param matrices vector containing n 3x3 matrices
 * @return MatrixXd - 3*n, 3*n Matrix containing the diagonal stack
 */
MatrixXd StackDiagonals(std::vector<Matrix3d> matrices){
	MatrixXd diagonal(matrices.size()*3, matrices.size()*3);
	for(size_t i = 0; i < matrices.size(); i++){
		
		diagonal( seq(i*3, 2+i*3), seq(i*3, 2+i*3)) = matrices[i];
	
	}
	return diagonal;
}