#include <iostream>
#include "quadtree.h"
#include "elapsed_time.h"
using namespace std;

int main(){
  
  bodygroup bg(cin);
  int time_steps = 10;
  double avg_constr = 0;
  double avg_com = 0;
  double avg_comp = 0;
  
  for(int i = 0; i < time_steps; i++){
    //bg.display();
    //cout << endl;
    
    cout << "step " << i << " complete." << endl;
    start_timer();
    quadtree q1;
    q1.setTheta(1.5);
    q1.insert(&bg);
    avg_constr+=elapsed_time();
    cout << "quadtree built" << endl;
 
    start_timer();
    q1.calcCOM();
    avg_com += elapsed_time();
    cout << "CoM calc done" << endl;
    
    //this is where we parallelize
    //update the acclerations of all bodies
    start_timer();
    for(int j = 0; j < bg.getSize(); j++){
      q1.barnesHut(bg[j]);  
    }
    cout << "barnes hut done" << endl;
    //once all accels are computed, then
    //we can update positions
    for(int j = 0; j < bg.getSize(); j++){
      bg[j]->update();
    }
    cout << "position update done" << endl;
    avg_comp += elapsed_time();
  }
  //bg.display();

  cout << "Average construction time: " << avg_constr/time_steps << endl;
  cout << "Average center of mass calculation time: " << avg_com/time_steps << endl;
  cout << "Average BH computations: " << avg_comp/time_steps << endl;

  
  return 0;
}
