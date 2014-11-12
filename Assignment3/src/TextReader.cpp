#include "TextReader.h"
#include <stdio>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

TextReader::TextReader(){
}

TextReader::~TextReader(){

}

void TextReader::parse(Scene& scene, const char* file_loc){
	std::ifstream file;
	file.open(file_loc);
	std::string line;

	// Transform* trans = new Transform();
	// bool is_transformed = false;

	std::getline(file, line);

	std::stringstream fl(line);
	int num_patches;
	fl >> num_patch;

	while(std::getline(file, line)){
		std::stringstream l(line);
		
		if(l.length() > 0){
			Patch* patch = new Patch();

			for(int i = 0; i < 4; i++){
				Curve* curve = new Curve(3);

				for(int j = 0; j < 4; i++){
					float x, y, z;

					l >> x, l >> y, l >> z;

					ControlPoint* p = new ControlPoint(x, y, z);
					curve->insertPoint(p);
				}

				patch->insertCurve(curve);
			}
		}

		scene->insertPatch(patch);
	}
	
	file.close();
}