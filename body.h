#ifndef _body_
#define _body_
#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

class body {
  protected:
    //int id;//need this?
    long x;
    long y;
    long m;
    float velX;
    float velY;
    float accelX;
    float  accelY;

  public:
    body();
    body(istream &is);
    body(long nx, long ny, long nm);
    
    long getX() { return x; }
    long getY() { return y; }
    long getMass() { return m; }
    float getVel();
    float getAccel();
    
    long distX(long);
    long distY(long);
    long distance(long,long);
    
    void display();
    void move();
    void update();
    void setAccel(float,float);
    
};

#endif //_body_
