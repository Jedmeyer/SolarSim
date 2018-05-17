#ifndef _Shape_
#define _Shape_
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

struct Vec {
  double x, y;
  Vec(){
    x = y = 0;
  }
  Vec(double x0, double y0){
    x = x0;
    y = y0;
  }
  Vec(const Vec &v){
    x = v.x;
    y = v.y;
  }
  Vec(istream &is){
    is >> x;
    is >> y;
  }
  void display(){
    cout << x << " " << y << endl;
  }
};


class Shape{
 protected:
  Color color;
  Vec position;
 public:
  Shape();
  Shape(Vec p);
  Shape(Vec p, Color c);
  Shape(istream &is);

  Color getColor() { return color; }
  Vec getPosition() {return position; }
  
  void setColor(Color c);
  void setColor(float r, float g, float b);
  void setPosition(int x, int y);
  void setPosition(Vec P);

  void sendGlColor();
  
  void display();

  
  virtual void draw() = 0;
  virtual void update(int, int) = 0;
  virtual bool containsPoint(int, int) = 0;

};

#endif //_Shape_
