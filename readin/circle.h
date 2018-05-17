#ifndef _Circle_
#define _Circle_
#include <iostream>
#include <fstream>

using namespace std;

class Circle {
 protected:
  float rad;
  long double xpos;
  long double ypos;
  long double velocity;
  int r;
  int g;
  int b;

 public:
  Circle();
  Circle(istream &is);

  void draw();
};

#endif //_Circle_
