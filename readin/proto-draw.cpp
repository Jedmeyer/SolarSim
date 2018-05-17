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
#include "circle.h"
//#include "Rectangle.h"

//By Jacob Cabbage, but Erich helped a little one time, with moral support


bool mouseIsDragging = false;
Circle ** ciroc;

int WIDTH = 720;  // width of the user window (640 + 80)
int HEIGHT = 540;  // height of the user window (480 + 60)
char programName[] = "proto-draw";
int ct;


void loadCircs(const char* filename)
{
  int numFrames;
  int numCircs;
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
  // draw stuff
  /*
  for(int i = 0; i < numUserShapes; i++)
      userShape[i]->draw();
  
  for(int j = 0; j < numColorButtons; j++)
    {
      colorButtonBackground[j]->draw();
      colorButtonForeground[j]->draw();
    }
  */  
  for (int i = 0; i<10; i++)
    ciroc[ct][i].draw();
  ct++;
  if (ct > 9)
    ct = 0;
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
}
/*
// the mouse function is called when a mouse button is pressed down or released
void mouse(int button, int state, int x, int y)
{
  if ( GLUT_LEFT_BUTTON == button ) {
    if ( GLUT_DOWN == state ) {
      mouseIsDragging = true;
      // the user just pressed down on the mouse-- do something
      if(currentMode==CIRCLE)
	{
	  handleColorButtonPress(x,y);
	  userShape[numUserShapes] = new Circle;
	  userShape[numUserShapes]->setPosition(x,y);
	  userShape[numUserShapes]->setColor(currentColor);
	  numUserShapes++;
	}
      else if(currentMode==RECTANGLE)
	{
	  handleColorButtonPress(x,y);
	  userShape[numUserShapes] = new Rectangle;
	  userShape[numUserShapes]->setPosition(x,y);
	  userShape[numUserShapes]->setColor(currentColor);
	  numUserShapes++;
	}
    } else { 
      // the user just let go the mouse-- do something
      if(numUserShapes > 0)
	userShape[numUserShapes-1]->update(x,y);
      mouseIsDragging = false;
    }
  } else if ( GLUT_RIGHT_BUTTON == button ) {
  }
  glutPostRedisplay();
}

// the mouse_motion function is called when the mouse is being dragged,
//   and gives the current location of the mouse
void mouse_motion(int x,int y)
{
  if (currentMode == CIRCLE) {}
  else if(currentMode == RECTANGLE) {}
  if(numUserShapes > 0)
    userShape[numUserShapes-1]->update(x,y);
  // the mouse button is pressed, and the mouse is moving....
  glutPostRedisplay();
}
*/
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
  loadCircs("circs.txt");
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
  //glutMouseFunc(mouse);
  //glutMotionFunc(mouse_motion);
  glutMainLoop();
}

int main()
{
  init_gl_window();
}
