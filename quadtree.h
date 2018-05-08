#ifndef _quadtree_
#define _quadtree_
#include <iostream>
#include <fstream>
#include "bodygroup.h"
using namespace std;

class quadtree{
  protected:
    bool contains_body;
    quadtree* children;
    quadtree* parent;
    long left;
    long right;
    long top;
    long bottom;

  public:
    quadtree();
    quadtree(bodygroup);

    void insert(body);
    void insert(bodygroup);

    long getLeft(){return left;}
    long getRight() {return right; }
    long getTop() { return top;}
    long getBottom() { return bottom; }
}
