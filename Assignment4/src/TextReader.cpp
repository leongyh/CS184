#include "TextReader.h"
#include <cstdio>
#include <vector>
#include <cstring>
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
	fl >> num_patches;

	Patch* patch = new Patch();
	int count = 0;

	while(std::getline(file, line)){
		if(line.length() > 1){
			std::stringstream l(line);
			// printf("%s\n", line.c_str());
			Curve* curve = new Curve(3);

			for(int j = 0; j < 4; j++){
				float x, y, z;

				l >> x, l >> y, l >> z;

				ControlPoint* p = new ControlPoint(x, y, z);
				curve->insertPoint(*p);
			}

			patch->insertCurve(*curve);

			count++;

			if(count % 4 == 0){
				scene.insertPatch(*patch);
				patch = new Patch();
			}
		}
	}
	
	file.close();
}