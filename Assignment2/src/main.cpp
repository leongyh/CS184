#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <string>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

#include <time.h>
#include <math.h>

#include <glm/glm.hpp>

#include "Scene.h"
#include "Reader.h"
#include "TextReader.h"

#define PI 3.14159265  // Should be used from mathlib
inline float sqr(float x) { return x*x; }

using namespace std;


//****************************************************
// Main function:
// Read command inputs and initialize 
//****************************************************
int main(int argc, char *argv[]) {
	std::string file_in, file_out;
	int w, h;
	int depth = 0;

	for (int i = 1; i < argc; i++) {
		std::string arg(argv[i]);

		if(arg == "-f"){
			file_in = argv[i+1];
			i+=1;
		} else if(arg == "-dim"){
			w = atoi(argv[i+1]);
			h = atof(argv[i+2]);
		  	i+=2;
		} else if(arg == "-img"){
			file_out = argv[i+1];
			i+=1;
		} else if(arg == "-d"){
			depth = atoi(argv[i+1]);
			i+=1;
		} else {
			printf("Unknown flag %s \n", argv[i]);
		}
	}

	Scene* scene;

	if(depth > 0){
		scene = new Scene(depth);	
	} else{
		scene = new Scene();
	}

	// Reader* reader = new Reader("obj_tests.xml", argv[1]);
	TextReader* reader = new TextReader();

	scene->defineImage(w, h, file_out.c_str());
	reader->parse(*scene, file_in.c_str());
	scene->render();

  return 0;
}