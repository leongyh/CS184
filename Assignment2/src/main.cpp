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
#include "MyVector.h"

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

glm::vec3 k_ambient = glm::vec3(0, 0, 0);
glm::vec3 k_diffuse = glm::vec3(0, 0, 0);
glm::vec3 k_specular = glm::vec3(0, 0, 0);

float specular_pow;

PointLight* point_lights = (PointLight*) malloc(sizeof(PointLight)*5);
DirectionalLight* dir_lights = (DirectionalLight*) malloc(sizeof(DirectionalLight)*5);

int num_pl = 0;
int num_dl = 0;

//****************************************************
// Simple init function
//****************************************************
void initScene(){

  // Nothing to do here for this simple example.

}


//****************************************************
// reshape viewport if the window is resized
//****************************************************
void myReshape(int w, int h) {
  viewport.w = w;
  viewport.h = h;

  glViewport (0,0,viewport.w,viewport.h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, viewport.w, 0, viewport.h);

}


//****************************************************
// A routine to set a pixel by drawing a GL point.  This is not a
// general purpose routine as it assumes a lot of stuff specific to
// this example.
//****************************************************

void setPixel(int x, int y, GLfloat r, GLfloat g, GLfloat b) {
  glColor3f(r, g, b);
  glVertex2f(x + 0.5, y + 0.5);   // The 0.5 is to target pixel
  // centers 
  // Note: Need to check for gap
  // bug on inst machines.
}

void setPixel3f(float x, float y, float z, GLfloat r, GLfloat g, GLfloat b) {
  glColor3f(r, g, b);
  glVertex3f(x, y, z);   // The 0.5 is to target pixel
  // centers 
  // Note: Need to check for gap
  // bug on inst machines.
}

glm::vec3 getNormal(int theta, int phi){
  float x = sin(theta * PI / 180) * cos(phi * PI / 180);
  float y = sin(theta * PI / 180) * sin(phi * PI / 180);
  float z = cos(theta * PI / 180);

  return glm::vec3(x, y, z);
}

glm::vec3 calculateDiffusion(glm::vec3 normal, glm::vec3 incident, glm::vec3 intensity){
  float dot = glm::dot(normal, incident);
  float r = max(k_diffuse.x * intensity.x * dot, 0.0f);
  float g = max(k_diffuse.y * intensity.y * dot, 0.0f);
  float b = max(k_diffuse.z * intensity.z * dot, 0.0f);

  return glm::vec3(r, g, b);
}

void drawSphere(float centerX, float centerY, float centerZ, float radius){
  glBegin(GL_POINTS);
  //handle sphere size and radius
  // int x,y,z;  // Pixel indices

  // int minX = max(0,(int)floor(centerX-radius));
  // int maxX = min(viewport.w-1,(int)ceil(centerX+radius));

  // int minY = max(0,(int)floor(centerY-radius));
  // int maxY = min(viewport.h-1,(int)ceil(centerY+radius));

  // int minZ = max(0,(int)floor(centerZ-radius));
  // int maxZ = min(viewport.h-1,(int)ceil(centerZ+radius));

  // int sized_radius = min()

  for(int theta = -90; theta < 90; theta++){
    for(int phi = 0; phi < 360; phi++){
      glm::vec3 normal = getNormal(theta, phi);

      //draw sphere test
      float x = radius * normal.x;
      float y = radius * normal.y;
      float z = radius * normal.z;

      setPixel3f(x, y, z, 1.0, 0.0, 0.0);

      // for(int d = 0; d < num_dl; d++){
      //   glm::vec3 rgbDiffusion = calculateDiffusion(normal, (dir_lights[d]).getReverseDirection(), (dir_lights[d]).getColor());
      // }

      // for (int p = 0; i < num_pl; p++)
      // {
      //   glm::vec3 rgbDiffusion = calculateDiffusion(normal, (point_lights[p]).getLightVec(1,1,1), (point_lights[p]).getColor());
      // }
    }
  }

}

//****************************************************
// Draw a filled circle.  
//****************************************************


void circle(float centerX, float centerY, float radius) {
  // Draw inner circle
  glBegin(GL_POINTS);

  // We could eliminate wasted work by only looping over the pixels
  // inside the sphere's radius.  But the example is more clear this
  // way.  In general drawing an object by loopig over the whole
  // screen is wasteful.

  int i,j;  // Pixel indices

  int minI = max(0,(int)floor(centerX-radius));
  int maxI = min(viewport.w-1,(int)ceil(centerX+radius));

  int minJ = max(0,(int)floor(centerY-radius));
  int maxJ = min(viewport.h-1,(int)ceil(centerY+radius));



  for (i=0;i<viewport.w;i++) {
    for (j=0;j<viewport.h;j++) {

      // Location of the center of pixel relative to center of sphere
      float x = (i+0.5-centerX);
      float y = (j+0.5-centerY);

      float dist = sqrt(sqr(x) + sqr(y));

      if (dist<=radius) {

        // This is the front-facing Z coordinate
        float z = sqrt(radius*radius-dist*dist);

        setPixel(i,j, 1.0, 0.0, 0.0);

        // This is amusing, but it assumes negative color values are treated reasonably.
        // setPixel(i,j, x/radius, y/radius, z/radius );
      }


    }
  }


  glEnd();
}
//****************************************************
// function that does the actual drawing of stuff
//***************************************************
void myDisplay() {

  glClear(GL_COLOR_BUFFER_BIT);				// clear the color buffer

  glMatrixMode(GL_MODELVIEW);			        // indicate we are specifying camera transformations
  glLoadIdentity();				        // make sure transformation is "zero'd"


  // Start drawing
  circle(viewport.w / 2.0 , viewport.h / 2.0 , min(viewport.w, viewport.h) / 3.0);

  glFlush();
  glutSwapBuffers();					// swap buffers (we earlier set double buffer)
}


//****************************************************
// callback function that handles keypress
//***************************************************
void keyPress(unsigned char key, int x, int y){
  switch(key){
    case ' ':
      exit(0);   //quit on space
      break;
    default:
      break;
  }
}

//****************************************************
// the usual stuff, nothing exciting here
//****************************************************
int main(int argc, char *argv[]) {
  //Initialize arguments; constants and lights;
  for (int i = 0; i < argc; i++) {
    std::string arg(argv[i]);

    if(arg == "-ka"){
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