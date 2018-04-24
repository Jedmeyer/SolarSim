#ifndef _bodygroup_
#define _bodygroup_
#include <iostream>
#include <ostream>
#include <fstream>

#include "body.h"

class bodygroup{
  private:
    vector<body> bodies;
    float comX;
    float comY;
    float total_mass;
    int num_bodies;

  public:
    bodygroup();
    bodygroup(body**,int);
    bodygroup(ostream&);
    
    float* getCOM();
    float get_num_bodies() { return num_bodies; }

    void updateCoM();
    void display();
    void insert(const body&);

    body operator[](int n);
        
};




#endif //_bodygroup_
