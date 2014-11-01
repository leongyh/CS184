#include "Reader.h"
#include <cstdlib>
#include <cstdio>
#include <stdio.h>
#include <string.h>
#include <sstream>

Reader::Reader(const char* file_loc, char* num){
	obj = new ObjReader();
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
							// printf("%s\n", lights.child_value("col"));
							// printf("%s\n", lights.child_value("falloff"));

							float x, y, z;
							float r, g, b;
							int f;

							PointLight* pl;

							std::stringstream pos(lights.child_value("pos"));
							std::stringstream col(lights.child_value("col"));

							pos >> x, pos >> y, pos >> z;
							col >> r, col >> g, col >> b;

							if(strcmp(lights.child_value("falloff"), "") == 0){
								pl = new PointLight(x, y, z, r, g, b);
							} else{
								std::stringstream fall(lights.child_value("falloff"));

								fall >> f;

								pl = new PointLight(x, y, z, r, g, b, f);
							}

							scene.insertPointLight(pl);
						} else if(strcmp(lights.name(), "al") == 0){
							// printf("%s\n", lights.name());
							// printf("%s\n", lights.child_value("col"));

							float r, g, b;
							
							std::stringstream col(lights.child_value("col"));

							col >> r, col >> g, col >> b;

							AmbientLight* al = new AmbientLight(r, g, b);
							scene.insertAmbientLight(al);
						} 
					}
				} else if(strcmp(setup_params.name(), "cam") == 0){
					// // printf("%s\n", setup_params.name());
					// // printf("%s\n", setup_params.child_value("pos"));
					// // printf("%s\n", setup_params.child_value("view"));
					// // printf("%s\n", setup_params.child_value("up"));
					// // printf("%s\n", setup_params.child_value("depth"));

					// float x, y, z;
					// float vX, vY, vZ;
					// float uX, uY, uZ;
					// float d;

					// std::stringstream pos(setup_params.child_value("pos"));
					// std::stringstream view(setup_params.child_value("view"));
					// std::stringstream up(setup_params.child_value("up"));
					// std::stringstream depth(setup_params.child_value("depth"));

					// pos >> x, pos >> y, pos >> z;
					// view >> vX, view >> vY, view >> vZ;
					// up >> uX, up >> uY, up >> uZ;
					// depth >> d;

					// Camera* cam = new Camera(x, y, z, vX, vY, vZ, uX, uY, uZ, d);
					// scene.defineCamera(cam);

					// printf("%s\n", setup_params.name());
					// printf("%s\n", setup_params.child_value("pos"));
					// printf("%s\n", setup_params.child_value("ll"));
					// printf("%s\n", setup_params.child_value("lr"));
					// printf("%s\n", setup_params.child_value("ul"));
					// printf("%s\n", setup_params.child_value("ur"));

					float x, y, z;
					float llx, lly, llz;
					float lrx, lry, lrz;
					float ulx, uly, ulz;
					float urx, ury, urz;

					std::stringstream pos(setup_params.child_value("pos"));
					std::stringstream ll(setup_params.child_value("ll"));
					std::stringstream lr(setup_params.child_value("lr"));
					std::stringstream ul(setup_params.child_value("ul"));
					std::stringstream ur(setup_params.child_value("ur"));

					pos >> x, pos >> y, pos >> z;
					ll >> llx, ll >> lly, ll >> llz;
					lr >> lrx, lr >> lry, lr >> lrz;
					ul >> ulx, ul >> uly, ul >> ulz;
					ur >> urx, ur >> ury, ur >> urz;

					Camera* cam = new Camera(x, y, z, llx, lly, llz, lrx, lry, lrz, ulx, uly, ulz, urx, ury, urz);
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
					// printf("%s\n", geom.name());
					// printf("%s\n", geom.child_value("pos"));
					// printf("%s\n", geom.child_value("rad"));

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
						} else if(strcmp(sphere_params.name(), "trans") == 0){
							Transform* t = new Transform();

							for(pugi::xml_node trans_params = sphere_params.first_child(); trans_params; trans_params = trans_params.next_sibling()){
								if(strcmp(trans_params.name(), "tlt") == 0){
									// printf("%s\n", trans_params.child_value());
									float x, y, z;
									std::stringstream tlt(trans_params.child_value());
									tlt >> x, tlt >> y, tlt >> z;
									t->pushTranslate(x, y, z);
								} else if(strcmp(trans_params.name(), "scale") == 0){
									// printf("%s\n", trans_params.child_value());
									float x, y, z;
									std::stringstream scale(trans_params.child_value());
									scale >> x, scale >> y, scale >> z;
									t->pushScale(x, y, z);
								} else if(strcmp(trans_params.name(), "rot") == 0){
									// printf("%s\n", trans_params.child_value());
									float x, y, z;
									std::stringstream rot(trans_params.child_value());
									rot >> x, rot >> y, rot >> z;
									t->pushRotate(x, y, z);
								}
							}
							// t->print();
							sph->setTransform(t->getTransform());
						}
					}

					scene.insertSphere(sph);
				} else if(strcmp(geom.name(), "triangle") == 0){
					// printf("%s\n", geom.name());
					// printf("%s\n", geom.child_value("v1"));
					// printf("%s\n", geom.child_value("v2"));
					// printf("%s\n", geom.child_value("v3"));

					float v1x, v1y, v1z;
					float v2x, v2y, v2z;
					float v3x, v3y, v3z;

					std::stringstream v1(geom.child_value("v1"));
					std::stringstream v2(geom.child_value("v2"));
					std::stringstream v3(geom.child_value("v3"));
					
					v1 >> v1x, v1 >> v1y, v1 >> v1z;
					v2 >> v2x, v2 >> v2y, v2 >> v2z;
					v3 >> v3x, v3 >> v3y, v3 >> v3z;

					Triangle* tri = new Triangle(v1x, v1y, v1z, v2x, v2y, v2z, v3x, v3y, v3z);
					
					for(pugi::xml_node tri_params = geom.first_child(); tri_params; tri_params = tri_params.next_sibling()){
						if(strcmp(tri_params.name(), "ka") == 0){
							// printf("%s\n", geom.child_value("ka"));
							float kaR, kaG, kaB;
							std::stringstream ka(geom.child_value("ka"));
							ka >> kaR, ka >> kaG, ka >> kaB;
							tri->setAmbient(glm::vec3(kaR, kaG, kaB));
						} else if(strcmp(tri_params.name(), "kd") == 0){
							// printf("%s\n", geom.child_value("kd"));
							float kdR, kdG, kdB;
							std::stringstream kd(geom.child_value("kd"));
							kd >> kdR, kd >> kdG, kd >> kdB;
							tri->setDiffuse(glm::vec3(kdR, kdG, kdB));
						} else if(strcmp(tri_params.name(), "ks") == 0){
							// printf("%s\n", geom.child_value("ks"));
							float ksR, ksG, ksB;
							std::stringstream ks(geom.child_value("ks"));
							ks >> ksR, ks >> ksG, ks >> ksB;
							tri->setSpecular(glm::vec3(ksR, ksG, ksB));
						} else if(strcmp(tri_params.name(), "sp") == 0){
							// printf("%s\n", geom.child_value("sp"));
							int spow;
							std::stringstream sp(geom.child_value("sp"));
							sp >> spow;
							tri->setSpecularPow(spow);
						} else if(strcmp(tri_params.name(), "kr") == 0){
							// printf("%s\n", geom.child_value("kr"));
							float krR, krG, krB;
							std::stringstream kr(geom.child_value("kr"));
							kr >> krR, kr >> krG, kr >> krB;
							tri->setReflect(glm::vec3(krR, krG, krB));
						} else if(strcmp(tri_params.name(), "trans") == 0){
							Transform* t = new Transform();

							for(pugi::xml_node trans_params = tri_params.first_child(); trans_params; trans_params = trans_params.next_sibling()){
								if(strcmp(trans_params.name(), "tlt") == 0){
									// printf("%s\n", trans_params.child_value());
									float x, y, z;
									std::stringstream tlt(trans_params.child_value());
									tlt >> x, tlt >> y, tlt >> z;
									t->pushTranslate(x, y, z);
								} else if(strcmp(trans_params.name(), "scale") == 0){
									// printf("%s\n", trans_params.child_value());
									float x, y, z;
									std::stringstream scale(trans_params.child_value());
									scale >> x, scale >> y, scale >> z;
									t->pushScale(x, y, z);
								} else if(strcmp(trans_params.name(), "rot") == 0){
									// printf("%s\n", trans_params.child_value());
									float x, y, z;
									std::stringstream rot(trans_params.child_value());
									rot >> x, rot >> y, rot >> z;
									t->pushRotate(x, y, z);
								}
							}
							// t->print();
							tri->setTransform(t->getTransform());
						}
					}

					scene.insertTriangle(tri);
				} else if(strcmp(geom.name(), "obj") == 0){
					// printf("%s\n", geom.name());
					// printf("%s\n", geom.child_value("file"));
					// printf("%s\n", geom.child_value("trans"));

					const char* loc = geom.child_value("file");
					int type;
					glm::vec3 k_amb, k_diff, k_spec, k_refl;
					int spec_pow;

					std::stringstream t(geom.child_value("type"));

					t >> type;
					
					obj->parse(loc, type);
					// printf("%s\n", "Hi");
					for(pugi::xml_node obj_params = geom.first_child(); obj_params; obj_params = obj_params.next_sibling()){
						if(strcmp(obj_params.name(), "ka") == 0){
							// printf("%s\n", geom.child_value("ka"));
							float kaR, kaG, kaB;
							std::stringstream ka(geom.child_value("ka"));
							ka >> kaR, ka >> kaG, ka >> kaB;
							k_amb = glm::vec3(kaR, kaG, kaB);
						} else if(strcmp(obj_params.name(), "kd") == 0){
							// printf("%s\n", geom.child_value("kd"));
							float kdR, kdG, kdB;
							std::stringstream kd(geom.child_value("kd"));
							kd >> kdR, kd >> kdG, kd >> kdB;
							k_diff = glm::vec3(kdR, kdG, kdB);
						} else if(strcmp(obj_params.name(), "ks") == 0){
							// printf("%s\n", geom.child_value("ks"));
							float ksR, ksG, ksB;
							std::stringstream ks(geom.child_value("ks"));
							ks >> ksR, ks >> ksG, ks >> ksB;
							k_spec = glm::vec3(ksR, ksG, ksB);
						} else if(strcmp(obj_params.name(), "sp") == 0){
							// printf("%s\n", geom.child_value("sp"));
							int spow;
							std::stringstream sp(geom.child_value("sp"));
							sp >> spow;
							spec_pow = spow;
						} else if(strcmp(obj_params.name(), "kr") == 0){
							// printf("%s\n", geom.child_value("kr"));
							float krR, krG, krB;
							std::stringstream kr(geom.child_value("kr"));
							kr >> krR, kr >> krG, kr >> krB;
							k_refl = glm::vec3(krR, krG, krB);
						} else if(strcmp(obj_params.name(), "trans") == 0){
							Transform* t = new Transform();

							for(pugi::xml_node trans_params = obj_params.first_child(); trans_params; trans_params = trans_params.next_sibling()){
								if(strcmp(trans_params.name(), "tlt") == 0){
									// printf("%s\n", trans_params.child_value());
									float x, y, z;
									std::stringstream tlt(trans_params.child_value());
									tlt >> x, tlt >> y, tlt >> z;
									t->pushTranslate(x, y, z);
								} else if(strcmp(trans_params.name(), "scale") == 0){
									// printf("%s\n", trans_params.child_value());
									float x, y, z;
									std::stringstream scale(trans_params.child_value());
									scale >> x, scale >> y, scale >> z;
									t->pushScale(x, y, z);
								} else if(strcmp(trans_params.name(), "rot") == 0){
									// printf("%s\n", trans_params.child_value());
									float x, y, z;
									std::stringstream rot(trans_params.child_value());
									rot >> x, rot >> y, rot >> z;
									t->pushRotate(x, y, z);
								}
							}
							// t->print();
							obj->setTransform(t->getTransform());
						}
					}

					obj->createObj(scene, k_amb, k_diff, k_spec, spec_pow, k_refl);
					obj->reset();
					// printf("%s\n", "Hi");
				}
			}
		}
	}

	// printf("%s\n", root.find_child_by_attribute("test", "id", "0").children());
}