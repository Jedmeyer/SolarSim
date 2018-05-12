#include <iostream>
#include "bodygroup.h"
using namespace std;

int main() {
  bodygroup b1;
  bodygroup b2(cin);
  bodygroup b3(b2);

  b3.updateCoM();
  cout << b3.getCOMX() << endl;

  b2.getMinX()->display();
  
  b2[1]->display();
  b3.display();

  return 0;
}
