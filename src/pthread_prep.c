#include <stdlib.h>
#include <stdio.h>
#include "body.h"
#include "quadtree.h"
#include <pthread.h>
#include <queue>



quadtree q1;

queue<body*> q_bodies;  
int endthreads = 0;

pthread_mutex_t qlock;

pthread_cond_t qEmpty;

pthread_mutex_t qstep;

pthread_cond_t nextstep;
//Jason's stuff for writing pthreads to process queue. 
//Note this will be written in C, but should work not problem in C++. "SHOULD".




void thread_function(){
	/*
	//PsudoCode for Handling multiple threads!
	//while(!q_bodies.empty()){
		body *b;
		//Need a queue of all bodies that is regenerated each timestep
		lock(qlock);
		b = q_bodies.top();
		q_bodies.pop();
		unlock(qlock);
	}
	if(curtimesteps < tottimesteps){
		thread wait.
		

	}
	}




*/
	while(1){

		//Initialize body *b, which will be passed to barnes hut.
		body *b = NULL;

		if(endthreads){
			return;
		}

		//Locks q_bodies access. Also prevents other threads from working on a empty queue.
		pthread_mutex_lock(&qlock);

		//Tells the wait that the Q is onto the next step
		//Wait if Q is empty
		while(q_bodies.empty()){
			//First signal the main thread to start updating.
			pthread_cond_signal(&nextstep);
			//A Broadcast will be sent when the next timestep is started, allowing
			//The waiting thread to start, and unlock the for another thread.
			if(endthreads){
				pthread_mutex_unlock(&qlock);
			    pthread_cond_broadcast(&qEmpty);
				return;
			}
			pthread_cond_wait(&qEmpty,&qlock);
		}

		b = q_bodies.front();
		
		//Pop it and (un)lock...
		q_bodies.pop();

		pthread_mutex_unlock(&qlock);
		//since things can now access the queue, let's just do our fecking math.
		q1.barnesHut(b);
		if(endthreads){
			pthread_mutex_unlock(&qlock);
		    pthread_cond_broadcast(&qEmpty);
			return;
		}
		

	}
}



