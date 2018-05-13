#include <random>
#include <vector>
#include <iostream>
using namespace std;

struct vec3d{
  int x;
  int y; 
  int z;
};

void disp_vec3d(vec3d v){
  cout << v.x << " " << v.y << " " << v.z << endl;
}

void disp_vec3d_arr(vec3d **v, int n){
  for(int i = 0; i < n; i++)
    disp_vec3d(*v[i]);
}

vector<vec3d**> treeify(vec3d** p, int n){
  vector<vec3d*> points;
  for(int i = 0; i < n; i++)
    points.push_back(p[i]);

  
}

int main(){
  vec3d ** points;
  int n = 3;
  //int range[2] = {100,100};
  /*
  std::random_device rd();
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(1.0,2.0);
  cout << dis(gen) << endl;
  */
  points = new vec3d*[n];
  for(int i = 0; i < n; i++)
    points[i]=new vec3d;
  points[0]->x=points[0]->y=points[0]->z=1;
  points[1]->x=points[1]->y=points[1]->z=90;
  points[2]->x=points[2]->z=90;
  points[2]->y=1;
  
  disp_vec3d_arr(points,n);

  
}
