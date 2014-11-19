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

float angle_z = 0.0f, angle_x = 0.0f;
float tx = 0.0f, tz = 0.0f;
float scale = 1.0f;

void initLights() {
   GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat mat_shininess[] = { 50.0 };
   GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_SMOOTH);

   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
   glLightfv(GL_LIGHT0, GL_POSITION, light_position);

   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_DEPTH_TEST);
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

  gluLookAt(0.0f, -9.0f, 5.0f,
      0.0, 0.0f, 0.0f,
      0.0f, 0.0f, 1.0f);

  glScalef(scale, scale, scale);
  glTranslatef(tx, 0.0f, tz);
  glRotatef(angle_z, 0.0f, 0.0f, 1.0f);
  glRotatef(angle_x, 1.0f, 0.0f, 0.0f);
  
  scene->draw(WIREFRAME, FLATSHADING);

  glutSwapBuffers();
  glFlush();
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
  const float rot_sen = 1.0f;
  const float trans_sen = 0.1f;

  int mod = glutGetModifiers();

  switch(key){
    case GLUT_KEY_LEFT:
      if(mod == GLUT_ACTIVE_SHIFT){
        tx -= trans_sen;
      } else{
        angle_z -= rot_sen;
      }
      break;
    case GLUT_KEY_RIGHT:
      if(mod == GLUT_ACTIVE_SHIFT){
        tx += trans_sen;
      } else{
        angle_z += rot_sen;
      }
      break;
    case GLUT_KEY_UP:
      if(mod == GLUT_ACTIVE_SHIFT){
        tz += trans_sen;
      } else{
        angle_x -= rot_sen;
      }
      break;
    case GLUT_KEY_DOWN:
      if(mod == GLUT_ACTIVE_SHIFT){
        tz -= trans_sen;
      } else{
        angle_x += rot_sen;
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
  scene->render();
  // scene->print();

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
  glutSpecialFunc(specialKeyPress);

  glEnable(GL_DEPTH_TEST);
  
  glutMainLoop();

  return 1;
}