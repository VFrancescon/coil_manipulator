#include "precomputation.hpp"


int main(int argc, char* argv[]){
    
    int jointNo;

    //Sample number of max joints for development
    jointNo = 2;

    //timesteps are equal to joint no
    int timesteps = jointNo;  


    /* * * * * * * * * * * * * * * * * * * * * * * * *
     * PRECOMPUTATION FOR EACH TIMESTEP BEGINS HERE  *
     *                                               *
     *                                               *
     * * * * * * * * * * * * * * * * * * * * * * * * */
    std::vector<Vector3d> AppliedFields(jointNo);
    std::vector<int> DesiredAngles(jointNo);
    DesiredAngles[0] = 10;
    DesiredAngles[1] = 20;
    

    for(int k = jointNo; k-- > 0;){
        //setup position/orientation struct for later use
        std::vector<PosOrientation> iPosVec(jointNo);
        std::vector<Joint> iJoints(jointNo);
        //link joints position/orientation pointers to iPosVec's
        for(int i = 0; i < jointNo; i++){
            iJoints[i].assignPosOri(iPosVec[i]);
        }

        //create vector of links for properties
        std::vector<Link> iLinks(jointNo) ;
        dfltValues MechPpts;

        for(int i = 0; i < iLinks.size(); i++){
            iLinks[i].dL = MechPpts.len;
            iLinks[i].d = MechPpts.d;
            iLinks[i].E = MechPpts.E;
            iLinks[i].v = MechPpts.v;

        }

        //Evalaute K
        MatrixXd KStacked;
        KStacked = EvaluateK(iLinks);

        iJoints[0].q = Vector3d(0,10,0);
        iJoints[1].q = Vector3d(0,20,0);
        VectorXd AnglesStacked(iJoints.size()*3);
        AnglesStacked << iJoints[0].q, iJoints[1].q;


        DirectKinematics(iPosVec, iJoints, iLinks);
        MatrixXd Jacobian;
        Jacobian = EvaluateJacobian(iPosVec);
        
        Jacobian.transposeInPlace();
        MatrixXd JacobianINV(Jacobian.rows(), Jacobian.cols());
        JacobianINV = Jacobian.completeOrthogonalDecomposition().pseudoInverse();
        

        iJoints[0].LocMag = Vector3d(-0.0011, 0, -0.0028);
        iJoints[1].LocMag = Vector3d(0,0,-0.003);

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
        RHS = Jacobian * FieldMap;
        RHS_INV = RHS.completeOrthogonalDecomposition().pseudoInverse();
        Vector3d Field;
        Field = RHS_INV*KStacked*AnglesStacked;
        std::cout << "Applied Field requried:\n" << Field << "\n";
        AppliedFields.push_back(Field);

    }

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
 * @param jointNo number of joints (+1 from effective joint as we count end effector)
 */
void DirectKinematics(std::vector<PosOrientation> &iPosVec, std::vector<Joint> &iJoints, std::vector<Link> &iLinks){
	iJoints[0].Rotation = Matrix3d::Identity();
	iJoints[0].pLocal = Vector3d::Zero();

    int jointNo = (int) iJoints.size();

	for(int i = 1; i < jointNo; i++){
		iJoints[i].Rotation = RotationZYX(iJoints[i-1].Rotation, iJoints[i-1].q);
		iJoints[i].pLocal = iJoints[i-1].pLocal + iJoints[i].Rotation * Vector3d(0,0, -iLinks[i-1].dL);
	}
    
    for(int i = 0; i < jointNo; i++){
		
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
    
    int jointEff = (int) iPosVec.size();
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
				Vector3d pDiff = iPosVec[i+1].p - iPosVec[k].p;
				std::vector<Vector3d> z1{iPosVec[k].z(placeholders::all,0), iPosVec[k].z(placeholders::all,1), iPosVec[k].z(placeholders::all,2)};
				std::vector<Vector3d> ZcrossP{z1[0].cross(pDiff), z1[1].cross(pDiff), z1[2].cross(pDiff)};
				Jp << ZcrossP[0] , ZcrossP[1], ZcrossP[2];
				Jo << z1[0], z1[1], z1[2];	
			}
			MatrixXd Jn( Jp.rows() + Jo.rows(), Jp.cols());	
			Jn << Jp, 
				Jo;
			Jacobian(seq(0+i*6, 5+i*6), seq(0+k*3,2+k*3)) = Jn;
		}
	}
	return Jacobian;
}

MatrixXd MagtoFieldMap(std::vector<Joint> &iJoints){
    int jointNo = iJoints.size();
    MatrixXd Map;
    Map = VerticalStack(Matrix3d::Zero(), SkewMagnetisation(iJoints[0]));

    for(int i = 1; i < jointNo; i++){
        MatrixXd intermediateStack;
        intermediateStack = VerticalStack(Matrix3d::Zero(), SkewMagnetisation(iJoints[i]));
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
Matrix3d SkewMagnetisation(Joint J){
    Matrix3d skewed;
    Vector3d ProcMag;
    ProcMag = J.Rotation *  (-J.LocMag);
    skewed << 0, - ProcMag[2],  ProcMag[1],
             ProcMag[2], 0, - ProcMag[0],
            - ProcMag[1],  ProcMag[0], 0;
    return skewed;
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
	for(size_t i = 0; i < matrices.size(); i++){
		
		diagonal( seq(i*3, 2+i*3), seq(i*3, 2+i*3)) = matrices[i];
	
	}
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