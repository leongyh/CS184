#include "RayTracer.h"
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <cmath>

RayTracer::RayTracer(){
	depth = 5;
}

RayTracer::RayTracer(int d){
	depth = d;
}

RayTracer::~RayTracer(){

}

Color RayTracer::trace(const Ray& cam_ray, std::vector<Sphere> spheres){
	//find intersect on all geometries first
	Sphere* closest_sphere;
	float smallest_t = -1.0f;

	for(int i = 0; i < spheres.length(); i++){
		Sphere sphere = spheres.get(i);

		float t = spheres.intersect(cam_ray);

		if(t >= 0){
			if(smallest_t < 0){
				closest_sphere = &sphere;
				smallest_t = t;
			} else if(t < smallest_t){
				closest_sphere = &sphere;
				smallest_t = t;
			}
		}
	}

	//paint red for simple test
	if(closest_sphere == NULL){
		return new Color(1.0f, 1.0f, 1.0f);
	} else{
		return new Color(1.0f, 0.0f, 0.0f);
	}
}



void RayTracer::print(){
	printf("The Ray Tracer has recursion depth %d", depth);
}