#ifndef _body_
#define _body_
#include <iostream>
#include <fstream>
using namespace std;

class body {
  protected:
    long x;
    long y;
    long m;
    float dx;
    float dy;

  public:
    body();
    body(istream &is);
    body(int x, int y, int m);
    
    long getX() { return x; }
    long getY() { return y; }
    
    void display();
    void move();
    void update(float x, float y);
    
};

#endif //_body_
