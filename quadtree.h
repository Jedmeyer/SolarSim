#ifndef _quadtree_
#define _quadtree_
#include <iostream>
#include <fstream>
#include "bodygroup.h"
using namespace std;

class quadtree{
  protected:
    bool contains_body;
    body* contained;

    float theta;    

    quadtree** children;
    
    long double left, right;
    long double top, bottom;

  public:
    quadtree();//idk if this will actually be used;
    quadtree(long double l, long double r, long double t, long double b, body* c);
    quadtree(bodygroup*);
    ~quadtree();

    void insert(bodyi*);
    void insert(bodygroup*);

    long getLeft(){return left;}
    long getRight() {return right; }
    long getTop() { return top;}
    long getBottom() { return bottom; }

    float getTau() { return tau; }
    void setTau(float t) { tau = t; }

    bool isParent() { return contains_body; }

}
