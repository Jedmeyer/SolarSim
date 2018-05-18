#include "circle.h"
#include <GL/glut.h>
#include <math.h>
using namespace std;

void Circle::sendGLColor() {
  glColor3f(r/255., g/255., b/255.);
}

void Circle::draw() {
  const float PI = 3.14159265358979f;
  sendGLColor();
  const int NUM_DIVS = 20;
  glBegin(GL_TRIANGLE_FAN);
  glVertex2d(xpos, ypos);
  for (int i = 0; i<NUM_DIVS; ++i)
        glVertex2d(xpos + rad*cos(i*2*PI/(NUM_DIVS-1)), ypos + rad*sin(i*2*PI/(NUM_DIVS-1)));
  glEnd();
}

//default constructor
Circle::Circle(){
  xpos = 0;
  ypos = 0;
  rad = 30;
  r = 255;
  g = 0;
  b = 255;
}

Circle::Circle(istream &is){
  rad = 2;
  is >> xpos;
  is >> ypos;
  r = 255;
  g = 255;
  b = 255;
  is >> velocity;
  g = velocity*10;
}
