#include "IKSolver.h"

IKSolver::IKSolver(){
	
};

IKSolver::~IKSolver(){

};

void IKSolver::hardSolve(Arm& arm, Goal& goal){
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

		if(glm::length(g) > max_length){
			g = max_length * glm::normalize(g);
		}

		if(glm::length(g-e) <= 0.01) done = true;

		if(!done){
			Eigen::MatrixXf jacobian(3, 12);
		
			Eigen::Vector3f dP(g.x - e.x, g.y - e.y, g.z - e.z);
			dP = 0.05 * dP;
			std::vector<Joint*> joints = arm.getJoints();

			//analytical method
			// for(int i = 0; i < joints.size(); i++){
			// 	glm::vec3 jpos = arm.getJointPos(i);
			// 	// glm::vec3 dofx = glm::cross(glm::vec3(1.0f, 0.0f, 0.0f), glm::normalize(e - jpos));
			// 	// glm::vec3 dofy = glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), glm::normalize(e - jpos));
			// 	// glm::vec3 dofz = glm::cross(glm::vec3(0.0f, 0.0f, 1.0f), glm::normalize(e - jpos));
			// 	glm::vec3 dofx = glm::cross(glm::vec3(1.0f, 0.0f, 0.0f), (e - jpos));
			// 	glm::vec3 dofy = glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), (e - jpos));
			// 	glm::vec3 dofz = glm::cross(glm::vec3(0.0f, 0.0f, 1.0f), (e - jpos));

			// 	Eigen::Vector3f v1(dofx.x, dofx.y, dofx.z);
			// 	Eigen::Vector3f v2(dofy.x, dofy.y, dofy.z);
			// 	Eigen::Vector3f v3(dofz.x, dofz.y, dofz.z);
				
			// 	jacobian.col(3*i+0) = v1;
			// 	jacobian.col(3*i+1) = v2;
			// 	jacobian.col(3*i+2) = v3;
			// }

			//numerical method
			for(int i = 0; i < joints.size(); i++){
				glm::vec3 dofx = arm.simX(i);
				glm::vec3 dofy = arm.simY(i);
				glm::vec3 dofz = arm.simZ(i);

				Eigen::Vector3f v1(dofx.x, dofx.y, dofx.z);
				Eigen::Vector3f v2(dofy.x, dofy.y, dofy.z);
				Eigen::Vector3f v3(dofz.x, dofz.y, dofz.z);
				
				jacobian.col(3*i+0) = v1;
				jacobian.col(3*i+1) = v2;
				jacobian.col(3*i+2) = v3;
			}

			dA = jacobian.jacobiSvd(Eigen::ComputeThinU | Eigen::ComputeThinV).solve(dP);

			arm.applyDeltaAngle(dA);
		}
	}
}

void IKSolver::solve(Arm& arm, Goal& goal){
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

		if(glm::length(g) > max_length){
			g = max_length * glm::normalize(g);
		}

		if(glm::length(g-e) <= 0.015) done = true;

		if(!done){
			Eigen::MatrixXf jacobian(3, 12);
		
			Eigen::Vector3f dP(g.x - e.x, g.y - e.y, g.z - e.z);
			dP = 0.1 * dP;
			std::vector<Joint*> joints = arm.getJoints();

			//analytical method
			// for(int i = 0; i < joints.size(); i++){
			// 	glm::vec3 jpos = arm.getJointPos(i);
			// 	// glm::vec3 dofx = glm::cross(glm::vec3(1.0f, 0.0f, 0.0f), glm::normalize(e - jpos));
			// 	// glm::vec3 dofy = glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), glm::normalize(e - jpos));
			// 	// glm::vec3 dofz = glm::cross(glm::vec3(0.0f, 0.0f, 1.0f), glm::normalize(e - jpos));
			// 	glm::vec3 dofx = glm::cross(glm::vec3(1.0f, 0.0f, 0.0f), (e - jpos));
			// 	glm::vec3 dofy = glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), (e - jpos));
			// 	glm::vec3 dofz = glm::cross(glm::vec3(0.0f, 0.0f, 1.0f), (e - jpos));

			// 	Eigen::Vector3f v1(dofx.x, dofx.y, dofx.z);
			// 	Eigen::Vector3f v2(dofy.x, dofy.y, dofy.z);
			// 	Eigen::Vector3f v3(dofz.x, dofz.y, dofz.z);
				
			// 	jacobian.col(3*i+0) = v1;
			// 	jacobian.col(3*i+1) = v2;
			// 	jacobian.col(3*i+2) = v3;
			// }

			//numerical method
			for(int i = 0; i < joints.size(); i++){
				glm::vec3 dofx = arm.simX(i);
				glm::vec3 dofy = arm.simY(i);
				glm::vec3 dofz = arm.simZ(i);

				Eigen::Vector3f v1(dofx.x, dofx.y, dofx.z);
				Eigen::Vector3f v2(dofy.x, dofy.y, dofy.z);
				Eigen::Vector3f v3(dofz.x, dofz.y, dofz.z);
				
				jacobian.col(3*i+0) = v1;
				jacobian.col(3*i+1) = v2;
				jacobian.col(3*i+2) = v3;
			}

			dA = jacobian.jacobiSvd(Eigen::ComputeThinU | Eigen::ComputeThinV).solve(dP);

			arm.applyDeltaAngle(dA);
			iter += 1;

			if(iter > 400){
				return;
			}
		}
	}
};