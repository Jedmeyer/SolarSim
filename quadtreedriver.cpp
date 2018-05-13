#include <iostream>
#include "quadtree.h"
using namespace std;

int main(){
  
  bodygroup bg(cin);
  //cout << "Number of time steps: ";
  int time_steps = 100;
  //cin >> time_steps;
  for(int i = 0; i < time_steps; i++){
    quadtree q1;
    bg.display();
    cout << endl; 
    q1.insert(&bg);

    q1.calcCOM();
    //this is where we parallelize
    //update the acclerations of all bodies
    for(int i = 0; i < bg.getSize(); i++){
      q1.barnesHut(bg[i]);  
    }
    //once all accels are computed, then
    //we can update positions
    for(int i = 0; i < bg.getSize(); i++){
      bg[i]->update();
    }
  }
  bg.display();
  
  return 0;
}
