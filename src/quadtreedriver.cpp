#include <iostream>
#include "quadtree.h"
#include "elapsed_time.h"
#include <thread> 
#include "pthread_prep.c"
using namespace std;

int main(){


  pthread_mutex_init(&qlock,NULL);
  pthread_cond_init(&qEmpty,NULL);
  pthread_mutex_init(&qstep, NULL);
  pthread_cond_init (&nextstep,NULL);


  bodygroup bg(cin);
  int time_steps = 100;
  double avg_constr = 0;
  double avg_com = 0;
  double avg_comp = 0;

  thread thandle[8];



  /*This part is a little complex: basically
    we have to pass 3 things:
    1. The address method the thread is using as a function
    2. The identifier/object that the thread is performing it on.
    3+: Any Arguements used for the method.*/
  for(int j = 0; j < 8; ++j){
    thandle[j] = thread(&thread_function); //Address of method/function...
  }

  //Main Loop
  for(int i = 0; i < time_steps; i++){
    //bg.display();
    //cout << endl;
    
    cout << "step " << i << " complete." << endl;
    start_timer();
    q1.setTheta(1.5);
    q1.insert(&bg);
    avg_constr+=elapsed_time();
    cout << "quadtree built" << endl;
 
    start_timer();
    q1.calcCOM();
    avg_com += elapsed_time();
    cout << "CoM calc done" << endl;
    
    for(int i = 0; i < ((int)bg.getSize()); ++i){
      q_bodies.push(bg[i]);
    }
    start_timer(); 

    //Tell threads: "Go"
    pthread_cond_broadcast(&qEmpty);


  
    //Need to wait for the barnes hut to be done!
    pthread_mutex_lock(&qstep);
    while(!q_bodies.empty()){
      pthread_cond_wait(&nextstep,&qstep);
    }
    pthread_mutex_unlock(&qstep);
    //Wait for next step broadcast?




    cout << "barnes hut done" << endl;
    //once all accels are computed, then
    //we can update positions
    for(int j = 0; j < bg.getSize(); j++){
      bg[j]->update();
    }
    cout << "position update done" << endl;
    avg_comp += elapsed_time();
  
  bg.display();
}
  //Once timesteps are over: set global bool to
  //"end threads"
  endthreads = 1;
  pthread_cond_broadcast(&qEmpty);
  //Threads quickly destroyed
  for(int j = 0; j < bg.getSize(); ++j){
    thandle[j].join();
  }
  

  cout << "Average construction time: " << avg_constr/time_steps << endl;
  cout << "Average center of mass calculation time: " << avg_com/time_steps << endl;
  cout << "Average BH computations: " << avg_comp/time_steps << endl;
  pthread_mutex_destroy(&qlock);
  pthread_cond_destroy(&qEmpty);
  pthread_mutex_destroy(&qstep);
  pthread_cond_destroy(&nextstep);
  
  return 0;

}