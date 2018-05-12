#include <iostream>
#include "quadtree.h"
using namespace std;

int main(){
  quadtree q1;
  bodygroup b1(cin);
  cout << "here" << endl;
  quadtree q2(10, 15, 15, 10, NULL);

  q1.insert(&b1);
  cout << "here" << endl;
  q1.setTheta(2.0);

  

  return 0;
}
