#include <iostream>
using namespace std;

#include "body.h"

int main(){
  body a;
  body b(cin);
  body c(a);
  body d(1, 1, 1);

  cout << c.getX() << " " << c.getY() << endl;
  cout << d.getMass() << endl;

  cout << a.distance(&b) << endl;
 
  a.gravity(&b);
  a.update();
   
  a.display();
  b.display();
  c.display();
  d.display();
  
}
