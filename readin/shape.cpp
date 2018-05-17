#include "shape.h"
#include <GL/glut.h>
#include <math.h>

//converts color from 255 standard to 1 standard for glColor3f
void Shape::sendGLColor(){
  glColor3f(color.r/255., color.g/255., color.b/255.);
}

/** Default Constructor  */
Shape::Shape(){
  color.r = 254;
  color.g = 254;
  color.b = 254;
  position.x = 0;
  position.y = 0;
}

/** Constructor
     @param p Vector of initial position
*/ 

Shape::Shape(Vec p){
  color.r = 254;
  color.g = 254;
  color.b = 254;
  position.x = p.x;
  position.y = p.y;
}

/**Constructor
 @param p vector of initial position
 @param c Color of the shape
*/
Shape::Shape(Vec p, Color c) {
  color.r = c.r;
  color.g = c.g;
  color.b = c.b; 
  position.x = p.x;
  position.y = p.y;
}

/** istream constructor
     @param is read in color and position from istream file
*/
Shape::Shape(istream &is) {
  is >> color.r;
  is >> color.g; 
  is >> color.b;
  is >> position.x;
  is >> position.y;
}

/** sets the color of the shape 
    @param c the Color variable to set it to
*/
void Shape::setColor(Color c) {  
  color.r = c.r;   
  color.g = c.g; 
  color.b = c.b; 
}

/** sets the color of the shape
    @param r float of red value
    @param g float of green value
    @param b float of blue value 
*/
void Shape::setColor(float r, float g, float b) {
  color.r = r;
  color.g = g;
  color.b = b;
}

/** sets the positions of the shape
    @param x x position
    @param y y position
*/
void Shape::setPosition(int x, int y) {  
  position.x = x;
  position.y = y;
}

/** sets the positions of the shape
    @param P Vector of the starting position
*/ void Shape::setPosition(Vec P) {  
  position.x = P.x;  
  position.y = P.y;
} 

/** displays the shapes color and positions
 */
void Shape::display() {  
  color.display(); 
  position.display();
}
