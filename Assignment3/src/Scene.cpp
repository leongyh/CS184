#include "Scene.h"
#include <cstdlib>
#include <cstdio>

Scene::Scene(float u){
	this->step = u;
}

Scene::~Scene(){

}

void Scene::insertDirectionalLight(DirectionalLight& dl){
	this->dir_lights.push_back(&dl);
}

void Scene::insertPointLight(PointLight& pl){
	this->pnt_lights.push_back(&pl);
}

void Scene::insertPatch(Patch& patch){
	this->patches.push_back(&patch);
}

void Scene::render(){
	printf("Rendering start...\n");
	
}

void Scene::uniformSubdivide(){
	int num_div = 1.0f / this->step;

	for(int pi = 0; pi < this->patches.size(); pi++){
		for(int ui = 0; ui < num_div; ui++){
			for(int vi = 0; vi < num_div; vi++){
				float u = ui * this->step;
				float v = vi * this->step;

				interpolatePatch(*this->patches[pi], u, v);
			}
		}
	}
}

std::pair<ControlPoint*, glm::vec3> Scene::interpolateCurve(Curve& c, float u){
	glm::vec3 A = c.getPoints()[0]->getPosition() * (1.0f - u) + c.getPoints()[1]->getPosition() * u;
	glm::vec3 B = c.getPoints()[1]->getPosition() * (1.0f - u) + c.getPoints()[2]->getPosition() * u;
	glm::vec3 C = c.getPoints()[2]->getPosition() * (1.0f - u) + c.getPoints()[3]->getPosition() * u;

	glm::vec3 D = A * (1.0f - u) + B * u;
	glm::vec3 E = B * (1.0f - u) + C * u;

	std::pair<ControlPoint*, glm::vec3> curvedata;

	curvedata.first = new ControlPoint(D * (1.0f - u) + E * u);
	curvedata.second = 3.0f * (E - D);

	return curvedata;
}

std::pair<ControlPoint*, glm::vec3> Scene::interpolatePatch(Patch& p, float u, float v){
	Curve* vcurve = new Curve(3);
	Curve* ucurve = new Curve(3);

	Curve* curve1 = p.getDemCurves()[0];
	Curve* curve2 = p.getDemCurves()[1];
	Curve* curve3 = p.getDemCurves()[2];
	Curve* curve4 = p.getDemCurves()[3];

	vcurve->insertPoint(*interpolateCurve(*curve1, u).first);
	vcurve->insertPoint(*interpolateCurve(*curve2, u).first);
	vcurve->insertPoint(*interpolateCurve(*curve3, u).first);
	vcurve->insertPoint(*interpolateCurve(*curve4, u).first);

	ucurve->insertPoint(*interpolateCurve(*curve1, v).first);
	ucurve->insertPoint(*interpolateCurve(*curve2, v).first);
	ucurve->insertPoint(*interpolateCurve(*curve3, v).first);
	ucurve->insertPoint(*interpolateCurve(*curve4, v).first);

	std::pair<ControlPoint*, glm::vec3> vcurvedata;
	std::pair<ControlPoint*, glm::vec3> ucurvedata;

	vcurvedata = interpolateCurve(*vcurve, v);
	ucurvedata = interpolateCurve(*ucurve, u);

	ControlPoint* point = vcurvedata.first;
	glm::vec3 normal = glm::normalize(glm::cross(ucurvedata.second, vcurvedata.second));

	std::pair<ControlPoint*, glm::vec3> patchdata;

	patchdata.first = point;
	patchdata.second = normal;

	return patchdata;
}

void Scene::print(){
	for(int i = 0; i < this->patches.size(); i++){
		printf("Patch #%d:\n", i);
		this->patches[i]->print();
	}

	printf("The Scene has %ld patches\n", this->patches.size());
}