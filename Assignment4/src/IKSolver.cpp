#include "IKSolver.h"

IKSolver::IKSolver(){
	
};

IKSolver::~IKSolver(){

};

void IKSolver::solve(Arm& arm, Goal& goal){
	// bool seen = false;
	bool done = false;
	int iter = 0;
	float max_length = arm.getMaxLength();
	Eigen::VectorXf dA(12);

	for (int i = 0; i < 1; i++){
		dA(i) = 0.0f;
	}

	while(!done){
		glm::vec3 e = arm.getEndPoint();
		glm::vec3 g = goal.getPosition();

		if(glm::length(g-e) <= 0.015) done = true;

		if(!done){
			if(glm::length(g) > max_length){
				g = max_length * glm::normalize(g);
			}

			Eigen::MatrixXf jacobian(3, 12);
		
			Eigen::Vector3f dP(g.x - e.x, g.y - e.y, g.z - e.z);
			dP = 0.05 * dP;
			std::vector<Joint*> joints = arm.getJoints();

			for(int i = 0; i < joints.size(); i++){
				glm::vec3 jpos = arm.getJointPos(i);
				glm::vec3 dofx = glm::cross(glm::vec3(1.0f, 0.0f, 0.0f), glm::normalize(e - jpos));
				glm::vec3 dofy = glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), glm::normalize(e - jpos));
				glm::vec3 dofz = glm::cross(glm::vec3(0.0f, 0.0f, 1.0f), glm::normalize(e - jpos));

				Eigen::Vector3f v1(dofx.x, dofx.y, dofx.z);
				Eigen::Vector3f v2(dofy.x, dofy.y, dofy.z);
				Eigen::Vector3f v3(dofz.x, dofz.y, dofz.z);
				
				jacobian.col(3*i+0) = v1;
				jacobian.col(3*i+1) = v2;
				jacobian.col(3*i+2) = v3;
			}

			dA = jacobian.jacobiSvd(Eigen::ComputeThinU | Eigen::ComputeThinV).solve(dP);

			// if(!seen) std::cout << "****************" << std::endl;
			// std::cout << dA.norm() << std::endl;
			// std::cout << "---------------" << std::endl;

			// if(dA.norm() > 0.0080){
			// 	dA = dA / 4.0f;
			// }

			arm.applyDeltaAngle(dA);
			// seen = true;
			iter += 1;

			if(iter > 250){
				return;
			}
		}
	}
};