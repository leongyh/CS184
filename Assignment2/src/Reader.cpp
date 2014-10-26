#include "Reader.h"
#include <cstdlib>
#include <cstdio>
#include <stdio.h>
#include <string.h>
#include <sstream>

Reader::Reader(const char* file_loc, int num){
	pugi::xml_document doc;
	doc.load_file(file_loc);

	root = doc.document_element();
	test_num = num;
}

Reader::~Reader(){

}

void Reader::run(Scene& scene){

	// bool found_test = false;
	// bool end = false;

	// if(in.is_open()){
	// 	//find test case first
	// 	while(!found_test){
	// 		std::string line, cmd;

	// 		if(!getline(in, line)){
	// 			found_test = true;
	// 			end = true;
	// 			break;
	// 		}

	// 		stringstream s(line);

	// 		s >> cmd;

	// 		if(cmd == "#test"){
	// 			int case_num;

	// 			s >> case_num;

	// 			if(case_num == test_num){
	// 				found_test = true;
	// 			}
	// 		}
	// 	}

	// 	//find all params of that test case
	// 	while(!end){
	// 		std::string line, cmd;

	// 		if(!getline(in, line)){
	// 			found_test = true;
	// 			end = true;
	// 			break;
	// 		}

	// 		stringstream s(line);

	// 		s >> cmd;

	// 	   	if(arg == "<setting>"){
	// 	    	k_ambient = glm::vec3(atof(argv[i+1]), atof(argv[i+2]), atof(argv[i+3]));
	// 	    } else if(arg == "-kd"){
	// 	    	k_diffuse = glm::vec3(atof(argv[i+1]), atof(argv[i+2]), atof(argv[i+3]));
	// 	    } else if(arg == "-ks"){
	// 	      k_specular = glm::vec3(atof(argv[i+1]), atof(argv[i+2]), atof(argv[i+3]));

	// 	      i+=3;
	// 	    }  else if(arg == "-sp"){
	// 	      specular_pow = atof(argv[i+1]);

	// 	      i+=1;
	// 	    }  else if(arg == "-pl"){
	// 	      ::new(&point_lights[num_pl]) PointLight(atof(argv[i+1]), atof(argv[i+2]), atof(argv[i+3]), atof(argv[i+4]), atof(argv[i+5]), atof(argv[i+6]));

	// 	      i+=6;
	// 	      num_pl++;
	// 	    } else if(arg == "-dl"){
	// 	      ::new(&dir_lights[num_dl]) DirectionalLight(atof(argv[i+1]), atof(argv[i+2]), atof(argv[i+3]), atof(argv[i+4]), atof(argv[i+5]), atof(argv[i+6]));
	// 	}
	// }
}

void Reader::test(Scene& scene){
	for(pugi::xml_node test_params = root.find_child_by_attribute("test", "id", "0").first_child(); test_params; test_params = test_params.next_sibling()){
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
				}
			}
		} else if(test_params.name() == "geom"){
			for(pugi::xml_node geom = test_params.first_child(); geom; geom = geom.next_sibling()){
				if(strcmp(geom.name(), "sphere") == 0){

				}
			}
		}
	}


	// printf("%s\n", root.find_child_by_attribute("test", "id", "0").children());
}