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

#include "Scene.h"
#include "Reader.h"

#define PI 3.14159265  // Should be used from mathlib
inline float sqr(float x) { return x*x; }

using namespace std;


//****************************************************
// Main function:
// Read command inputs and initialize 
//****************************************************
int main(int argc, char *argv[]) {
  Scene* scene = new Scene();
  
  Reader* reader = new Reader("scene.xml", argv[1]);
  reader->parse(*scene);
  scene->render();

  return 0;
}