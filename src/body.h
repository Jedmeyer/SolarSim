#ifndef _body_
#define _body_
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

#define G 6.673*pow(10,-10)

class body {
  protected:
    long double x;
    long double y;
    long double m;
    long double velX;
    long double velY;
    long double accelX;
    long double accelY;

  public:
    body();
    body(istream &is);
    body(const body*);
    body(long double nx, long double ny, long double nm);
    
    long double getX() const { return x; }
    long double getY() const { return y; }
    long double getMass() const{ return m; }
    long double getVelX() const {return velX; }
    long double getVelY() const {return velY; }
    long double getAccelX() const { return accelX; }
    long double getAccelY() const { return accelY; }
    
    long double distX(long double );
    long double distY(long double);
    long double distance(long double ,long double);
    long double distance(const body*);   
 
    void display();
    void update();
    void setAccel(long double, long double);
    void setPos(long double, long double);
    void setMass(long double nm);
    void gravity(body*); 
};

#endif //_body_
