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
    
    long double comX;
    long double comY;
    long double total_mass;
    long double* comVals;
    
    float theta;    

    quadtree** children;
    
    long double left, right;
    long double top, bottom;

  public:
    quadtree();
    quadtree(long double l, long double r, long double t, long double b, body* c);
    //quadtree(const bodygroup&);//not working and I dont think we'll need it.
    ~quadtree();

    void insert(body*);
    void insert(bodygroup*);

    long getLeft(){return left;}
    long getRight() {return right; }
    long getTop() { return top;}
    long getBottom() { return bottom; }

    float getTheta() { return theta; }
    void setTheta(float t) { theta = t; }

    long double getComX() { return comX; }
    long double getComY() { return comY; }
    long double getMass() { return total_mass; }
    void updateComVals();

    bool isParent() { return parent; }
    int whichChild(body*);
    quadtree* getChild(int index) { return children[index]; }

    long double* calcCOM();
    void clear();    
};
#endif //_quadtree_
