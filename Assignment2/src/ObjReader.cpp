#include "ObjReader.h"
#include <cstdlib>
#include <cstdio>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
// #include <regex>

ObjReader::ObjReader(){
	is_transformed = false;
}

ObjReader::~ObjReader(){

}

//Sources viewed/used: http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/
//This reader doesn't use textures
void ObjReader::parse(const char* file_loc, int f_type){
	//read obj file first
	std::ifstream file;
	file.open(file_loc);
	std::string line;

	glm::vec3 ka;
	glm::vec3 kd;
	glm::vec3 ks;
	int sp = 1;
	glm::vec3 kr;

	Transform* trans = new Transform();
	bool is_transformed = false;

	while(std::getline(file, line)){
		std::stringstream l(line);
		char type[10];
		std::string vals;

		l >> type;
		std::getline(l, vals);

		if(strcmp(type, "v") == 0){
			glm::vec3 vert;
			sscanf(vals.c_str(), "%f %f %f\n", &vert.x, &vert.y, &vert.z);
			v.push_back(vert);
		} else if(strcmp(type, "vn") == 0){
			glm::vec3 norm;
			sscanf(vals.c_str(), "%f %f %f\n", &norm.x, &norm.y, &norm.z);
			vn.push_back(norm);
		} else if(strcmp(type, "vt") == 0){
			glm::vec2 tex;
			sscanf(vals.c_str(), "%f %f\n", &tex.x, &tex.y);
		} else if(strcmp(type, "f") == 0){
			unsigned int vert_ind[3], normal_ind[3];
			// printf("%d\n", f_type);
			if(f_type == 0){
				sscanf(vals.c_str(), "%d %d %d\n", &vert_ind[0], &vert_ind[1], &vert_ind[2]);

				v_index.push_back(vert_ind[0]);
				v_index.push_back(vert_ind[1]);
				v_index.push_back(vert_ind[2]);
			} else if(f_type == 1){
				sscanf(vals.c_str(), "%d//%d %d//%d %d//%d\n", &vert_ind[0], &normal_ind[0], &vert_ind[1], &normal_ind[1], &vert_ind[2], &normal_ind[2]);

				v_index.push_back(vert_ind[0]);
				v_index.push_back(vert_ind[1]);
				v_index.push_back(vert_ind[2]);
				vn_index.push_back(normal_ind[0]);
				vn_index.push_back(normal_ind[1]);
				vn_index.push_back(normal_ind[2]);
			}
		} else {
			printf("Unknown prefix '%s' in line: %s\n", type, line.c_str());
		}
	}
	
	file.close();
	
	// FILE* file = fopen(file_loc, "r");

	// if(file == NULL){
	// 	printf("Obj file at %s not found.\n", file_loc);
	// }
	
	// while(true){
	// 	char type[128];
		
	// 	int response = fscanf(file, "%s", type);
		
	// 	if(response == EOF){
	// 		// printf("%s\n", "EOF");
	// 		break;
	// 	}
		
	// 	if(strcmp(type, "v") == 0){
	// 		glm::vec3 vert;
	// 		fscanf(file, "%f %f %f\n", &vert.x, &vert.y, &vert.z);
	// 		v.push_back(vert);
	// 	} else if(strcmp(type, "vn") == 0){
	// 		glm::vec3 norm;
	// 		fscanf(file, "%f %f %f\n", &norm.x, &norm.y, &norm.z);
	// 		vn.push_back(norm);
	// 	} else if(strcmp(type, "vt") == 0){
	// 		glm::vec2 tex;
	// 		fscanf(file, "%f %f\n", &tex.x, &tex.y);
	// 	} else if(strcmp(type, "f") == 0){
	// 		unsigned int vert_ind[3], normal_ind[3];
	// 		// printf("%d\n", f_type);
	// 		if(f_type == 0){
	// 			fscanf(file, "%d %d %d\n", &vert_ind[0], &vert_ind[1], &vert_ind[2]);

	// 			v_index.push_back(vert_ind[0]);
	// 			v_index.push_back(vert_ind[1]);
	// 			v_index.push_back(vert_ind[2]);
	// 		} else if(f_type == 1){
	// 			fscanf(file, "%d//%d %d//%d %d//%d\n", &vert_ind[0], &normal_ind[0], &vert_ind[1], &normal_ind[1], &vert_ind[2], &normal_ind[2]);

	// 			v_index.push_back(vert_ind[0]);
	// 			v_index.push_back(vert_ind[1]);
	// 			v_index.push_back(vert_ind[2]);
	// 			vn_index.push_back(normal_ind[0]);
	// 			vn_index.push_back(normal_ind[1]);
	// 			vn_index.push_back(normal_ind[2]);
	// 		}
	// 	}
	// }
}

void ObjReader::createObj(Scene& scene, glm::vec3 ka, glm::vec3 kd, glm::vec3 ks, int sp, glm::vec3 kr){
	//handle adding triangles to scene
	// printf("%lu\n", v_index.size());
	if(v_index.size() == vn_index.size()){
		//do barycentric interpolation
		for(int i = 0; i < v_index.size(); i+=3){
			unsigned int i1 = v_index[i];
			unsigned int i2 = v_index[i+1];
			unsigned int i3 = v_index[i+2];
			// printf("%d %d %d\n", i1, i2, i3);
			glm::vec3 v1 = v[i1 - 1];
			glm::vec3 v2 = v[i2 - 1];
			glm::vec3 v3 = v[i3 - 1];
			
			Triangle* tri = new Triangle(v1, v2, v3);
			tri->setAmbient(ka);
			tri->setDiffuse(kd);
			tri->setSpecular(ks);
			tri->setSpecularPow(sp);
			tri->setReflect(kr);

			if(is_transformed){
				tri->setTransform(trans);
			}

			scene.insertTriangle(tri);
		}
	} else if (v_index.size() != 0 && vn_index.size() == 0){
		//do flat shading
		for(int i = 0; i < v_index.size(); i+=3){
			unsigned int i1 = v_index[i];
			unsigned int i2 = v_index[i+1];
			unsigned int i3 = v_index[i+2];
			// printf("%d %d %d\n", i1, i2, i3);
			glm::vec3 v1 = v[i1 - 1];
			glm::vec3 v2 = v[i2 - 1];
			glm::vec3 v3 = v[i3 - 1];
			
			Triangle* tri = new Triangle(v1, v2, v3);
			tri->setAmbient(ka);
			tri->setDiffuse(kd);
			tri->setSpecular(ks);
			tri->setSpecularPow(sp);
			tri->setReflect(kr);

			if(is_transformed){
				tri->setTransform(trans);
			}

			scene.insertTriangle(tri);
		}
	}
}

void ObjReader::setTransform(glm::mat4 mat){
	trans = mat;
	is_transformed = true;
}

void ObjReader::reset(){
	v.clear();
	vn.clear();
	v_index.clear();
	vn_index.clear();

	trans = glm::mat4(1.0f);
	is_transformed = false;
}