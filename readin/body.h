#ifndef _Body_
#define _Body_
#include <iostream>
#include <fstream>
using namespace std;

struct Color {
  float r, g, b;

  Color(float a, float c, float d) {
    r = a;
    g=c;
    b=d;
  }

  Color() {
    r = g = b = 254.;
  }

  Color(const Color &c) {
    r = c.r;
    g = c.g;
    b = c.b;
  }

  void display()
  {     
    cout << r << " " << g << " " << b << endl;
  }
};

