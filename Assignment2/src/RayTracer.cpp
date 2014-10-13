#include "RayTracer.h"
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <vector>

RayTracer::RayTracer(){
	depth = 5;
}

RayTracer::RayTracer(int d){
	depth = d;
}

RayTracer::~RayTracer(){

}

Color* RayTracer::trace(Ray* cam_ray, std::vector<Sphere>& spheres){
	//find intersect on all geometries first
	Sphere* closest_sphere;
	float smallest_t = -1.0f;

	for(int i = 0; i < spheres.size(); i++){
		Sphere sphere = spheres[i];

		float t = sphere.intersect(cam_ray);

		if(t >= 0.0f){
			if(smallest_t < 0.0f){
				closest_sphere = &sphere;
				smallest_t = t;
			} else if(t < smallest_t){
				closest_sphere = &sphere;
				smallest_t = t;
			}
		}
	}

	//paint red for simple test
	if(smallest_t < 0.0f){
		return new Color(0.0f, 0.0f, 0.0f);
	} else{
		return new Color(1.0f, 0.0f, 0.0f);
	}
}

void RayTracer::print(){
	printf("The Ray Tracer has recursion depth %d", depth);
}