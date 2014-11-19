#include "Scene.h"
#include <cstdlib>
#include <cstdio>

Scene::Scene(int type, float u){
	this->type = 0;
	this->step = u;
}

Scene::~Scene(){

}

void Scene::insertPatch(Patch& patch){
	this->patches.push_back(&patch);
}

void Scene::render(){
	// printf("Rendering start...\n");
	
	uniformSubdivide();
}

void Scene::uniformSubdivide(){
	int num_div = 1.0f / this->step;

	// if(isWire){
	// 	// printf("%s\n", "Hi	");
	// 	for(int pi = 0; pi < this->patches.size(); pi++){
	// 		for(int ui = 0; ui < num_div; ui++){
	// 			glBegin(GL_LINE_STRIP);

	// 			for(int vi = 0; vi < num_div; vi++){
	// 				float u = ui * this->step;
	// 				float v = vi * this->step;

	// 				std::pair<ControlPoint*, glm::vec3> patch_data = interpolatePatch(*this->patches[pi], u, v);
					
	// 				ControlPoint* p = patch_data.first;

	// 				glm::vec3 point_pos = p->getPosition();
					
	// 				glm::vec3 normal = patch_data.second;

	// 				// printf("Pos: (%f, %f, %f)\n", point_pos.x, point_pos.y, point_pos.z);

	// 				glVertex3f(point_pos.x, point_pos.y, point_pos.z);

	// 				free(p);
	// 			}

	// 			glEnd();


	// 			glBegin(GL_LINE_STRIP);

	// 			for(int vi = 0; vi < num_div; vi++){
	// 				float u = ui * this->step;
	// 				float v = vi * this->step;

	// 				std::pair<ControlPoint*, glm::vec3> patch_data = interpolatePatch(*this->patches[pi], v, u);
					
	// 				ControlPoint* p = patch_data.first;

	// 				glm::vec3 point_pos = p->getPosition();
					
	// 				glm::vec3 normal = patch_data.second;

	// 				// printf("Pos: (%f, %f, %f)\n", point_pos.x, point_pos.y, point_pos.z);

	// 				glVertex3f(point_pos.x, point_pos.y, point_pos.z);

	// 				free(p);
	// 			}

	// 			glEnd();
	// 		}
	// 	}	
	// } else if(isFlat){
	// 	for(int pi = 0; pi < this->patches.size(); pi++){
	// 		for(int ui = 0; ui < num_div - 1; ui++){
	// 			glBegin(GL_QUADS);

	// 			for(int vi = 0; vi < num_div - 1; vi++){
	// 				float u = ui * this->step;
	// 				float v = vi * this->step;

	// 				std::pair<ControlPoint*, glm::vec3> patch_data1 = interpolatePatch(*this->patches[pi], u, v);
	// 				std::pair<ControlPoint*, glm::vec3> patch_data2 = interpolatePatch(*this->patches[pi], u, v + 1);
	// 				std::pair<ControlPoint*, glm::vec3> patch_data3 = interpolatePatch(*this->patches[pi], u + 1, v);
	// 				std::pair<ControlPoint*, glm::vec3> patch_data4 = interpolatePatch(*this->patches[pi], u + 1, v + 1);

	// 				ControlPoint* p1 = patch_data1.first;
	// 				ControlPoint* p2 = patch_data2.first;
	// 				ControlPoint* p3 = patch_data3.first;
	// 				ControlPoint* p4 = patch_data4.first;

	// 				glm::vec3 point_pos1 = p1->getPosition();
	// 				glm::vec3 point_pos2 = p2->getPosition();
	// 				glm::vec3 point_pos3 = p3->getPosition();
	// 				glm::vec3 point_pos4 = p4->getPosition();

	// 				glm::vec3 normal1 = patch_data1.second;
	// 				glm::vec3 normal2 = patch_data2.second;
	// 				glm::vec3 normal3 = patch_data3.second;
	// 				glm::vec3 normal4 = patch_data4.second;

	// 				// printf("Pos: (%f, %f, %f)\n", point_pos.x, point_pos.y, point_pos.z);

	// 				glNormal3f(normal1.x, normal1.y, normal1.z);
	// 				glVertex3f(point_pos1.x, point_pos1.y, point_pos1.z);

	// 				glNormal3f(normal2.x, normal2.y, normal2.z);
	// 				glVertex3f(point_pos2.x, point_pos2.y, point_pos2.z);

	// 				glNormal3f(normal3.x, normal3.y, normal3.z);
	// 				glVertex3f(point_pos3.x, point_pos3.y, point_pos3.z);

	// 				glNormal3f(normal4.x, normal4.y, normal4.z);
	// 				glVertex3f(point_pos4.x, point_pos4.y, point_pos4.z);
	// 			}

	// 			glEnd();
	// 		}
	// 	}
	// } else if(!isFlat){

	// }
	
	for(int pi = 0; pi < this->patches.size(); pi++){
		for(int ui = 0; ui <= num_div; ui++){
			for(int vi = 0; vi <= num_div; vi++){
				float u = ui * this->step;
				float v = vi * this->step;

				std::pair<ControlPoint*, glm::vec3> patch_data = interpolatePatch(*this->patches[pi], u, v);
				
				ControlPoint* p = patch_data.first;

				glm::vec3 point_pos = p->getPosition();
				
				glm::vec3 normal = patch_data.second;

				// printf("Pos: (%f, %f, %f)\n", point_pos.x, point_pos.y, point_pos.z);

				// glVertex3f(point_pos.x, point_pos.y, point_pos.z);

				this->generated_pts.push_back(p);
				this->generated_normals.push_back(normal);
			}
		}
	}
}

void Scene::draw(bool isWire, bool isFlat){
	int num_div = 1.0f / this->step;

	if(isWire){
		for(int pi = 0; pi < this->patches.size(); pi++){
			for(int ui = 0; ui <= num_div; ui++){
				glBegin(GL_LINE_STRIP);

				for(int vi = 0; vi <= num_div; vi++){
					ControlPoint* p = this->generated_pts[pi*(num_div+1)*(num_div+1) + ui*(num_div+1) + vi];

					glm::vec3 point_pos = p->getPosition();

					// printf("Pos: (%f, %f, %f)\n", point_pos.x, point_pos.y, point_pos.z);

					glVertex3f(point_pos.x, point_pos.y, point_pos.z);
				}

				glEnd();

				glBegin(GL_LINE_STRIP);

				for(int vi = 0; vi <= num_div; vi++){
					ControlPoint* p = this->generated_pts[pi*(num_div+1)*(num_div+1) + vi*(num_div+1) + ui];

					glm::vec3 point_pos = p->getPosition();

					// printf("Pos: (%f, %f, %f)\n", point_pos.x, point_pos.y, point_pos.z);

					glVertex3f(point_pos.x, point_pos.y, point_pos.z);
				}

				glEnd();
			}
		}
	} else if(isFlat){
		for(int pi = 0; pi < this->patches.size(); pi++){
			for(int ui = 0; ui <= num_div - 1; ui++){
				glBegin(GL_QUADS);

				for(int vi = 0; vi <= num_div - 1; vi++){
					ControlPoint* p1 = this->generated_pts[pi*(num_div+1)*(num_div+1) + ui*(num_div+1) + vi];
					ControlPoint* p2 = this->generated_pts[pi*(num_div+1)*(num_div+1) + ui*(num_div+1) + (vi+1)];
					ControlPoint* p3 = this->generated_pts[pi*(num_div+1)*(num_div+1) + (ui+1)*(num_div+1) + vi];
					ControlPoint* p4 = this->generated_pts[pi*(num_div+1)*(num_div+1) + (ui+1)*(num_div+1) + (vi+1)];

					glm::vec3 point_pos1 = p1->getPosition();
					glm::vec3 point_pos2 = p2->getPosition();
					glm::vec3 point_pos3 = p3->getPosition();
					glm::vec3 point_pos4 = p4->getPosition();

					glm::vec3 normal1 = this->generated_normals[pi*(num_div+1)*(num_div+1) + ui*(num_div+1) + vi];
					glm::vec3 normal2 = this->generated_normals[pi*(num_div+1)*(num_div+1) + ui*(num_div+1) + (vi+1)];
					glm::vec3 normal3 = this->generated_normals[pi*(num_div+1)*(num_div+1) + (ui+1)*(num_div+1) + vi];
					glm::vec3 normal4 = this->generated_normals[pi*(num_div+1)*(num_div+1) + (ui+1)*(num_div+1) + (vi+1)];
					// printf("Pos: (%f, %f, %f)\n", point_pos.x, point_pos.y, point_pos.z);

					glNormal3f(normal1.x, normal1.y, normal1.z);
					glVertex3f(point_pos1.x, point_pos1.y, point_pos1.z);

					glNormal3f(normal2.x, normal2.y, normal2.z);
					glVertex3f(point_pos2.x, point_pos2.y, point_pos2.z);

					glNormal3f(normal3.x, normal3.y, normal3.z);
					glVertex3f(point_pos3.x, point_pos3.y, point_pos3.z);

					glNormal3f(normal4.x, normal4.y, normal4.z);
					glVertex3f(point_pos4.x, point_pos4.y, point_pos4.z);
				}

				glEnd();
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