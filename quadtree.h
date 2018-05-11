#ifndef _quadtree_
#define _quadtree_
#include <iostream>
#include <fstream>
#include "bodygroup.h"
using namespace std;

class quadtree{
  protected:
    bool parent;
    body* contained;

    float theta;    

    quadtree** children;
    
    long double left, right;
    long double top, bottom;

  public:
    quadtree();
    quadtree(long double l, long double r, long double t, long double b, body* c);
    quadtree(bodygroup*);
    ~quadtree();

    void insert(body*);
    void insert(bodygroup*);

    long getLeft(){return left;}
    long getRight() {return right; }
    long getTop() { return top;}
    long getBottom() { return bottom; }

    float getTheta() { return tau; }
    void setTheta(float t) { theta = t; }

    bool isParent() { return parent; }
    int whichChild(body*);

    void clear();    
}
