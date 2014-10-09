// CS184 Simple OpenGL Example
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>

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

#ifdef _WIN32
static DWORD lastTime;
#else
static struct timeval lastTime;
#endif

#define PI 3.14159265

using namespace std;

//****************************************************
// Some Classes
//****************************************************
class Viewport {
  public:
    int w, h; // width and height
};


//****************************************************
// Global Variables
//****************************************************
Viewport    viewport;

//****************************************************
// reshape viewport if the window is resized
//****************************************************
void myReshape(int w, int h) {
  viewport.w = w;
  viewport.h = h;

  glViewport(0,0,viewport.w,viewport.h);// sets the rectangle that will be the window
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();                // loading the identity matrix for the screen

  //----------- setting the projection -------------------------
  // glOrtho sets left, right, bottom, top, zNear, zFar of the chord system


  // glOrtho(-1, 1 + (w-400)/200.0 , -1 -(h-400)/200.0, 1, 1, -1); // resize type = add
  // glOrtho(-w/400.0, w/400.0, -h/400.0, h/400.0, 1, -1); // resize type = center

  glOrtho(-1, 1, -1, 1, 1, -1);    // resize type = stretch

  //------------------------------------------------------------
}


//****************************************************
// sets the window up
//****************************************************
void initScene(){
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Clear to black, fully transparent

  myReshape(viewport.w,viewport.h);
}

void drawRing(float start, float end, float radius, float width){
  glColor3f(1.0f,1.0f,1.0f);

  glBegin(GL_LINE_LOOP);

  // draw inner
  for (float i = start; i < end; i+=0.05f)
  {
    glVertex3f(cos(i * PI / 180) * radius, sin(i * PI / 180) * radius, 0.0f);
  }

  // draw outer
  for (float i = end; i > start; i-=0.05f)
  {
    glVertex3f(cos(i * PI / 180) * (radius + width), sin(i * PI / 180) * (radius + width), 0.0f);
  }

  glEnd();
}

void drawCircle(float radius, float r, float g, float b){
  glColor3f(r,g,b);

  glBegin(GL_POLYGON);

  // draw inner
  for (float i = 0; i < 360.0f; i+=0.05f)
  {
    glVertex3f(cos(i * PI / 180) * radius, sin(i * PI / 180) * radius, 0.0f);
  }

  glEnd();
}

void drawCrossRing(float radius, float phi, float theta_start, float theta_end, float width){
  glColor3f(1.0f,1.0f,1.0f);

  glBegin(GL_LINE_LOOP);

  // draw inner
  for (float i = theta_start; i < theta_end; i+=0.05f)
  {
    glVertex3f(cos(phi * PI / 180) * sin(i * PI / 180) * radius, sin(phi * PI / 180) * sin(i * PI / 180) * radius, radius * cos(i * PI / 180));
  }

  // draw outer
  for (float i = theta_end; i > theta_start; i-=0.05f)
  {
    glVertex3f(cos((phi + 5) * PI / 180) * sin((i + 5) * PI / 180) * (radius), sin((phi + 5) * PI / 180) * sin((i + 5) * PI / 180) * (radius), (radius) * cos(i * PI / 180));
  }

  glEnd();
}

//***************************************************
// function that does the actual drawing
//***************************************************
void myDisplay() {


  //----------------------- ----------------------- -----------------------
  // This is a quick hack to add a little bit of animation.
  // static float tip = 0.5f;
  // const  float stp = 0.0001f;
  // const  float beg = 0.1f;
  // const  float end = 0.9f;

  // tip += stp;
  // if (tip>end) tip = beg;
  // //----------------------- ----------------------- -----------------------


  glClear(GL_COLOR_BUFFER_BIT);                // clear the color buffer (sets everything to black)

  glMatrixMode(GL_MODELVIEW);                  // indicate we are specifying camera transformations
  glLoadIdentity();                            // make sure transformation is "zero'd"

  // //----------------------- code to draw objects --------------------------
  // // Rectangle Code
  // //glColor3f(red component, green component, blue component);
  // glColor3f(1.0f,0.0f,0.0f);                   // setting the color to pure red 90% for the rect

  // glBegin(GL_POLYGON);                         // draw rectangle 
  // //glVertex3f(x val, y val, z val (won't change the point because of the projection type));
  // glVertex3f(-0.8f, 0.0f, 0.0f);               // bottom left corner of rectangle
  // glVertex3f(-0.8f, 0.5f, 0.0f);               // top left corner of rectangle
  // glVertex3f( 0.0f, 0.5f, 0.0f);               // top right corner of rectangle
  // glVertex3f( 0.0f, 0.0f, 0.0f);               // bottom right corner of rectangle
  // glEnd();
  // // Triangle Code
  // glColor3f(1.0f,0.5f,0.0f);                   // setting the color to orange for the triangle

  // float basey = -sqrt(0.48f);                  // height of triangle = sqrt(.8^2-.4^2)
  // glBegin(GL_POLYGON);
  // glVertex3f(tip,  0.0f, 0.0f);                // top tip of triangle
  // glVertex3f(0.1f, basey, 0.0f);               // lower left corner of triangle
  // glVertex3f(0.9f, basey, 0.0f);               // lower right corner of triangle
  // glEnd();

  static float start1 = 20.0f;
  static float start2 = 110.0f;
  static float start3 = 290.0f;
  static float start4 = 235.0f;
  static float start5 = 355.0f;

  static float startx1 = 10.0f;
  static float startx2 = 100.0f;
  static float startx3 = 190.0f;
  static float startx4 = 280.0f;

  const float stp1 = 0.8f;
  const float stp2 = -1.2f;
  const float stp3 = 1.0f;
  const float stp4 = 2.0f;
  const float stp5 = -2.4f;

  const float stpx = 2.0f;

  start1 += stp1;
  start2 += stp2;
  start3 += stp3;
  start4 += stp4;
  start5 += stp5;

  startx1 += stpx;
  startx2 += stpx;
  startx3 += stpx;
  startx4 += stpx;

  start1 = fmod(start1, 360);
  start2 = fmod(start2, 360);
  start3 = fmod(start3, 360);
  start4 = fmod(start4, 360);
  start5 = fmod(start5, 360);

  startx1 = fmod(startx1, 360);
  startx2 = fmod(startx2, 360);
  startx3 = fmod(startx3, 360);
  startx4 = fmod(startx4, 360);

  drawRing(start1, start1 + 130, 0.65f, 0.05f);
  drawRing(start2, start2 + 255, 0.55f, 0.05f);
  drawRing(start3, start3 + 150, .45f, 0.05f);
  drawRing(start4, start4 + 85, .35f, 0.05f);
  drawRing(start5, start5 + 300, 0.25f, 0.05f);

  drawCircle(0.2f, 1, 1, 1);
  drawCircle(0.05f, 0, 0, 0);

  drawCrossRing(0.75f, 45, startx1, startx1 + 70, 0.05f);
  drawCrossRing(0.75f, 135, startx2, startx2 + 70, 0.05f);
  drawCrossRing(0.75f, 225, startx3, startx3 + 70, 0.05f);
  drawCrossRing(0.75f, 315, startx4, startx4 + 70, 0.05f);
  //-----------------------------------------------------------------------

  glFlush();
  glutSwapBuffers();                           // swap buffers (we earlier set double buffer)
}


//****************************************************
// called by glut when there are no messages to handle
//****************************************************
void myFrameMove() {
  //nothing here for now
#ifdef _WIN32
  Sleep(10);                                   //give ~10ms back to OS (so as not to waste the CPU)
#endif
  glutPostRedisplay(); // forces glut to call the display function (myDisplay())
}


//****************************************************
// the usual stuff, nothing exciting here
//****************************************************
int main(int argc, char *argv[]) {
  //This initializes glut
  glutInit(&argc, argv);

  //This tells glut to use a double-buffered window with red, green, and blue channels 
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

  // Initalize theviewport size
  viewport.w = 400;
  viewport.h = 400;

  //The size and position of the window
  glutInitWindowSize(viewport.w, viewport.h);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("CS184!");

  initScene();                                 // quick function to set up scene

  glutDisplayFunc(myDisplay);                  // function to run when its time to draw something
  glutReshapeFunc(myReshape);                  // function to run when the window gets resized
  glutIdleFunc(myFrameMove);                   // function to run when not handling any other task
  glutMainLoop();                              // infinite loop that will keep drawing and resizing and whatever else

  return 0;
}








