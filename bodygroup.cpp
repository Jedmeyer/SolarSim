#include <iostream>
#include "bodygroup.h"

bodygroup::bodygroup(){
  comX = NULL;
  comY = NULL;
  total_mass = 0;
  num_bodies=0;
}

bodygroup::bodygroup(ostream& in){
  in >> num_bodies;
  for(int i = 0; i < num_bodies; i++){
    bodies.push_back(new body(in));
    total_mass+=bodies[i].getMass();
  }
}

bodygroup::bodygroup(body** b, int n){
  total_mass = 0;
  num_bodies = n;
  for(int i = 0; i < n; i++){
    bodies.push_back(*b[i]);
    total_mass += *b[i].getMass();
  }
}

float* bodygroup::getCOM(){
  float com[2] = {comX,comY};
  return com;
}

void bodygroup::updateCoM(){
  int sumX = 0;
  int sumY = 0;
  for(int i = 0; i < num_bodies; i++){
    sumX+=bodies[i].getMass()*bodies[i].distX(0);
    sumY+=bodies[i].getMass()*bodies[i].distY(0);
  }
  comX = sumX/total_mass;
  comY = sumY/total_mass;
}

void bodygroup::display(){
  for(int i = 0; i < num_bodies; i++){
    cout << "<--- bodygroup --->" << endl;
    bodies[i].display();
    cout << "<--- end bodygroup --->" << endl;
  }
}

void bodygroup::insert(const body& b){
  num_bodies++;
  body* nb = b;
  total_mass+=nb->getMass();
  bodies.push_back(*b);
}

body& operator[](int n){
  return bodies[i];
}
