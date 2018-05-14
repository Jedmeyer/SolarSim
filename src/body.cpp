#include <iostream>
#include "body.h"
using namespace std;

body::body(){
  x = y = m = velX = velY = accelX = accelY = 0; 
}

body::body(istream &is) {//assuming no starting acceleration
  is >> x >> y >> m >> velX >> velY;
  accelX = 0;
  accelY = 0;
}

body::body(const body* b){
  x = b->getX();
  y = b->getY();
  m = b->getMass();
  velX = b->getVelX();
  velY = b->getVelY();
  accelX = b->getAccelX();
  accelY = b->getAccelY();
}

body::body(long double nx, long double ny, long double nm) {
  x = nx;
  y = ny;
  m = nm;  
  velX = 0;
  velY = 0;
  accelX = 0;
  accelY = 0;
}

long double body::distX(long double xpos){
  return (abs((long double)xpos - x));
}

long double body::distY(long double ypos){
  return (abs((long double)ypos - y));
}

long double body::distance(long double nx, long double ny){
  long double val1 = nx - x;
  long double val2 = ny -y;
  return ((long double) sqrt((long double)val1*val1 + val2*val2));
}

long double body::distance(const body* b){
  long double xdiff = abs(b->getX() - x);
  long double ydiff = abs(b->getY() - y);
  return (sqrt(xdiff*xdiff + ydiff*ydiff));
}

void body::display() {
  cout << "(x,y)= (" << x << "," << y << ")"<<endl;
  cout << "mass = " << m << endl;
  cout << "(dx,dy)= (" << velX << "," << velY << ")"<<endl;
  cout << endl;
}

void body::update() {
  x += velX; 
  y += velY;
  velX += accelX;
  velY += accelY;
  accelX = 0;
  accelY = 0;
}

void body::setAccel(long double ax, long double ay){
  accelX = ax;
  accelY = ay;
}

void body::gravity(body* b){
  long double r = distance(b);
  if(r == 0){
    r = 0.01;
  }
  long double a = G * b->getMass() / (r*r);

  //I believe this subtraction is in the correct order.
  //However, with weird behavior check this.
  long double xdiff = b->getX() - x;
  long double ydiff = b->getY() - y;

  long double ax = a*xdiff/r;
  long double ay = a*ydiff/r;
  
  accelX += ax;
  accelY += ay;
}

void body::setPos(long double xpos, long double ypos){
  x = xpos;
  y = ypos;
}

void body::setMass(long double nm){
  m = nm;
}
