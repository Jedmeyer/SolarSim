#ifndef _bodygroup_
#define _bodygroup_
#include <iostream>
#include <ostream>
#include <fstream>

#include "body.h"

class bodygroup{
  private:
    body** bodies;
    float comX;
    float comY;
    float total_mass;
    int num_bodies;

    body* minX, minY, maxX, maxY;

  public:
    bodygroup();
    bodygroup(const bodygroup& rhs);
    bodygroup(ostream&);
    ~bodygroup();    

    float* getCOM();
    float getSize() { return num_bodies; }

    void updateCoM();
    void display();

    body& operator[](int n);
        
};




#endif //_bodygroup_
