#include<iostream>
#include<fstream>
using namespace std;
#ifdef MACOSX
#include<GLUT/glut.h>
#else
#include<GL/glut.h>
#endif
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include "circle.h"
//#include "Rectangle.h"

//By Jacob Cabbage, but Erich helped a little one time, with moral support


bool mouseIsDragging = false;
Circle ** ciroc;

int WIDTH = 720;  // width of the user window (640 + 80)
int HEIGHT = 720;  // height of the user window (480 + 60)
char programName[] = "proto-draw";
int ct = 0;
int numFrames;
int numCircs;
int dampener= 0;
int DAMPENER;
int helper = 0;

//necessary definitions for the pause/play button
bool pausePress = false, overPause = false;
float pausePos[] = {(int)(WIDTH/2)-52, HEIGHT-52, 52, 52};
char unpausedtext[] = ">";//text displayed on the button if simulation is not paused
char pausedtext[] = "||";//text displayed on button if simulation is paused
char * pausebuttonname = unpausedtext; //pointer to change the text displayed on the pause button when it is clicked
int pauseobject = 0;

//reset button
bool resetPress = false, overReset = false;
float resetPos[] = {(int)(WIDTH/2)+4, HEIGHT-52, 52, 52};
char resetText[] = "R";

//slider
bool sliderIsPressed = false, overSlider = false;
double sliderBox1[] = { (int)(WIDTH-100)/2, HEIGHT-26,   100, 4 };  // background of slider
double sliderBox2[] = {  (int)(WIDTH-100)/2+5, HEIGHT-18,   10, 20 };  // foreground of slider
double sliderPos = 0;  // where the slider currently is located
double sliderStartPos;  // where the mouse first clicked on the slider
double sliderMax = 100;  // upper limit to the sliderPos

//draw text function to label buttons
void drawText(float x, float y, const char *text) {
  glRasterPos2f( x, y );
  int length = strlen(text);
  for (int i = 0; i < length; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
}
void drawText(float *pos, const char *text) {
  drawText(pos[0], pos[1], text);
}
//draws a rectangle, giver coords of upper left corner, width, height
void drawBox(float x, float y, float width, float height) {
  glBegin(GL_POLYGON);
  glVertex2f(x, y);
  // upper left
  glVertex2f(x, y + height);
  // lower left
  glVertex2f(x + width, y + height);  // lower right
  glVertex2f(x + width, y);  // upper right
  glEnd();
}

void drawBox(float *pos) {
  drawBox(pos[0], pos[1], pos[2], pos[3]);
}

// the following function draws a rectangle, given
//   the upper left vertex and the width and height
void drawBox(double x, double y, double width, double height)
{
  glBegin(GL_POLYGON);
    glVertex2f(x, y);  // upper left
    glVertex2f(x, y + height);  // lower left
    glVertex2f(x + width, y + height);  // lower right
    glVertex2f(x + width, y);  // upper right
  glEnd();
}
void drawBox(double *pos)
{
  drawBox(pos[0], pos[1], pos[2], pos[3]);
}


void loadCircs(const char* filename)
{
  ifstream g(filename);
  if(!g.good()) {
    cerr << "Warning: Unable to open " << filename << ", ignoring it. " << endl;
    return; }
  g >> numFrames;
  g >> numCircs;
  
  ciroc = new Circle*[numFrames];
  for (int i = 0; i< numFrames; i++){
    ciroc[i] = new Circle[numCircs];
    for(int j = 0; j < numCircs; j++)
      {
  ciroc[i][j] = Circle(g);
  
      }
  }
  
  cout << "Number of circles loaded: " << numCircs << endl;
}


void drawWindow()
{
  // clear the buffer
  glClear(GL_COLOR_BUFFER_BIT);

  
  for (int i = 0; i<numCircs; i++)
    ciroc[ct][i].draw();
  if (dampener%DAMPENER == 0) {
    if (ct < numFrames-2)
      if (pauseobject == 1){
  ct++;
  if (helper == (numFrames/100))
    sliderPos++;
  helper++;
      }
  }
    if (dampener == DAMPENER)
      dampener = 0;
    dampener++;

  //Draws the Pause button
  if (pausePress) glColor3f(.75, 1., .4);
  else if (overPause) glColor3f(.5, .75, .2);
  else glColor3f(.5,.5,.5);
  drawBox(pausePos);
  glColor3f(1., 0., 0.);
  drawText((int)(WIDTH/2)-31, HEIGHT-80, pausebuttonname);

  //Draws the reset button
  if (resetPress) glColor3f(.75, 1., .4);
  else if (overReset) glColor3f(.5, .75, .2);
  else glColor3f(.5, .5, .5);
  drawBox(resetPos);
  glColor3f(1., 0., 0.);
  drawText((int)(WIDTH/2)+26, HEIGHT-80, resetText);

    // draw the slider background
  if ( sliderIsPressed || overSlider ) glColor3f(.5, .5, .5);  // gray
  else glColor3f(.25, .25, .25);  // dark gray
  drawBox(sliderBox1);
  // draw the slider foreground
  if ( overSlider ) glColor3f(.95, .95, .95);  // very light gray
  else glColor3f(.75, .75, .75);  // light gray
  drawBox(sliderBox2[0] + sliderPos, sliderBox2[1], 
          sliderBox2[2],  sliderBox2[3]);
  
  // tell the graphics card that we're done-- go ahead and draw!
  //   (technically, we are switching between two color buffers...)
  glutSwapBuffers();
  glutPostRedisplay();
}

// process keyboard events
void keyboard( unsigned char c, int x, int y )
{
  int win = glutGetWindow();
  switch(c) {
  case 'c': // circle mode
    //currentMode = CIRCLE;
    cout << "Changing to circle mode." << endl;
    break;
    
  case 'r': //rectangle mode
    //currentMode = RECTANGLE;
    cout << "Changing to rectangle mode." << endl;
    break;
    
    case 'q':
    case 'Q':
    case 27:
      // get rid of the window (as part of shutting down)
      glutDestroyWindow(win);
      exit(0);
      break;
    default:
      break;
  }
  glutPostRedisplay();
}

// the reshape function handles the case where the user changes the size
//   of the window.  We need to fix the coordinate
//   system, so that the drawing area is still the unit square.
void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   WIDTH = w;  HEIGHT = h;
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0., WIDTH-1, HEIGHT-1, 0., -1.0, 1.0);

   pausePos[0] = (int)(WIDTH/2)-52; pausePos[1] =  HEIGHT-110;
   resetPos[0] = (int)(WIDTH/2)+9; resetPos[1] = HEIGHT-110;
   sliderBox1[0] = (int)(WIDTH-100)/2+5; sliderBox1[1] = HEIGHT-26; sliderBox1[2] = 100;
   sliderBox2[0] =  (int)(WIDTH-100)/2+5; sliderBox2[1] =  HEIGHT-39;
   sliderMax = numFrames;

}
bool onPause(int x, int y) {
  return x >= pausePos[0] && y >= pausePos[1] && x <=pausePos[0] + pausePos[2] && y <=pausePos[1] + pausePos[3];
}

bool onReset(int x, int y) {
  return x >= resetPos[0] && y >= resetPos[1] && x <=resetPos[0] + resetPos[2] && y <=resetPos[1] + resetPos[3];
}

// the following function tests whether a point at position x,y is inside
//   the rectangle on the screen corresponding to the slider
bool onSliderForeground(int x, int y)
{
  return x >= sliderBox2[0]+sliderPos  && y >= sliderBox2[1] &&
         x <= sliderBox2[0]+sliderBox2[2]+sliderPos &&
         y <= sliderBox2[1]+sliderBox2[3];
}
bool onSliderBackground(int x, int y)
{
  return x >= sliderBox2[0]  && y >= sliderBox2[1] &&
         x <= sliderBox2[0]+sliderMax+sliderBox2[2] &&
         y <= sliderBox2[1]+sliderBox2[3];
}

// the mouse function is called when a mouse button is pressed down or released
void mouse(int button, int state, int x, int y)
{
  if ( GLUT_LEFT_BUTTON == button ) {
    if ( GLUT_DOWN == state ) {
      // the user just pressed down on the mouse-- do something
      if (onPause(x, y) ) pausePress = true;//the next three buttons are only clickable in the simulation window
      else pausePress = false;
      if (onReset(x, y) ) resetPress = true;
      else resetPress = false;
      if ( onSliderForeground(x,y) ) {
        sliderIsPressed = true;
        sliderStartPos = x - sliderPos;
      } else if ( onSliderBackground(x,y) ) {
        sliderIsPressed = true;
        sliderPos = x - sliderBox1[0];
        sliderStartPos = x-sliderPos;
      } else sliderIsPressed = false;
    } 
    else { 
      // the user just let go the mouse-- do something
      if (onPause(x, y) && pausePress) {  if (pauseobject == 0) {
    pauseobject = 1;//pauses the simulation
    pausePress = false;
    pausebuttonname = pausedtext;
  }   
  else {
    pauseobject = 0;//unpauses the simulation
    pausePress = false; //alternate way to note that the display is paused is by not declaring pausePress to be false unless the button is clicked again, playing the simulation. this would leave the button highlighted.
    pausebuttonname = unpausedtext;//switches text displayed over the pause button to note whether or not the simulation is running
  }
      }
      if ( sliderIsPressed )
        //cout << "New slider position: " << sliderPos << endl;
  if (sliderPos < 100)
    ct = sliderPos * (numFrames/100);
      
      sliderIsPressed = false;
    }
      if (onReset(x, y) && resetPress) {
  ct = 0;
  sliderPos = 0;
  resetPress = false;
      }
  } else if ( GLUT_RIGHT_BUTTON == button ) {
  }
  glutPostRedisplay();
}

// the mouse_motion function is called when the mouse is being dragged,
//   and gives the current location of the mouse
void mouse_motion(int x,int y)
{

  if(onPause(x,y)) overPause = true;
  else overPause = false;
  if(onReset(x,y)) overReset = true;
  else overReset = false;

  if ( sliderIsPressed ) {
    double newSliderPos = x - sliderStartPos;
    // check that the new slider pos does not go off the end of the slider
    if ( newSliderPos < 0 ) sliderPos = 0;
    else if ( newSliderPos > sliderMax ) sliderPos = sliderMax;
    else sliderPos = newSliderPos;
  }
  else {
    if ( onSliderBackground(x,y) ) overSlider = true;
    else overSlider = false;
  }
  // the mouse button is pressed, and the mouse is moving....
  glutPostRedisplay();
}

// the init function sets up the graphics card to draw properly
void init(void)
{
  // clear the window to black
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);

  // set up the coordinate system:  number of pixels along x and y
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0., WIDTH-1, HEIGHT-1, 0., -1.0, 1.0);

  // welcome message
  cout << "Welcome to " << programName << "." << endl;
}


// init_gl_window is the function that starts the ball rolling, in
//  terms of getting everything set up and passing control over to the
//  glut library for event handling.  It needs to tell the glut library
//  about all the essential functions:  what function to call if the
//  window changes shape, what to do to redraw, handle the keyboard,
//  etc.
void init_gl_window()
{
  ct = 0;
  loadCircs("../output/jasontest.txt");
  char *argv[] = {programName};
  int argc = sizeof(argv) / sizeof(argv[0]);
  glutInit(&argc, argv);
  glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE );
  glutInitWindowSize(WIDTH,HEIGHT);
  glutInitWindowPosition(100,100);
  glutCreateWindow(programName);
  init();

  glutDisplayFunc(drawWindow);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutMouseFunc(mouse);
  glutMotionFunc(mouse_motion);
  glutMainLoop();
}

int main()
{
  
  cout << "Enter Dampening Rate: ";
  cin >> DAMPENER;
  cout << endl;
  
  init_gl_window();
}
