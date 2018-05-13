#include <iostream>
#include "quadtree.h"
#include "elapsed_time.h"
using namespace std;

int main(){
  

  bodygroup bg(cin);
  //cout << "Number of time steps: ";
  int time_steps = 100;
  //cin >> time_steps;
  
  double avg_constr = 0;
  double avg_com = 0;
  double avg_comp = 0;
  for(int i = 0; i < time_steps; i++){

    bg.display();
    cout << endl; 

    //cout << "getting to the end" << endl;
    start_timer();
    quadtree q1;
    q1.setTheta(1);
    q1.insert(&bg);
    avg_constr+=elapsed_time();
     
    start_timer();
    q1.calcCOM();
    avg_com += elapsed_time();
    //this is where we parallelize
    //update the acclerations of all bodies
    
    start_timer();
    for(int i = 0; i < bg.getSize(); i++){
      q1.barnesHut(bg[i]);  
    }
    //once all accels are computed, then
    //we can update positions
    for(int i = 0; i < bg.getSize(); i++){
      bg[i]->update();
    }
    avg_comp += elapsed_time();
  }
  bg.display();

  cout << "Average construction time: " << avg_constr/time_steps << endl;
  cout << "Average center of mass calculation time: " << avg_com/time_steps << endl;
  cout << "Average BH computations: " << avg_comp/time_steps << endl;

  
  return 0;
}
