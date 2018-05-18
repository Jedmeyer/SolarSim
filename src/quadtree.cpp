#include <iostream>
#include "quadtree.h"
using namespace std;

quadtree::quadtree(){
  theta = 1;
  parent  = false;
  contained = NULL;
  children = NULL;
  left = 0; right = 100000;
  top = 100000; bottom = 0;
}

quadtree::quadtree(long double l, long double r, long double t, long double b, body* c):
  left(l), right(r), top(t), bottom(b)
{
  parent = false;
  children = NULL;
  theta = 1;
  contained = c;
}

quadtree::~quadtree(){
  //Memory Leak here. We don't destruct the quadtree. Clear() is not defined, but declared!
  
    this->clear();


}

void quadtree::clear(){
  parent = false;
  contained = NULL;

  if(children==NULL)
    return;
  
  for(int i = 0; i < 4; i++){
    if(children[i]==NULL)
      continue;
    delete children[i];
    children[i] = NULL;
  }
  delete[] comVals; 
}

//currently this only works when the windows is the default size of 1080 x 1080
bool quadtree::outOfBounds(body* i){
  if(i->getX() > 1080 || i->getX() < 0 || i->getY() > 1080 || i->getY() < 0)
    return true;

  return false;
}

void quadtree::insert(body* i){
  //cout << "quadrant: " << whichChild(i) << endl;
  //cout << "dims: " << left << " " << right << " " << bottom << " " << top << endl;
  /*cout << "contained: " << endl;
  if(contained != NULL){
    cout << contained << endl;
    contained->display();
  }
  cout << "inserting: " << endl << i << endl;
  i->display();
  */
  if(outOfBounds(i))
    return;
  if(contained != NULL) { 
    if(i->getX() == contained->getX() && i->getY() == contained->getY()){
      return;
    }
  }  

  if(parent){
    //cout << "is parent" << endl;
    this->children[whichChild(i)]->insert(i);
  }
   
  else if(!parent && contained!=NULL){
    /*if((abs(contained->getX() - i->getX()) < 1) && (abs(contained->getY() - i->getY()) < 1)){
      i->setPos(i->getX()+1, i->getY()+1);
      cout << "calling if" << endl;
    }*/
    //cout << "not parent and something inside" << endl;
    this->children = new quadtree*[4];
    long double midX = (this->left + this->right)/2.0;
    long double midY = (this->top + this->bottom)/2.0;
    this->children[0] = new quadtree(midX,right,top,midY,NULL);
    this->children[0]->setTheta(theta);
    this->children[1] = new quadtree(left,midX,top,midY,NULL);
    this->children[1]->setTheta(theta);
    this->children[2] = new quadtree(left,midX,midY,bottom,NULL);
    this->children[2]->setTheta(theta);
    this->children[3] = new quadtree(midX,right,midY,bottom,NULL);
    this->children[3]->setTheta(theta);
    parent = true;
    children[whichChild(contained)]->insert(contained);
    contained = NULL;
    //cout << "inserted child" << endl;
    children[whichChild(i)]->insert(i);//getting stuck in a loop where this calls the original even though they're not close
    //try printing zone dims.
    //cout << "inserted incoming node" << endl;
    return;
  } 

  else if(!parent && contained == NULL){
    //cout << "not parent and nothing inside" << endl;
    contained = i;
    return;
  }
}

void quadtree::insert(bodygroup* g){
  for(int i = 0; i < g->getSize(); i++){
    //cout << "insert_i=" << i << endl;
    this->insert((*g)[i]);  
  }
}

int quadtree::whichChild(body* b){
  long double xVal = b->getX();
  long double yVal = b->getY();
  
  long double midX = (left + right)/2.0;
  long double midY = (top + bottom)/2.0;

  if(xVal >= midX && yVal >= midY)
    return 0;
  else if(xVal <= midX && yVal >= midY)
    return 1;
  else if(xVal <= midX && yVal <= midY)
    return 2;
  else if(xVal >= midX && yVal <= midY)
    return 3;
  cout << endl;  
  b->display(); 
  cout << "whichChild returning -1" << endl;
  //if none of the if conditions have been called, something is wrong
  //so we want to return something that will generate a recognizable error.
  return -1;
 
}

void quadtree::updateComVals(){
  comVals = new long double[3];
  comVals[0] = comX; 
  comVals[1] = comY; 
  comVals[2] = total_mass;
}

long double* quadtree::calcCOM(){
  total_mass = 0;
  if(!parent && contained != NULL){
    comX = contained->getX();
    comY = contained->getY();
    total_mass = contained->getMass();
  }
  else if(parent){
    long double** recur = new long double*[4];
    long double xTot = 0;
    long double yTot = 0;
    //I think this should work. However, with unexpected behavior,
    //consider the fact that distance values may have to be reset
    //based on the zones border values.
    for(int i = 0; i < 4; i++){
      recur[i] = children[i]->calcCOM();
      xTot += recur[i][0]*recur[i][2];
      yTot += recur[i][1]*recur[i][2];
      total_mass += recur[i][2]; 
    }
    comX = xTot/total_mass;
    comY = yTot/total_mass;
    delete[] recur;
  }
  updateComVals();
  return comVals;
}

void quadtree::barnesHut(body* b){
  if(contained == b)
    return;
  if(!parent && contained!=NULL){
    b->gravity(contained);
    return;
  }
  else if(getDim()/b->distance(comX,comY) < theta){
    body temp(comX,comY,total_mass);
    b->gravity(&temp);//acceleration is now updated 
    return;
  }
  else {
    for(int zone = 0; zone < 4; zone++){
      if(!children[zone]->empty())
        children[zone]->barnesHut(b);
    }
    return;
  }
}
