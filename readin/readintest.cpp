#include<iostream>
#include<fstream>
#include<iomanip>
#include<sstream>

using namespace std;

#include<vector>
#ifdef MACOSX
#include<GLUT/glut.h>
#else
#include<GL/glut.h>
#endif

#include<string.h>


//draws a rectangle, given coords of upper left corner, the width, the height
void drawBox(float x, float y, float width, float height)
{
  glBegin(GL_POLYGON);
    glVertex2f(x, y);  // upper left
    glVertex2f(x, y + height);  // lower left
    glVertex2f(x + width, y + height);  // lower right
    glVertex2f(x + width, y);  // upper right
  glEnd();
}

//calls drawBox function given a list of doubles.

void drawBox(float *pos)
{
  drawBox(pos[0], pos[1], pos[2], pos[3]);
}
