#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <time.h>
#include <fstream>
using namespace std;


long double** gen(int n,int dist){
  srand(time(NULL));
  long double** pos;
  pos = new long double*[n];
  for(int i = 0; i < n; i++)
    pos[i]=new long double[5];

  for(int i = 0; i < n; i++){
    pos[i][0] = rand() % dist;//xPos
    pos[i][1] = rand() % dist;//yPos
    pos[i][2] = rand() % 20000000000 + 10000000000;//mass
    pos[i][3] = 0;//xVel
    pos[i][4] = 0;//yVel
  }
  return pos;  
}


void printer(long double ** e, int n,long double dim){
  ofstream of("output.txt");
  of << dim << endl;
  of << n << endl;
  for(int i = 0; i < n; i++){
    for(int j = 0; j < 5; j++)
      of << e[i][j] << " ";
    of << endl;
  }
}

int main(){
  int num_vert;
  cout << "Number of particles: ";
  cin >> num_vert;
  cout << endl;
  int dist;
  cout << "NxN grid dimension limit: ";
  cin >> dist;
  cout << endl;

  long double** out = gen(num_vert, dist);
  
  printer(out,num_vert,dist);

  return 0;
}
