#include <iostream>
#include "quadtree.h"
#include "elapsed_time.h"
#include <thread> 
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
    q1.setTheta(1);
    q1.insert(&bg);
    avg_constr+=elapsed_time();
    cout << "quadtree built" << endl;
 
    start_timer();
    q1.calcCOM();
    avg_com += elapsed_time();
    cout << "CoM calc done" << endl;
    
    //this is where we parallelize
    //update the acclerations of all bodies
    
    //Thread container t
    thread t[(int)bg.getSize()];


    //LAUNCH?! I SAID LUNCH not LAUNCH!
    //tl dr; Launch the THREADS (NUKES)
    
    start_timer();

    /*this part is a little complex: basically
    we have to pass 3 things:
    1. The method the thread is using as a function
    2. The identifier/object that the thread is performing it on.
    3+: Any Arguements used for the method.*/
    for(int j = 0; j < bg.getSize(); ++j){
      t[j] = thread(&quadtree::barnesHut, //Address of Method...
                            &q1, //Object
                            bg[j]); //Method's arguement 1.
    }

    //Threads quickly destroyed
    //Reserved only for barnesHut
    for(int j = 0; j < bg.getSize(); ++j){
      t[j].join();
    }

    //Threads not longer in use.

    cout << "barnes hut done" << endl;
    //once all accels are computed, then
    //we can update positions
    for(int j = 0; j < bg.getSize(); j++){
      bg[j]->update();
    }
    cout << "position update done" << endl;
    avg_comp += elapsed_time();
  }
  bg.display();

  cout << "Average construction time: " << avg_constr/time_steps << endl;
  cout << "Average center of mass calculation time: " << avg_com/time_steps << endl;
  cout << "Average BH computations: " << avg_comp/time_steps << endl;

  
  return 0;
}
