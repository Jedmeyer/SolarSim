#include <iostream>
#include "body.h"
using namespace std;

body::body(){
  x = y = m = velX = velY = accelX = accelY = 0; 
}

body::body(istream &is) {
  is >> x >> y >> m >> velX >> velY >> accelX >> accelY;
}

body::body(const body* b){
  x = b->getX();
  y = b->getY();
  m = b->getMass();
  velX = b->getVel()[0];
  velY = b->getVel()[1];
  accelX = b->getAccel()[0];
  accelY = b->getAccel()[1];
}

body::body(long nx, long ny, long nm) {
  x = nx;
  y = ny;
  m = nm;
  
}

float* body::getVel(){
  float vel[2] = {velX, velY};
  return vel;
}

float* body::getAccel(){
  float accel[2] = {accelX, accelY};
  return accel;
}

long body::distX(long xpos){
  return abs(xpos - x);
}

long body::distY(long ypos){
  return abs(ypos - y);
}

long body::distance(long nx, long ny){
  int val1 = nx - x;
  int val2 = ny -y;
  return (sqrt(val1*val1 + val2*val2));
}

void body::display() {
  cout << "(x,y)= (" << x << "," << y << ")"<<endl;
  cout << "mass = " << m << endl;
  cout << "(dx,dy)= (" << velX << "," << velY << ")"<<endl;
}

void body::update() {
  x+=velX; 
  y+=velY;
  velX+= accelX;
  velY+= accelY;
}

void body::setAccel(float ax, float ay){
  accelX = ax;
  accelY = ay;
}

void body::gravity(body b){
  float a1x = G * b.getMass() / distX(b.getX());
  float a1y = G * b.getMass() / distY(b.getY());

  setAccel(a1x,a1y); 
}
