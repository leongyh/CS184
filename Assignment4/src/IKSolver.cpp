#include "IKSolver.h"

IKSolver::IKSolver(){
	
};

IKSolver::~IKSolver(){

};

glm::vec3 IKSolver::solve(Arm& arm){
	Eigen::MatrixXf jacobian(3, 12);
	glm::vec3 e = arm.getEndPoint();
	std::vector<Joint*> joints = arm.getJoints();

	for(int i = 0; i < joints.size(); i++){
		glm::vec3 jpos = arm.getJointPos(i);
		glm::vec3 dofx = glm::cross(glm::vec3(1.0f, 0.0f, 0.0f), (e - jpos));
		glm::vec3 dofy = glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), (e - jpos));
		glm::vec3 dofz = glm::cross(glm::vec3(0.0f, 0.0f, 1.0f), (e - jpos));

		Eigen::Vector3f v1(dofx.x, dofx.y, dofx.z);
		Eigen::Vector3f v2(dofy.x, dofy.y, dofy.z);
		Eigen::Vector3f v3(dofz.x, dofz.y, dofz.z);
		
		jacobian.col(3*i+0) = v1;
		jacobian.col(3*i+1) = v2;
		jacobian.col(3*i+2) = v3;
	}

	// std::cout << jacobian << std::endl;

	Eigen::MatrixXf jacobian_inv = jacobian.transpose() * (jacobian * jacobian.transpose()).inverse();

	std::cout << jacobian_inv << std::endl;
	std::cout << "---------------" << std::endl;

	return e;
};