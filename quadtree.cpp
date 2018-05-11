#include <iostream>
#include "quadtree.h"
using namespace std;

quadtree::quadtree(){
  theta = 1;
  parent  = false;
  contained = NULL;
  children = NULL;
  left = 0; right = 1920;
  top = 1080; bottom = 0;
}

quadtree::quadtree(long double l, long double r, long double t, long double b, body* c):
  left(l), right(r), top(t), bottom(b)
{
  parent = false;
  children = NULL;
  theta = 1;
  containted = c;
}

quadtree::quadtree(bodygroup* g){
  if(g->getSize()==0)
    return;
  if(g==NULL)
    return;
  parent = false; //this will be changed to true in the insert cycle
  
  left = g->getMinX()->getX();
  right = g->getMinY()->getY();
  top = g->getMaxX()->getX();
  bottom = g->getMaxY()->getY();

  insert(g);
}

quadtree::~quadtree(){
  clear();
}

quadtree::clear(){
  parent = false;
  contained = NULL;

  if(chilren==NULL)
    return;
  
  for(int i = 0; i < 4; i++){
    if(children[i]==NULL)
      continue;
    delete children[i];
    children[i] = NULL;
  } 
}

void quadtree::insert(body* i){
  if(parent){
    this->children[whichChild(i)].insert(i);
  }
 
  else if(!parent && contained!=NULL){
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
    this->children[whichChild(contained)].insert(contained);
    contained = NULL;
    children[whichChild(i)].insert(i);
  } 

  else if(!parent && contained == NULL){
    contained = i;
  }
}

void quadtree::insert(bodygroup* g){
  for(int i = 0; i < g.getSize(); i++)
    this->insert(g[i]);  
}

int quadtree::whichChild(body* b){
  long double xVal = b->getX();
  long double yVal - b->getY();
  
  long double midX = (left + right)/2.0;
  long double midY = (top + bottom)/2.0;

  if(xVal > midX && yVal > midY)
    return 0;
  else if(xVal < midX && yVal > midY)
    return 1;
  else if(xVal < midX && yVal < midY)
    return 2;
  else if(xVal > midX && yVal < midY)
    return 3;
}
