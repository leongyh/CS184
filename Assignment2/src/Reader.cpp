#include "Reader.h"
#include <cstdlib>
#include <cstdio>
#include <stdio.h>
#include <string.h>
#include <sstream>

Reader::Reader(const char* file_loc, const char* num){
	pugi::xml_document doc;
	doc.load_file(file_loc);

	root = doc.document_element();
	test_num = num;
}

Reader::~Reader(){

}

void Reader::parse(Scene& scene){
	for(pugi::xml_node test_params = root.find_child_by_attribute("test", "id", test_num).first_child(); test_params; test_params = test_params.next_sibling()){
		// printf("%s\n", test_params.name());

		if(strcmp(test_params.name(), "setup") == 0){
			// printf("//%s\n", test_params.name());

			for(pugi::xml_node setup_params = test_params.first_child(); setup_params; setup_params = setup_params.next_sibling()){
				// printf("%s\n", setup_params.name());
				if(strcmp(setup_params.name(), "lights") == 0){
					for(pugi::xml_node lights = setup_params.first_child(); lights; lights = lights.next_sibling()){
						if(strcmp(lights.name(), "dl") == 0){
							// printf("%s\n", lights.name());
							// printf("%s\n", lights.child_value("dir"));
							// printf("%s\n", lights.child_value("col"));

							float x, y, z;
							float r, g, b;

							std::stringstream dir(lights.child_value("dir"));
							std::stringstream col(lights.child_value("col"));

							dir >> x, dir >> y, dir >> z;
							col >> r, col >> g, col >> b;

							DirectionalLight* dl = new DirectionalLight(x, y, z, r, g, b);
							scene.insertDirectionalLight(dl);
						} else if(strcmp(lights.name(), "pl") == 0){
							// printf("%s\n", lights.name());
							// printf("%s\n", lights.child_value("pos"));
							// printf("%s\n", lights.child_value("center"));
							// printf("%s\n", lights.child_value("scale"));
							// printf("%s\n", lights.child_value("col"));

							float x, y, z;
							float cX, cY, cZ;
							float s;
							float r, g, b;

							std::stringstream pos(lights.child_value("pos"));
							std::stringstream center(lights.child_value("center"));
							std::stringstream scale(lights.child_value("scale"));
							std::stringstream col(lights.child_value("col"));

							pos >> x, pos >> y, pos >> z;
							center >> cX, center >> cY, center >> cZ;
							scale >> s;
							col >> r, col >> g, col >> b;

							PointLight* pl = new PointLight(x, y, z, cX, cY, cZ, s, r, g, b);
							scene.insertPointLight(pl);
						} 
					}
				} else if(strcmp(setup_params.name(), "cam") == 0){
					// printf("%s\n", setup_params.name());
					// printf("%s\n", setup_params.child_value("pos"));
					// printf("%s\n", setup_params.child_value("view"));
					// printf("%s\n", setup_params.child_value("up"));
					// printf("%s\n", setup_params.child_value("depth"));

					float x, y, z;
					float vX, vY, vZ;
					float uX, uY, uZ;
					float d;

					std::stringstream pos(setup_params.child_value("pos"));
					std::stringstream view(setup_params.child_value("view"));
					std::stringstream up(setup_params.child_value("up"));
					std::stringstream depth(setup_params.child_value("depth"));

					pos >> x, pos >> y, pos >> z;
					view >> vX, view >> vY, view >> vZ;
					up >> uX, up >> uY, up >> uZ;
					depth >> d;

					Camera* cam = new Camera(x, y, z, vX, vY, vZ, uX, uY, uZ, d);
					scene.defineCamera(cam);
				} else if(strcmp(setup_params.name(), "image") == 0){
					// printf("%s\n", setup_params.name());
					// printf("%s\n", setup_params.child_value("width"));
					// printf("%s\n", setup_params.child_value("height"));
					// printf("%s\n", setup_params.child_value("out"));

					float w = atoi(setup_params.child_value("width"));
					float h = atoi(setup_params.child_value("height"));
					const std::string loc = std::string(setup_params.child_value("out"));

					scene.defineImage(w, h, loc);
				}
			}
		} else if(strcmp(test_params.name(), "geom") == 0){
			for(pugi::xml_node geom = test_params.first_child(); geom; geom = geom.next_sibling()){
				if(strcmp(geom.name(), "sphere") == 0){
				// 	printf("%s\n", geom.name());
				// 	printf("%s\n", geom.child_value("pos"));
				// 	printf("%s\n", geom.child_value("rad"));

					float x, y, z;
					float r;

					std::stringstream pos(geom.child_value("pos"));
					std::stringstream rad(geom.child_value("rad"));
					
					pos >> x, pos >> y, pos >> z;
					rad >> r;

					Sphere* sph = new Sphere(x, y, z, r);
					
					for(pugi::xml_node sphere_params = geom.first_child(); sphere_params; sphere_params = sphere_params.next_sibling()){
						if(strcmp(sphere_params.name(), "ka") == 0){
							// printf("%s\n", geom.child_value("ka"));
							float kaR, kaG, kaB;
							std::stringstream ka(geom.child_value("ka"));
							ka >> kaR, ka >> kaG, ka >> kaB;
							sph->setAmbient(glm::vec3(kaR, kaG, kaB));
						} else if(strcmp(sphere_params.name(), "kd") == 0){
							// printf("%s\n", geom.child_value("kd"));
							float kdR, kdG, kdB;
							std::stringstream kd(geom.child_value("kd"));
							kd >> kdR, kd >> kdG, kd >> kdB;
							sph->setDiffuse(glm::vec3(kdR, kdG, kdB));
						} else if(strcmp(sphere_params.name(), "ks") == 0){
							// printf("%s\n", geom.child_value("ks"));
							float ksR, ksG, ksB;
							std::stringstream ks(geom.child_value("ks"));
							ks >> ksR, ks >> ksG, ks >> ksB;
							sph->setSpecular(glm::vec3(ksR, ksG, ksB));
						} else if(strcmp(sphere_params.name(), "sp") == 0){
							// printf("%s\n", geom.child_value("sp"));
							int spow;
							std::stringstream sp(geom.child_value("sp"));
							sp >> spow;
							sph->setSpecularPow(spow);
						} else if(strcmp(sphere_params.name(), "kr") == 0){
							// printf("%s\n", geom.child_value("kr"));
							float krR, krG, krB;
							std::stringstream kr(geom.child_value("kr"));
							kr >> krR, kr >> krG, kr >> krB;
							sph->setReflect(glm::vec3(krR, krG, krB));
						}
					}

					scene.insertSphere(sph);
				}
			}
		}
	}


	// printf("%s\n", root.find_child_by_attribute("test", "id", "0").children());
}