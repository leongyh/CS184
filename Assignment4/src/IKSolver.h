#ifndef IK_SOLVER_H_
#define IK_SOLVER_H_

#include <glm/glm.hpp>
#include <Eigen/Dense>

#include <iostream>
#include <cstdlib>
#include <cstdio>

#include "Arm.h"
#include "Goal.h"

class IKSolver{

	public:
		IKSolver();
		virtual ~IKSolver(); 
		
		void solve(Arm& arm, Goal& goal);
		void hardSolve(Arm& arm, Goal& goal);
};

#endif