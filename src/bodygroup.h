#ifndef _bodygroup_
#define _bodygroup_
#include <iostream>
#include <ostream>
#include <fstream>

#include "body.h"

class bodygroup{
  private:
    body** bodies;
    long double comX;
    long double comY;
    long double total_mass;
    int num_bodies;
    /*
    body* minX;
    body* minY;
    body* maxX;
    body* maxY;
    */
    bodygroup& operator=(const bodygroup&);    

  public:
    bodygroup();
    bodygroup(const bodygroup&);
    bodygroup(istream&);
    ~bodygroup();    

    double getCOMX() const { return comX; } 
    double getCOMY() const{ return comY; } 
    double getSize() const { return num_bodies; }
    /*
    body* getMinX() { return minX; }
    body* getMinY() { return minY; }
    body* getMaxX() { return maxX; }
    body* getMaxY() { return maxY; }
    */   

    void clear();
    void updateCoM();
    void display();

    body* operator[] (int n) const;
};
#endif //_bodygroup_
