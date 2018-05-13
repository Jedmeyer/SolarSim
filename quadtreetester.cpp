#include <iostream>
#include "quadtree.h"
using namespace std;

int main(){
  quadtree q1;
  bodygroup b1(cin);
  quadtree q2(10, 15, 15, 10, NULL);

  q1.insert(&b1);
  q1.setTheta(2.0);

  q1.calcCOM();

  return 0;
}
