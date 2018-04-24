#include <iostream>
using namespace std;

body::body(){
  x = y = m = velX = velY = accelX = accelY = 0; 
}

body::body(istream &is) {
  is >> x >> y >> m >> velX >> velX >> accelX >> accelY;
}

body::body(long nx, long ny, long nm) {
  x = nx;
  y = ny;
  m = nm;
  
}

long* body::getVel(){
  float vel[2] = {velX, velY};
  return vel;
}

long* body::getAccel(){
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
  return (sqrt(val1*val1 + val2*val2);
}

void body::display() {
  cout << "(x,y)= (" << x << "," << y << ")"<<endl;
  cout << "mass = " << m << endl;
  cout << "(dx,dy)= (" << dx << "," << dy << ")"<<endl;
}

void body::move() {
  x+=dx;
  y+=dy;
}
i
void body::update() {
  dx = accelX;
  dy = accelY;
}

void setAccel(float ax, float ay){
  accelX = ax;
  accelY = ay;
}
