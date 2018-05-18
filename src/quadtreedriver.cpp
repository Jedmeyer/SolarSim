#include <iostream>
#include "quadtree.h"
#include "elapsed_time.h"
#include <thread> 
#include "pthread_prep.c"

#define NUMTHREADS 4

using namespace std;

int main(){


  pthread_mutex_init(&qlock,NULL);
  pthread_cond_init(&qEmpty,NULL);
  pthread_mutex_init(&qstep, NULL);
  pthread_cond_init (&nextstep,NULL);

  long double dim = 0;
  cin >> dim;



  bodygroup bg(cin);
  int time_steps = 1000000;
  double avg_constr = 0;
  double avg_com = 0;
  double avg_comp = 0;

  thread thandle[20]; //Max 20 threads


  /*This part is a little complex: basically
    we have to pass 3 things:
    1. The address method the thread is using as a function
    2. The identifier/object that the thread is performing it on.
    3+: Any Arguements used for the method.*/
  cout << time_steps << endl << bg.getSize() << endl;
  for(int j = 0; j < NUMTHREADS; ++j){
    thandle[j] = thread(&thread_function); //Address of method/function...
  }

  //Main Loop
  for(int i = 0; i < time_steps; i++){
    bg.display();
    //cout << endl;
    
    //cout << "step " << i << " complete." << endl;
    start_timer();
    q1.setTheta(1.5);
    q1.insert(&bg);
    avg_constr+=elapsed_time();
    //cout << "quadtree built" << endl;
 
    start_timer();
    q1.calcCOM();
    avg_com += elapsed_time();
    //cout << "CoM calc done" << endl;
    


    //No adding to the Q on lock!
    for(int i = 0; i < ((int)bg.getSize()); ++i){
      pthread_mutex_lock(&qlock);
      q_bodies.push(bg[i]);
      pthread_mutex_unlock(&qlock);
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




    //once all accels are computed, then
    //we can update positions
    for(int j = 0; j < bg.getSize(); j++){
      bg[j]->update();
    }
    //cout << "position update done" << endl;
    avg_comp += elapsed_time();
  
  bg.display();
}
  //Once timesteps are over: set global bool to
  //"end threads"
  endthreads = 1;
  pthread_cond_broadcast(&qEmpty);

  //Threads quickly destroyed
  for(int j = 0; j < NUMTHREADS; ++j){
    thandle[j].join();
  }
  

  pthread_mutex_destroy(&qlock);
  pthread_cond_destroy(&qEmpty);
  pthread_mutex_destroy(&qstep);
  pthread_cond_destroy(&nextstep);
  
  return 0;

}
