#include <iostream>
#include "bodygroup.h"

bodygroup::bodygroup(){
  comX = 0;
  comY = 0;
  minX = minY = maxX= maxY = NULL;
  total_mass = 0;
  num_bodies=0;
  bodies = NULL;
}

bodygroup::bodygroup(ostream& in){
  total_mass=0;
  in >> num_bodies;
  bodies=new body*[num_bodies];
  for(int i = 0; i < num_bodies; i++){
    bodies[i]=(new body(in));
    
    if((this->minX==NULL)||(this->bodies[i]->getX() < this->minX->getX()))
      this->minX = this->bodies[i];
    if((this->maxX==NULL)||(this->bodies[i]->getX() > this->maxX->getX()))
      this->maxX = this->bodies[i];
    if((this->minY==NULL)||(this->bodies[i]->getY() < this->minY->getY()))
      this->minY = this->bodies[i];
    if((this->maxY==NULL)||(this->bodies[i]->getY() > this->maxY->getY()))
      this->maxY = this->bodies[i];
    
    total_mass+=bodies[i].getMass();
  }
}

bodygroup::bodygroup(const bodygroup& rhs){
  (*this) = rhs;
}

bodygroup::~bodygroup(){
  if(num_bodies < 1)
    return;
  for(int i = 0; i < num_bodies; i++){
    delete[] bodies[i];
  }
  delete[] bodies;
  bodies = NULL;
  minX = minY = maxX = maxY = NULL;
  num_bodies = 0;
  total_mass = 0;
  comX = comY = 0;
}

float* bodygroup::getCOM(){
  float com[2] = {comX,comY};
  return com;
}

void bodygroup::updateCoM(){
  int sumX = 0;
  int sumY = 0;
  for(int i = 0; i < num_bodies; i++){
    sumX+=bodies[i]->getMass()*bodies[i].distX(0);
    sumY+=bodies[i]->getMass()*bodies[i].distY(0);
  }
  comX = sumX/total_mass;
  comY = sumY/total_mass;
}

void bodygroup::display(){
  cout << "<--- bodygroup --->" << endl;
  for(int i = 0; i < num_bodies; i++){
    bodies[i]->display();
  }
  cout << "<--- end bodygroup --->" << endl;
}

body& operator[](int n){
  return bodies[i];
}
