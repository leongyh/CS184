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

// glm::vec3 k_ambient = glm::vec3(0, 0, 0);
// glm::vec3 k_diffuse = glm::vec3(0, 0, 0);
// glm::vec3 k_specular = glm::vec3(0, 0, 0);
// glm::vec3 k_ward = glm::vec3(0, 0, 0);

// float specular_pow = 0;
// float k_ward_x = 0;
// float k_ward_y = 0;

// glm::vec3 view_vec = glm::normalize(glm::vec3(0, 0, 1.0f));
// glm::vec3 ward_vec = glm::vec3(0, 0, 1.0f);

// PointLight* point_lights = (PointLight*) malloc(sizeof(PointLight)*5);
// DirectionalLight* dir_lights = (DirectionalLight*) malloc(sizeof(DirectionalLight)*5);

// int num_pl = 0;
// int num_dl = 0;

// float centerX;
// float centerY;
// float centerZ;
// float unit_radius;

// int specular_method = 0;
// bool is_multi = false;
// bool is_wave = false;

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

// glm::vec3 getNormal(float theta, float phi){
//   float x = sin(theta * PI / 180) * cos(phi * PI / 180);
//   float y = sin(theta * PI / 180) * sin(phi * PI / 180);
//   float z = cos(theta * PI / 180);

//   return glm::normalize(glm::vec3(x, y, z));
// }

// glm::vec3 calculateDiffusion(glm::vec3 normal, glm::vec3 incident, glm::vec3 intensity){
//   float dot = glm::dot(normal, incident);

//   float r = max(k_diffuse.x * intensity.x * dot, 0.0f);
//   float g = max(k_diffuse.y * intensity.y * dot, 0.0f);
//   float b = max(k_diffuse.z * intensity.z * dot, 0.0f);

//   return glm::vec3(r, g, b);
// }

// glm::vec3 calculateSpecular(glm::vec3 normal, glm::vec3 incident, glm::vec3 intensity){
//   //reflected
//   glm::vec3 r_vec = glm::normalize((-1.0f * incident) + (2.0f * glm::dot(incident, normal) * normal));

//   float dot_pow = pow(max(0.0f, glm::dot(r_vec, view_vec)), specular_pow);
//   if(dot_pow > 0.0001f){
//     printf("%f\n", dot_pow);
//   }
//   //half-angle
//   // glm::vec3 h_vec = glm::normalize(incident + view_vec);

//   // float dot_pow = pow(max(0.0f, glm::dot(normal, h_vec)), specular_pow);

//   float r = max(k_specular.x * intensity.x * dot_pow, 0.0f);
//   float g = max(k_specular.y * intensity.y * dot_pow, 0.0f);
//   float b = max(k_specular.z * intensity.z * dot_pow, 0.0f);
//   // printf("%f %f %f\n", r, g, b); 
//   return glm::vec3(r, g, b);
// }

// glm::vec3 calculateWardSpecular(glm::vec3 normal, glm::vec3 incident, glm::vec3 intensity){
//   //half-angle
//   glm::vec3 h_vec = glm::normalize(incident + view_vec);

//   //X and Y ansiotropic directions
//   glm::vec3 x_vec = glm::normalize(glm::cross(normal, ward_vec));
//   glm::vec3 y_vec = glm::normalize(glm::cross(normal, x_vec));

//   float beta = -2 * (pow((glm::dot(h_vec, x_vec) / k_ward_x), 2) + pow((glm::dot(h_vec, y_vec) / k_ward_y), 2)) / (1 + glm::dot(h_vec, normal));
//   float ward_const = (1 / (4 * PI * k_ward_x * k_ward_y * sqrt(glm::dot(normal, incident) * glm::dot(normal, view_vec)))) * exp(beta);

//   float dot = glm::dot(normal, incident);

//   float r = 0.0f;
//   float g = 0.0f;
//   float b = 0.0f;
  
//   if(!isnan(ward_const)){
//     r = max((k_ward.x * ward_const) * intensity.x * dot, 0.0f);
//     g = max((k_ward.y * ward_const) * intensity.y * dot, 0.0f);
//     b = max((k_ward.z * ward_const) * intensity.z * dot, 0.0f);
//   }

//   return glm::vec3(r, g, b);
// }

// glm::vec3 calculateAmbient(glm::vec3 intensity){
//   float r = max(k_ambient.x * intensity.x , 0.0f);
//   float g = max(k_ambient.y * intensity.y, 0.0f);
//   float b = max(k_ambient.z * intensity.z, 0.0f);

//   return glm::vec3(r, g, b);
// }

// void drawSphere(float cX, float cY, float cZ, float rad){
//   glBegin(GL_POINTS);
  
//   //iterate through sperical coordinate. 0.25f interval due to gaps in pixel.
//   for(float theta = -90; theta < 90; theta+=0.25f){
//     for(float phi = 0; phi < 360; phi+=0.25f){
//       glm::vec3 normal = getNormal(theta, phi);

//       //coordinates of surface.
//       float x = rad * normal.x + cX;
//       float y = rad * normal.y + cY;
//       float z = rad * normal.z + cZ;

//       //color components
//       float r = 0.0f;
//       float g = 0.0f;
//       float b = 0.0f;

//       for(int d = 0; d < num_dl; d++){
//         glm::vec3 rgbDiffusion = calculateDiffusion(normal, (dir_lights[d]).getReverseDirection(), (dir_lights[d]).getColor());

//         glm::vec3 rgbSpecular = glm::vec3(0.0f, 0.0f, 0.0f);

//         if(specular_method == 1){
//           rgbSpecular = calculateSpecular(normal, (dir_lights[d]).getReverseDirection(), (dir_lights[d]).getColor());
//         } else if(specular_method == 2){
//           rgbSpecular = calculateWardSpecular(normal, (dir_lights[d]).getReverseDirection(), (dir_lights[d]).getColor());
//         }

//         glm::vec3 rgbAmbient = calculateAmbient((dir_lights[d]).getColor());

//         r += rgbDiffusion.x + rgbSpecular.x + rgbAmbient.x;
//         g += rgbDiffusion.y + rgbSpecular.y + rgbAmbient.y;
//         b += rgbDiffusion.z + rgbSpecular.z + rgbAmbient.z;
//       }

//       for (int p = 0; p < num_pl; p++)
//       {
//         glm::vec3 rgbDiffusion = calculateDiffusion(normal, (point_lights[p]).getLightVec(x, y, z), (point_lights[p]).getColor());

//         glm::vec3 rgbSpecular = glm::vec3(0.0f, 0.0f, 0.0f);

//         if(specular_method == 1){
//           rgbSpecular = calculateSpecular(normal, (point_lights[p]).getLightVec(x, y, z), (point_lights[p]).getColor());
//         } else if(specular_method == 2){
//           rgbSpecular = calculateWardSpecular(normal, (point_lights[p]).getLightVec(x, y, z), (point_lights[p]).getColor());
//         }

//         glm::vec3 rgbAmbient = calculateAmbient((point_lights[p]).getColor());

//         r += rgbDiffusion.x + rgbSpecular.x + rgbAmbient.x;
//         g += rgbDiffusion.y + rgbSpecular.y + rgbAmbient.y;
//         b += rgbDiffusion.z + rgbSpecular.z + rgbAmbient.z;
//       }

//       r = min(1.0f, r);
//       g = min(1.0f, g);
//       b = min(1.0f, b);

//       setPixel(x, y, r, g, b);
//     }
//   }
// }

// void drawMultiSphere(){
//   drawSphere(1.0f * viewport.w / 5.0f, 2.0f * viewport.h / 5.0f, min(viewport.w, viewport.h) / 2.0f, unit_radius / 2.0f);
//   drawSphere(4.0f * viewport.w / 5.0f, 3.0f * viewport.h / 5.0f, min(viewport.w, viewport.h) / 2.0f, unit_radius / 4.0f);
//   drawSphere(1.5f * viewport.w / 5.0f, 3.5f * viewport.h / 5.0f, min(viewport.w, viewport.h) / 2.0f, unit_radius / 2.5f);
//   drawSphere(4.0f * viewport.w / 5.0f, 4.0f * viewport.h / 5.0f, min(viewport.w, viewport.h) / 2.0f, unit_radius / 3.3f);
//   drawSphere(4.0f * viewport.w / 5.0f, 1.0f * viewport.h / 5.0f, min(viewport.w, viewport.h) / 2.0f, unit_radius / 1.75f);
// }

// glm::vec3 getWaveNormal(float x, float y, float z){
//   //gradient method
//   return glm::normalize(glm::vec3(1/10 * cos(x/10) * cos(z/20), 0.0f, -1.0f/20 * sin(x/10) * sin(z/20)));
// }

// void drawWave(){
//   glBegin(GL_POINTS);

//   for(float x = 2.0f * viewport.w / 10.0f; x < 8.0f * viewport.w / 10.0f; x+=0.1f){
//     for(float z = 3.0f * viewport.w / 10.0f; z < 7.0f * viewport.w / 10.0f; z+=0.1f){
//       //coordinates of surface.
//       float y = (viewport.h * 0.3) * sin(x/10) * cos(z/20) + viewport.h / 2.0f;

//       //normal of surface
//       glm::vec3 normal = getWaveNormal(x, y, z);

//       //color components
//       float r = 0.0f;
//       float g = 0.0f;
//       float b = 0.0f;

//       for(int d = 0; d < num_dl; d++){
//         glm::vec3 rgbDiffusion = calculateDiffusion(normal, (dir_lights[d]).getReverseDirection(), (dir_lights[d]).getColor());

//         glm::vec3 rgbSpecular = glm::vec3(0.0f, 0.0f, 0.0f);

//         if(specular_method == 1){
//           rgbSpecular = calculateSpecular(normal, (dir_lights[d]).getReverseDirection(), (dir_lights[d]).getColor());
//         } else if(specular_method == 2){
//           rgbSpecular = calculateWardSpecular(normal, (dir_lights[d]).getReverseDirection(), (dir_lights[d]).getColor());
//         }

//         glm::vec3 rgbAmbient = calculateAmbient((dir_lights[d]).getColor());

//         r += rgbDiffusion.x + rgbSpecular.x + rgbAmbient.x;
//         g += rgbDiffusion.y + rgbSpecular.y + rgbAmbient.y;
//         b += rgbDiffusion.z + rgbSpecular.z + rgbAmbient.z;
//       }

//       for (int p = 0; p < num_pl; p++)
//       {
//         glm::vec3 rgbDiffusion = calculateDiffusion(normal, (point_lights[p]).getLightVec(x, y, z), (point_lights[p]).getColor());

//         glm::vec3 rgbSpecular = glm::vec3(0.0f, 0.0f, 0.0f);

//         if(specular_method == 1){
//           rgbSpecular = calculateSpecular(normal, (point_lights[p]).getLightVec(x, y, z), (point_lights[p]).getColor());
//         } else if(specular_method == 2){
//           rgbSpecular = calculateWardSpecular(normal, (point_lights[p]).getLightVec(x, y, z), (point_lights[p]).getColor());
//         }

//         glm::vec3 rgbAmbient = calculateAmbient((point_lights[p]).getColor());

//         r += rgbDiffusion.x + rgbSpecular.x + rgbAmbient.x;
//         g += rgbDiffusion.y + rgbSpecular.y + rgbAmbient.y;
//         b += rgbDiffusion.z + rgbSpecular.z + rgbAmbient.z;
//       }

//       r = min(1.0f, r);
//       g = min(1.0f, g);
//       b = min(1.0f, b);

//       // printf("%.3f\n", r);

//       setPixel(x, y, r, g, b);
//     }
//   }
// }

//****************************************************
// function that does the actual drawing of stuff
//***************************************************
void myDisplay() {
  glClear(GL_COLOR_BUFFER_BIT);				// clear the color buffer

  glMatrixMode(GL_MODELVIEW);			        // indicate we are specifying camera transformations
  glLoadIdentity();				        // make sure transformation is "zero'd"


  // Start drawing
  // if(is_wave){
  //   drawWave();
  // }else if(!is_multi){
  //   drawSphere(centerX, centerY, centerZ, unit_radius);  
  // } else{
  //   drawMultiSphere();
  // }
  

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
  // Initalize theviewport size
  viewport.w = 200;
  viewport.h = 200;

  Scene* scene = new Scene();
  TextReader* reader = new TextReader();

  reader->parse(scene, argv[1]);

  //This initializes glut
  glutInit(&argc, argv);

  //This tells glut to use a double-buffered window with red, green, and blue channels 
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

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