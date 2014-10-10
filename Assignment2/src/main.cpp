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

#ifdef OSX
#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/glu.h>
#endif

#include <time.h>
#include <math.h>

#include <glm/glm.hpp>

#include "PointLight.h"
#include "DirectionalLight.h"
#include "Ray.h"
#include "Scene.h"
#include "Sphere.h"


#define PI 3.14159265  // Should be used from mathlib
inline float sqr(float x) { return x*x; }

using namespace std;


//****************************************************
// Main function:
// Read command inputs and initialize 
//****************************************************
int main(int argc, char *argv[]) {
  //Initialize arguments; constants and lights;
  for (int i = 0; i < argc; i++) {
    std::string arg(argv[i]);

    if(arg == "-scene"){
      k_ambient = glm::vec3(atof(argv[i+1]), atof(argv[i+2]), atof(argv[i+3]));

      i+=3;
    } else if(arg == "-kd"){
      k_diffuse = glm::vec3(atof(argv[i+1]), atof(argv[i+2]), atof(argv[i+3]));

      i+=3;
    } else if(arg == "-ks"){
      k_specular = glm::vec3(atof(argv[i+1]), atof(argv[i+2]), atof(argv[i+3]));

      i+=3;
    }  else if(arg == "-sp"){
      specular_pow = atof(argv[i+1]);

      i+=1;
    }  else if(arg == "-pl"){
      ::new(&point_lights[num_pl]) PointLight(atof(argv[i+1]), atof(argv[i+2]), atof(argv[i+3]), atof(argv[i+4]), atof(argv[i+5]), atof(argv[i+6]));

      i+=6;
      num_pl++;
    } else if(arg == "-dl"){
      ::new(&dir_lights[num_dl]) DirectionalLight(atof(argv[i+1]), atof(argv[i+2]), atof(argv[i+3]), atof(argv[i+4]), atof(argv[i+5]), atof(argv[i+6]));

      i+=6;
      num_dl++;
    } else {

    }
  }

  //This initializes glut
  glutInit(&argc, argv);

  //This tells glut to use a double-buffered window with red, green, and blue channels 
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

  // Initalize theviewport size
  viewport.w = 400;
  viewport.h = 400;

  //The size and position of the window
  glutInitWindowSize(viewport.w, viewport.h);
  glutInitWindowPosition(0,0);
  glutCreateWindow(argv[0]);

  initScene();							// quick function to set up scene

  glutDisplayFunc(myDisplay);				// function to run when its time to draw something
  glutReshapeFunc(myReshape);				// function to run when the window gets resized

  glutKeyboardFunc(keyPress);     // quit on space button

  glutMainLoop();							// infinite loop that will keep drawing and resizing
  // and whatever else

  return 0;
}