#ifndef JACOBIAN_H_
#define JACOBIAN_H_

#include <glm/glm.hpp>

class Jacobian{
	float* matrix;
	
	public:
		Jacobian(int dim);
		Jacobian(const Jacobian& obj);
		virtual ~Jacobian(); 
		
		void 

		void print();
};

#endif