#include <iostream>
#include "bodygroup.h"

bodygroup::bodygroup(){
  comX = 0;
  comY = 0;
  //minX = minY = maxX= maxY = NULL;
  total_mass = 0;
  num_bodies=0;
  bodies = NULL;
}

bodygroup::bodygroup(istream& in){
  total_mass=0;
  in >> num_bodies;
  bodies=new body*[num_bodies];
  for(int i = 0; i < num_bodies; i++){
    bodies[i]=(new body(in));
    /*
    if((this->minX==NULL)||(this->bodies[i]->getX() < this->minX->getX()))
      this->minX = this->bodies[i];
    if((this->maxX==NULL)||(this->bodies[i]->getX() > this->maxX->getX()))
      this->maxX = this->bodies[i];
    if((this->minY==NULL)||(this->bodies[i]->getY() < this->minY->getY()))
      this->minY = this->bodies[i];
    if((this->maxY==NULL)||(this->bodies[i]->getY() > this->maxY->getY()))
      this->maxY = this->bodies[i];
    */
    total_mass+=bodies[i]->getMass();
  }
}

bodygroup::bodygroup(const bodygroup& rhs){
  (*this)=rhs;
}
bodygroup::~bodygroup(){
  this->clear();
}


void bodygroup::clear(){
  //cout << "the number of bodies is: " << this->num_bodies << endl;
  if(this->bodies == NULL)
    return;
  if(this->num_bodies < 1)
    return;
  //cout << this->num_bodies << endl;
  
  for(int i = 0; i < num_bodies; i++){
    //cout << i << endl;
    delete[] bodies[i];
  }
  //cout << "here" << endl;
  delete[] bodies;
  bodies = NULL;
  //minX = minY = maxX = maxY = NULL;
  num_bodies = 0;
  total_mass = 0;
  comX = comY = 0;
  //cout << "here" << endl;
}

void bodygroup::updateCoM(){
  int sumX = 0;
  int sumY = 0;
  for(int i = 0; i < num_bodies; i++){
    sumX+=bodies[i]->getMass()*bodies[i]->distX(0);
    sumY+=bodies[i]->getMass()*bodies[i]->distY(0);
  }
  comX = sumX/total_mass;
  comY = sumY/total_mass;
}

void bodygroup::display(){
  for(int i = 0; i < num_bodies; i++){
    bodies[i]->display();
  }
}

body* bodygroup::operator[] (int n) const{
  return bodies[n];
}

bodygroup& bodygroup::operator=(const bodygroup& b){
  if(this == &b)
    return (*this);

  //for some reason I'm getting an error here when deallocating memory
  //to rememdy this, I've made the equal operator private, and assume
  //that it will only be used by the copy constructor in which case
  //no deallocation is needed.
  //this->clear();
  num_bodies = b.getSize();
  bodies = new body*[num_bodies];
  for(int i = 0; i < num_bodies; i++){
    bodies[i] = new body(b[i]);
    /*
    if((this->minX==NULL)||(this->bodies[i]->getX() < this->minX->getX()))
      this->minX = this->bodies[i];
    if((this->maxX==NULL)||(this->bodies[i]->getX() > this->maxX->getX()))
      this->maxX = this->bodies[i];
    if((this->minY==NULL)||(this->bodies[i]->getY() < this->minY->getY()))
      this->minY = this->bodies[i];
    if((this->maxY==NULL)||(this->bodies[i]->getY() > this->maxY->getY()))
      this->maxY = this->bodies[i];
    */
    total_mass+=bodies[i]->getMass();
  }
  return (*this);
}
