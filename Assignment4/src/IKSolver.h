#ifndef IK_SOLVER_H_
#define IK_SOLVER_H_

#include <glm/glm.hpp>
#include <Eigen/Dense>

#include <iostream>

#include "Arm.h"

class IKSolver{

	public:
		IKSolver();
		virtual ~IKSolver(); 
		
		glm::vec3 solve(Arm& arm);
};

#endif