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
#include "Path.h"

#define PI 3.14159265  // Should be used from mathlib
inline float sqr(float x) { return x*x; }

using namespace std;

//****************************************************
// Some Classes
//****************************************************

class Viewport;

class Viewport {
  public:
    int w, h; // width and height
};


//****************************************************
// Global Variables
//****************************************************
Viewport	viewport;
Scene* scene;
Path* path;

float sens = 0.05f;
float x_t, y_t, z_t = 0.0f;
bool freeMode = false;
bool begin = false;

GLfloat light_position0[] = { 0.0, 1.0, -0.5, 0.0 };
GLfloat light_position1[] = { 20.0, -20.0, 0.0, 1.0 };
GLfloat light_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

GLfloat mat_ambient[] = { 0.3, 0.0, 0.1, 1.0 };
GLfloat mat_diffuse[] = { 0.85, 0.0, 0.1, 1.0 };
GLfloat mat_specular[] = { 0.8, 0.8, 0.8, 1.0 };
GLfloat shininess[] = { 16.0 };

GLfloat mat_ambient2[] = { 0.1, 0.0, 0.3, 1.0 };
GLfloat mat_diffuse2[] = { 0.1, 0.0, 0.85, 1.0 };
GLfloat mat_specular2[] = { 0.8, 0.8, 0.8, 1.0 };
GLfloat shininess2[] = { 16.0 };

void initLights(){
  glClearColor(0.0, 0.0, 0.0, 0.0);

  glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position0);

  glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
  glLightfv(GL_LIGHT1, GL_POSITION, light_position1);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
}

void renderScene(void) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  glLoadIdentity();

  gluLookAt(0.0f, -18.0f, 0.0f,
      0.0, 0.0f, 0.0f,
      0.0f, 0.0f, 1.0f);
  
  if(freeMode){
    scene->render(x_t, y_t, z_t);
  } else{
    if(begin){
      scene->renderPath();
    }
  }

  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
  scene->drawArm();

  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient2);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse2);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular2);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess2);
  scene->drawGoal();

  if(!freeMode)  scene->drawPath();
  
  glutSwapBuffers();
  glFlush();
}

void myReshape(int w, int h) {
  viewport.w = w;
  viewport.h = h;

  if(h == 0)
    h = 1;
  float ratio = 1.0* w / h;

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glViewport(0, 0, viewport.w, viewport.h);

  // float nRange = 5.0f;

  // if (w <= h)
  //   glOrtho (-nRange, nRange, -nRange*h/w, Rnange*h/w, -nRange, nRange);
  // else
  //   glOrtho (-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange, nRange);

  gluPerspective(45,ratio,1,100);

  glMatrixMode(GL_MODELVIEW);
}

//****************************************************
// callback function that handles keypress
//***************************************************
void keyPress(unsigned char key, int x, int y){
  switch(key){
    case ' ':
      exit(0);   //quit on space
      break;
    case 'd':
      x_t += sens;
      break;
    case 'a':
      x_t -= sens;
      break;
    case 'c':
      y_t += sens;
      break;
    case 'x':
      y_t -= sens;
      break;
    case 'w':
      z_t += sens;
      break;
    case 's':
      z_t -= sens;
      break;
    case 'b':
      begin ^= true;
    default:
      break;
  }
}

//****************************************************
// the usual stuff, nothing exciting here
//****************************************************
int main(int argc, char *argv[]) {
  // Initalize theviewport size
  viewport.w = 700;
  viewport.h = 700;

  std::string arg(argv[1]);
  int pathType = 1;

  if(arg == "-free"){
    printf("%s\n", argv[1]);
    freeMode = true;  
  } else if(arg == "-path"){
    pathType = atoi(argv[2]);
  }
  

  if(freeMode){
    scene = new Scene();
  } else{
    path = new Path(pathType);
    scene = new Scene(path);
  }

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowSize(viewport.w, viewport.h);
  glutInitWindowPosition(0,0);
  glutCreateWindow(argv[0]);

  initLights();

  glutDisplayFunc(renderScene);
  glutReshapeFunc(myReshape);
  glutIdleFunc(renderScene);
  
  glutKeyboardFunc(keyPress);

  glEnable(GL_DEPTH_TEST);
  
  glutMainLoop();

  return 1;
}