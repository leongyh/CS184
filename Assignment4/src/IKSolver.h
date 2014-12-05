#ifndef IK_SOLVER_H_
#define IK_SOLVER_H_

#include <glm/glm.hpp>

class IKSolver{
	glm:: position;
	
	public:
		IKSolver(float x, float y, float z);
		IKSolver(const IKSolver& obj);
		virtual ~IKSolver(); 
		
		
		void print();
};

#endif