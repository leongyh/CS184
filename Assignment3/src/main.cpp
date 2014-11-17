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

#include "TextReader.h"
#include "Scene.h"
#include "PointLight.h"
#include "DirectionalLight.h"

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

bool WIREFRAME = true;
bool FLATSHADING = false;

float phi = 90.0f, theta = 0.0f;
float eyeX = 0.0f, eyeY = -5.0f, eyeZ = 0.0f;
float transX = 0.0f, transY = 0.0f, transZ = 0.0f;

float angle = 0.0f;
float lx = 0.0f, lz = -1.0f;
float x = 0.0f, z = 5.0f;

void initGL() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glOrtho(-5.0f, 5.0f, -5.0f, 5.0f, -5.0f, 5.0f);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void drawSnowMan() {

  glColor3f(1.0f, 1.0f, 1.0f);

// Draw Body
  glTranslatef(0.0f ,0.75f, 0.0f);
  glutSolidSphere(0.75f,20,20);

// Draw Head
  glTranslatef(0.0f, 1.0f, 0.0f);
  glutSolidSphere(0.25f,20,20);

// Draw Eyes
  glPushMatrix();
  glColor3f(0.0f,0.0f,0.0f);
  glTranslatef(0.05f, 0.10f, 0.18f);
  glutSolidSphere(0.05f,10,10);
  glTranslatef(-0.1f, 0.0f, 0.0f);
  glutSolidSphere(0.05f,10,10);
  glPopMatrix();

// Draw Nose
  glColor3f(1.0f, 0.5f , 0.5f);
  glutSolidCone(0.08f,0.5f,10,2);
}

void renderScene(void) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // glEnable(GL_DEPTH_TEST);
  // glLoadIdentity();

  // gluLookAt(eyeX + transX, eyeY + transY, eyeZ + transZ, 
  //           0.0f + transX, 0.0f + transY,  0.0f + transZ,
  //           0.0f, 0.0f,  1.0f);
  
  // scene->render(WIREFRAME, FLATSHADING);
  glLoadIdentity();

  gluLookAt(  x, 1.0f, z,
      x+lx, 1.0f,  z+lz,
      0.0f, 1.0f,  0.0f);

  scene->render(WIREFRAME, FLATSHADING);

  glutSwapBuffers();
}

void myReshape(int w, int h) {
  viewport.w = w;
  viewport.h = h;

  // glViewport (0,0,viewport.w,viewport.h);
  // glMatrixMode(GL_PROJECTION);
  // glLoadIdentity();
  
  // // gluLookAt(eyeX + transX, eyeY + transY, eyeZ + transZ, 
  //           // 0.0f + transX, 0.0f + transY,  0.0f + transZ,
  //           // 0.0f, 0.0f,  1.0f);

  // glOrtho(-5.0f, 5.0f, -5.0f, 5.0f, -5.0f, 5.0f);

  if(h == 0)
    h = 1;
  float ratio = 1.0* w / h;

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glViewport(0, 0, viewport.w, viewport.h);

  // float nRange = 5.0f;

  // if (w <= h)
  //   glOrtho (-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange, nRange);
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
    case 'w':
      WIREFRAME = WIREFRAME ^ true;
      break;
    case 's': 
      break;
    default:
      break;
  }
}

void specialKeyPress(int key, int xx, int yy) {
  float fraction = 0.1f;
  int mod = glutGetModifiers();

  switch(key){
    case GLUT_KEY_LEFT:
      if(mod == GLUT_ACTIVE_SHIFT){

      } else{
        angle -= 0.01f;
        lx = sin(angle);
        lz = -cos(angle);
      }
      break;
    case GLUT_KEY_RIGHT:
      if(mod == GLUT_ACTIVE_SHIFT){

      } else{
        angle += 0.01f;
        lx = sin(angle);
        lz = -cos(angle);
      }
      break;
    case GLUT_KEY_UP:
      if(mod == GLUT_ACTIVE_SHIFT){

      } else{
        x += lx * fraction;
        z += lz * fraction;
      }
      break;
    case GLUT_KEY_DOWN:
      if(mod == GLUT_ACTIVE_SHIFT){

      } else{
        x -= lx * fraction;
        z -= lz * fraction;
      }
      break;
    default:
      break;
  }
}

//****************************************************
// the usual stuff, nothing exciting here
//****************************************************
int main(int argc, char *argv[]) {
  // Initalize theviewport size
  viewport.w = 500;
  viewport.h = 500;

  scene = new Scene(0, atof(argv[2]));
  TextReader* reader = new TextReader();

  reader->parse(*scene, argv[1]);
  // scene->print();

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowSize(viewport.w, viewport.h);
  glutInitWindowPosition(0,0);
  glutCreateWindow(argv[0]);

  // initGL();

  glutDisplayFunc(renderScene);
  glutReshapeFunc(myReshape);
  glutIdleFunc(renderScene);
  
  glutKeyboardFunc(keyPress);
  glutSpecialFunc(specialKeyPress);

  glEnable(GL_DEPTH_TEST);
  
  glutMainLoop();

  return 1;
}