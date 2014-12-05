#include "Scene.h"
#include <cstdlib>
#include <cstdio>

Scene::Scene(int type, float u, bool adaptive){
	this->type = 0;
	this->step = u;
	this->isAdaptive = adaptive;
}

Scene::~Scene(){

}

void Scene::insertPatch(Patch& patch){
	this->patches.push_back(&patch);
}

void Scene::render(){
	// printf("Rendering start...\n");
	if(this->isAdaptive){
		adaptiveSubdivide();
	} else{
		uniformSubdivide();
	}
}

void Scene::uniformSubdivide(){
	int num_div = 1.0f / this->step;

	for(int pi = 0; pi < this->patches.size(); pi++){
		for(int ui = 0; ui <= num_div; ui++){
			for(int vi = 0; vi <= num_div; vi++){
				float u = ui * this->step;
				float v = vi * this->step;

				std::pair<ControlPoint*, glm::vec3> patch_data = interpolatePatch(*this->patches[pi], u, v);
				
				ControlPoint* p = patch_data.first;

				glm::vec3 point_pos = p->getPosition();
				
				glm::vec3 normal = patch_data.second;

				this->generated_pts.push_back(p);
				this->generated_normals.push_back(normal);
			}
		}
	}
}

void Scene::adaptiveSubdivide(){
	for(int pi = 0; pi < this->patches.size(); pi++){
		Patch* p = this->patches[pi];

		Curve* c1 = p->getDemCurves()[0];
		Curve* c2 = p->getDemCurves()[3];

		ControlPoint* point1 = c1->getPoints()[0];
		ControlPoint* point2 = c1->getPoints()[3];
		ControlPoint* point3 = c2->getPoints()[3];
		ControlPoint* point4 = c2->getPoints()[0];
	
		// //Triangle 1
		// subdivideTriangle(*p, *point1, 0.0f, 0.0f, *point3, 1.0f, 1.0f, *point2, 1.0f, 0.0f);

		// //Triangle 2
		// subdivideTriangle(*p, *point1, 0.0f, 0.0f, *point4, 0.0f, 1.0f, *point3, 1.0f, 1.0f);

		//Triangle 1
		subdivideTriangle(*p, *point1, 0.0f, 0.0f, *point2, 1.0f, 0.0f, *point4, 0.0f, 1.0f);

		//Triangle 2
		subdivideTriangle(*p, *point2, 1.0f, 0.0f, *point3, 1.0f, 1.0f, *point4, 0.0f, 1.0f);
	}	
}

void Scene::subdivideTriangle(Patch& patch, ControlPoint& p1, float u1, float v1, ControlPoint& p2, float u2, float v2, ControlPoint& p3, float u3, float v3){
	glm::vec3 e1 = (p1.getPosition() + p2.getPosition()) / 2.0f;
	float eu1 = (u1 + u2) / 2.0f;
	float ev1 = (v1 + v2) / 2.0f;

	glm::vec3 e2 = (p2.getPosition() + p3.getPosition()) / 2.0f;
	float eu2 = (u2 + u3) / 2.0f;
	float ev2 = (v2 + v3) / 2.0f;

	glm::vec3 e3 = (p1.getPosition() + p3.getPosition()) / 2.0f;
	float eu3 = (u1 + u3) / 2.0f;
	float ev3 = (v1 + v3) / 2.0f;

	//Edge 1
	ControlPoint* s1 = interpolatePatch(patch, eu1, ev1).first;
	float dist1 = glm::length(s1->getPosition() - e1);

	//Edge 2
	ControlPoint* s2 =interpolatePatch(patch, eu2, ev2).first;
	float dist2 = glm::length(s2->getPosition() - e2);

	//Edge 3
	ControlPoint* s3 = interpolatePatch(patch, eu3, ev3).first;
	float dist3 = glm::length(s3->getPosition() - e3);

	if(dist1 < this->step && dist2 < this->step && dist3 < this->step){
		this->generated_pts.push_back(&p1);
		this->generated_pts.push_back(&p2);
		this->generated_pts.push_back(&p3);

		glm::vec3 normal1 = interpolatePatch(patch, u1, v1).second;
		glm::vec3 normal2 = interpolatePatch(patch, u2, v2).second;
		glm::vec3 normal3 = interpolatePatch(patch, u3, v3).second;

		// printf("---------\nnormal1: %f %f %f\n", normal1.x, normal1.y, normal1.z);
		// printf("normal2: %f %f %f\n", normal2.x, normal2.y, normal2.z);
		// printf("normal2: %f %f %f\n", normal3.x, normal3.y, normal3.z);

		this->generated_normals.push_back(normal1);
		this->generated_normals.push_back(normal2);
		this->generated_normals.push_back(normal3);
	} else if(dist1 >= this->step && dist2 < this->step && dist3 < this->step){
		subdivideTriangle(patch, p1, u1, v1, *s1, eu1, ev1, p3, u3, v3);
		subdivideTriangle(patch, p3, u3, v3, *s1, eu1, ev1, p2, u2, v2);
	} else if(dist1 < this->step && dist2 >= this->step && dist3 < this->step){
		subdivideTriangle(patch, p1, u1, v1, *s2, eu2, ev2, p3, u3, v3);
		subdivideTriangle(patch, p1, u1, v1, p2, u2, v2, *s2, eu2, ev2);
	} else if(dist1 < this->step && dist2 < this->step && dist3 >= this->step){
		subdivideTriangle(patch, p1, u1, v1, p2, u2, v2, *s3, eu3, ev3);
		subdivideTriangle(patch, p2, u2, v2, p3, u3, v3, *s3, eu3, ev3);
	} else if(dist1 >= this->step && dist2 >= this->step && dist3 < this->step){
		subdivideTriangle(patch, p1, u1, v1, *s2, eu2, ev2, p3, u3, v3);
		subdivideTriangle(patch, p1, u1, v1, *s1, eu1, ev1, *s2, eu2, ev2);
		subdivideTriangle(patch, *s1, eu1, ev1, p2, u2, v2, *s2, eu2, ev2);
	} else if(dist1 < this->step && dist2 >= this->step && dist3 >= this->step){
		subdivideTriangle(patch, p1, u1, v1, p2, u2, v2, *s3, eu3, ev3);
		subdivideTriangle(patch, p2, u2, v2, *s2, eu2, ev2, *s3, eu3, ev3);
		subdivideTriangle(patch, *s2, eu2, ev2, p3, u3, v3, *s3, eu3, ev3);
	} else if(dist1 >= this->step && dist2 < this->step && dist3 >= this->step){
		subdivideTriangle(patch, p1, u1, v1, *s1, eu1, ev1, *s3, eu3, ev3);
		subdivideTriangle(patch, *s1, eu1, ev1, p3, u3, v3, *s3, eu3, ev3);
		subdivideTriangle(patch, *s1, eu1, ev1, p2, u2, v2, p3, u3, v3);
	} else if(dist1 >= this->step && dist2 >= this->step && dist3 >= this->step){
		subdivideTriangle(patch, p1, u1, v1, *s1, eu1, ev1, *s3, eu3, ev3);
		subdivideTriangle(patch, *s2, eu2, ev2, p3, u3, v3, *s3, eu3, ev3);
		subdivideTriangle(patch, *s1, eu1, ev1, p2, u2, v2, *s2, eu2, ev2);
		subdivideTriangle(patch, *s1, eu1, ev1, *s2, eu2, ev2, *s3, eu3, ev3);
	}
}

void Scene::draw(bool isWire, bool isFlat){
	if(this->isAdaptive){
		if(isWire){
			for(int i = 0; i < this->generated_pts.size(); i+=3){
				glShadeModel(GL_SMOOTH);

				glLineWidth(1.35f);
				glBegin(GL_LINE_LOOP);
				// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				// glBegin(GL_POLYGON);

				ControlPoint* p1 = this->generated_pts[i];
				ControlPoint* p2 = this->generated_pts[i+1];
				ControlPoint* p3 = this->generated_pts[i+2];

				glm::vec3 point_pos1 = p1->getPosition();
				glm::vec3 point_pos2 = p2->getPosition();
				glm::vec3 point_pos3 = p3->getPosition();
				// printf("Pos: (%f, %f, %f)\n", point_pos.x, point_pos.y, point_pos.z);

				glVertex3f(point_pos1.x, point_pos1.y, point_pos1.z);
				glVertex3f(point_pos2.x, point_pos2.y, point_pos2.z);
				glVertex3f(point_pos3.x, point_pos3.y, point_pos3.z);
				// glVertex3f(point_pos1.x, point_pos1.y, point_pos1.z);

				glEnd();
			}
		} else if(isFlat){
			for(int i = 0; i < this->generated_pts.size(); i+=3){
				glShadeModel(GL_FLAT);
				glBegin(GL_TRIANGLES);
				// glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				// glBegin(GL_POLYGON);

				ControlPoint* p1 = this->generated_pts[i];
				ControlPoint* p2 = this->generated_pts[i+1];
				ControlPoint* p3 = this->generated_pts[i+2];

				glm::vec3 point_pos1 = p1->getPosition();
				glm::vec3 point_pos2 = p2->getPosition();
				glm::vec3 point_pos3 = p3->getPosition();

				glm::vec3 face_normal = glm::normalize(glm::cross(point_pos3 - point_pos1, point_pos2 - point_pos1));// printf("Pos: (%f, %f, %f)\n", point_pos.x, point_pos.y, point_pos.z);

				glNormal3f(face_normal.x, face_normal.y, face_normal.z);

				glVertex3f(point_pos3.x, point_pos3.y, point_pos3.z);
				glVertex3f(point_pos2.x, point_pos2.y, point_pos2.z);
				glVertex3f(point_pos1.x, point_pos1.y, point_pos1.z);

				glEnd();
			}
		} else if(!isFlat){
			for(int i = 0; i < this->generated_pts.size(); i+=3){
				glShadeModel(GL_SMOOTH);
				// glBegin(GL_TRIANGLES);
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				glBegin(GL_POLYGON);

				ControlPoint* p1 = this->generated_pts[i];
				ControlPoint* p2 = this->generated_pts[i+1];
				ControlPoint* p3 = this->generated_pts[i+2];

				glm::vec3 point_pos1 = p1->getPosition();
				glm::vec3 point_pos2 = p2->getPosition();
				glm::vec3 point_pos3 = p3->getPosition();

				glm::vec3 normal1 = this->generated_normals[i];
				glm::vec3 normal2 = this->generated_normals[i+1];
				glm::vec3 normal3 = this->generated_normals[i+2];

				// printf("Pos: (%f, %f, %f)\n", point_pos.x, point_pos.y, point_pos.z);

				glNormal3f(normal1.x, normal1.y, normal1.z);
				glVertex3f(point_pos1.x, point_pos1.y, point_pos1.z);

				glNormal3f(normal2.x, normal2.y, normal2.z);
				glVertex3f(point_pos2.x, point_pos2.y, point_pos2.z);

				glNormal3f(normal3.x, normal3.y, normal3.z);
				glVertex3f(point_pos3.x, point_pos3.y, point_pos3.z);

				glEnd();
			}
		}
	} else{
		int num_div = 1.0f / this->step;

		if(isWire){
			for(int pi = 0; pi < this->patches.size(); pi++){
				for(int ui = 0; ui <= num_div; ui++){
					glShadeModel(GL_SMOOTH);

					glLineWidth(1.35f);
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
					glShadeModel(GL_FLAT);
					glBegin(GL_QUADS);

					for(int vi = 0; vi <= num_div - 1; vi++){
						ControlPoint* p1 = this->generated_pts[pi*(num_div+1)*(num_div+1) + ui*(num_div+1) + vi];
						ControlPoint* p2 = this->generated_pts[pi*(num_div+1)*(num_div+1) + (ui+1)*(num_div+1) + vi];
						ControlPoint* p3 = this->generated_pts[pi*(num_div+1)*(num_div+1) + (ui+1)*(num_div+1) + (vi+1)];
						ControlPoint* p4 = this->generated_pts[pi*(num_div+1)*(num_div+1) + ui*(num_div+1) + (vi+1)];

						glm::vec3 point_pos1 = p1->getPosition();
						glm::vec3 point_pos2 = p2->getPosition();
						glm::vec3 point_pos3 = p3->getPosition();
						glm::vec3 point_pos4 = p4->getPosition();

						glm::vec3 face_normal = glm::normalize(glm::cross(point_pos2 - point_pos1, point_pos4 - point_pos1));

						// printf("Pos: (%f, %f, %f)\n", point_pos.x, point_pos.y, point_pos.z);
						glNormal3f(face_normal.x, face_normal.y, face_normal.z);
						glVertex3f(point_pos1.x, point_pos1.y, point_pos1.z);
						glVertex3f(point_pos2.x, point_pos2.y, point_pos2.z);
						glVertex3f(point_pos3.x, point_pos3.y, point_pos3.z);
						glVertex3f(point_pos4.x, point_pos4.y, point_pos4.z);
					} 

					glEnd();
				}
			}
		} else if(!isFlat){
			for(int pi = 0; pi < this->patches.size(); pi++){
				for(int ui = 0; ui <= num_div - 1; ui++){
					glShadeModel(GL_SMOOTH);
					glBegin(GL_QUADS);

					for(int vi = 0; vi <= num_div - 1; vi++){
						ControlPoint* p1 = this->generated_pts[pi*(num_div+1)*(num_div+1) + ui*(num_div+1) + vi];
						ControlPoint* p2 = this->generated_pts[pi*(num_div+1)*(num_div+1) + (ui+1)*(num_div+1) + vi];
						ControlPoint* p3 = this->generated_pts[pi*(num_div+1)*(num_div+1) + (ui+1)*(num_div+1) + (vi+1)];
						ControlPoint* p4 = this->generated_pts[pi*(num_div+1)*(num_div+1) + ui*(num_div+1) + (vi+1)];

						glm::vec3 point_pos1 = p1->getPosition();
						glm::vec3 point_pos2 = p2->getPosition();
						glm::vec3 point_pos3 = p3->getPosition();
						glm::vec3 point_pos4 = p4->getPosition();

						glm::vec3 normal1 = this->generated_normals[pi*(num_div+1)*(num_div+1) + ui*(num_div+1) + vi];
						glm::vec3 normal2 = this->generated_normals[pi*(num_div+1)*(num_div+1) + (ui+1)*(num_div+1) + vi];
						glm::vec3 normal3 = this->generated_normals[pi*(num_div+1)*(num_div+1) + (ui+1)*(num_div+1) + (vi+1)];
						glm::vec3 normal4 = this->generated_normals[pi*(num_div+1)*(num_div+1) + ui*(num_div+1) + (vi+1)];
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

	Curve* tu_curve1 = p.getDemCurves()[0];
	Curve* tu_curve2 = p.getDemCurves()[1];
	Curve* tu_curve3 = p.getDemCurves()[2];
	Curve* tu_curve4 = p.getDemCurves()[3];

	Curve* tv_curve1 = new Curve(3);
	Curve* tv_curve2 = new Curve(3);
	Curve* tv_curve3 = new Curve(3);
	Curve* tv_curve4 = new Curve(3);

	tv_curve1->insertPoint(*(new ControlPoint(*tu_curve1->getPoints()[0])));
	tv_curve1->insertPoint(*(new ControlPoint(*tu_curve2->getPoints()[0])));
	tv_curve1->insertPoint(*(new ControlPoint(*tu_curve3->getPoints()[0])));
	tv_curve1->insertPoint(*(new ControlPoint(*tu_curve4->getPoints()[0])));

	tv_curve2->insertPoint(*(new ControlPoint(*tu_curve1->getPoints()[1])));
	tv_curve2->insertPoint(*(new ControlPoint(*tu_curve2->getPoints()[1])));
	tv_curve2->insertPoint(*(new ControlPoint(*tu_curve3->getPoints()[1])));
	tv_curve2->insertPoint(*(new ControlPoint(*tu_curve4->getPoints()[1])));

	tv_curve3->insertPoint(*(new ControlPoint(*tu_curve1->getPoints()[2])));
	tv_curve3->insertPoint(*(new ControlPoint(*tu_curve2->getPoints()[2])));
	tv_curve3->insertPoint(*(new ControlPoint(*tu_curve3->getPoints()[2])));
	tv_curve3->insertPoint(*(new ControlPoint(*tu_curve4->getPoints()[2])));

	tv_curve4->insertPoint(*(new ControlPoint(*tu_curve1->getPoints()[3])));
	tv_curve4->insertPoint(*(new ControlPoint(*tu_curve2->getPoints()[3])));
	tv_curve4->insertPoint(*(new ControlPoint(*tu_curve3->getPoints()[3])));
	tv_curve4->insertPoint(*(new ControlPoint(*tu_curve4->getPoints()[3])));

	vcurve->insertPoint(*interpolateCurve(*tu_curve1, u).first);
	vcurve->insertPoint(*interpolateCurve(*tu_curve2, u).first);
	vcurve->insertPoint(*interpolateCurve(*tu_curve3, u).first);
	vcurve->insertPoint(*interpolateCurve(*tu_curve4, u).first);

	ucurve->insertPoint(*interpolateCurve(*tv_curve1, v).first);
	ucurve->insertPoint(*interpolateCurve(*tv_curve2, v).first);
	ucurve->insertPoint(*interpolateCurve(*tv_curve3, v).first);
	ucurve->insertPoint(*interpolateCurve(*tv_curve4, v).first);

	std::pair<ControlPoint*, glm::vec3> vcurvedata;
	std::pair<ControlPoint*, glm::vec3> ucurvedata;

	vcurvedata = interpolateCurve(*vcurve, v);
	ucurvedata = interpolateCurve(*ucurve, u);

	ControlPoint* point = vcurvedata.first;
	glm::vec3 normal = glm::normalize(glm::cross(ucurvedata.second, vcurvedata.second));

	std::pair<ControlPoint*, glm::vec3> patchdata;

	patchdata.first = point;
	patchdata.second = normal;

	// if(isnan(normal.x)){
	// 	printf("---------\nnormal: %f %f %f\n", normal.x, normal.y, normal.z);
	// 	printf("ucurve derv: %f %f %f\n", ucurvedata.second.x, ucurvedata.second.y, ucurvedata.second.z);
	// 	// vcurve->print();
	// 	vcurvedata.first->print();
	// 	ucurvedata.first->print();
	// 	printf("vcurve derv: %f %f %f\n", vcurvedata.second.x, vcurvedata.second.y, vcurvedata.second.z);
	// 	printf("u: %f,  v: %f\n", u, v);
	// }
	
	return patchdata;
}

void Scene::print(){
	for(int i = 0; i < this->patches.size(); i++){
		printf("Patch #%d:\n", i);
		this->patches[i]->print();
	}

	printf("The Scene has %ld patches\n", this->patches.size());
}