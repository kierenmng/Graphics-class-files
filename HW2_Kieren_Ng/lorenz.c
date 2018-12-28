/*
 * Simple program to demonstrate generating coordinates
 * using the Lorenz Attractor
 * A lot of this code was taken from example 9
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

//Globals
int th=0;         //  Azimuth of view angle
int ph=0;         //  Elevation of view angle
int mode=1;       //  Dimension
double dim=2;     //  Size of world

/*  Lorenz Parameters  */
double s  = 10;
double b  = 2.6666;
double r  = 28;

#define LEN 8192  //  Maximum length of text string

//Function taken from ex 9
void Print(const char* format , ...)
{
   char    buf[LEN];
   char*   ch=buf;
   va_list args;
   //  Turn the parameters into a character string
   va_start(args,format);
   vsnprintf(buf,LEN,format,args);
   va_end(args);
   //  Display the characters one at a time at the current raster position
   while (*ch)
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,*ch++);
}

void lorenz(double x, double y, double z)
{
   double ts = 0.001;
   double xtemp;
   double ytemp;
   double ztemp;
   
   glBegin(GL_LINES);
   for (int i = 0; i < 50000; i++)
   {
      double dx = s * (y - x);
      double dy = x * (r - z) - y;
      double dz = (x * y) - (b * z);

      x += ts * dx;
      y += ts * dy;
      z += ts * dz;

      double scaleTemp = sqrt(pow(x,2) + pow(y,2) + pow(z,2));
      xtemp = x/scaleTemp;
      ytemp = y/scaleTemp;
      ztemp = z/scaleTemp;
      glVertex3d(xtemp, ytemp, ztemp);
   }
   glEnd();
}

void display()
{
   //Erase window
   glClear(GL_COLOR_BUFFER_BIT);
   //Undo previous transformations
   glLoadIdentity();
   //Set eye position angle
   glRotated(ph,1,0,0);
   glRotated(th,0,1,0);
   //Draw axes
   glColor3f(1,1,1);
   glBegin(GL_LINES);
   glVertex3d(0.0,0.0,0.0);
   glVertex3d(1,0.0,0.0);
   glVertex3d(0.0,0.0,0.0);
   glVertex3d(0.0,1,0.0);
   glVertex3d(0.0,0.0,0.0);
   glVertex3d(0.0,0.0,1);
   glEnd();
   //  Label axes
   glRasterPos3d(1,0.0,0.0);
   Print("X");
   glRasterPos3d(0.0,1,0.0);
   Print("Y");
   glRasterPos3d(0.0,0.0,1);
   Print("Z");
   //  Display parameters
   glWindowPos2i(5,5);
   Print("Angle=%d,%d s = %0.2f  b = %0.2f  r = %0.2f ",th,ph,s,b,r);
   glColor3f(1,0,1);
   lorenz(s,b,r);
   //  Render the scene and make it visible
   glFlush();
   glutSwapBuffers();
}

void special(int key,int x,int y)
{
   //  Right arrow key - increase angle by 5 degrees
   if (key == GLUT_KEY_RIGHT)
      th += 5;
   //  Left arrow key - decrease angle by 5 degrees
   else if (key == GLUT_KEY_LEFT)
      th -= 5;
   //  Up arrow key - increase elevation by 5 degrees
   else if (key == GLUT_KEY_UP)
      ph += 5;
   //  Down arrow key - decrease elevation by 5 degrees
   else if (key == GLUT_KEY_DOWN)
      ph -= 5;
   //  PageUp key - increase dim
   else if (key == GLUT_KEY_PAGE_UP)
      dim += 0.1;
   //  PageDown key - decrease dim
   else if (key == GLUT_KEY_PAGE_DOWN && dim>1)
      dim -= 0.1;
   //  Keep angles to +/-360 degrees
   th %= 360;
   ph %= 360;
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

void key(unsigned char ch,int x,int y)
{
   //  Exit on ESC
   if (ch == 27)
      exit(0);
   //  Reset view angle
   else if (ch == '0')
      th = ph = 0;

   //s+
   else if (ch == '1')
    s += .25;

   //s-
   else if (ch == '2')
    s -= .25;

   //b+
   else if (ch == '3')
    b += .25;

   //b-
   else if (ch == '4')
    b -= .25;

   //r+
   else if (ch == '5')
    r += .25;
 
   //r-
   else if (ch == '6')
    r -= .25;

   //reset
   else if (ch == '7'){
      s = 10;
      b = 2.6666;
      r = 28;
    }

   glutPostRedisplay();
}


//reshape function taken from example
void reshape(int width,int height)
{
   //  Ratio of the width to the height of the window
   double w2h = (height>0) ? (double)width/height : 1;
   //  Set the viewport to the entire window
   glViewport(0,0, width,height);
   //  Tell OpenGL we want to manipulate the projection matrix
   glMatrixMode(GL_PROJECTION);
   //  Undo previous transformations
   glLoadIdentity();
   //  Orthogonal projection box adjusted for the
   //  aspect ratio of the window
   glOrtho(-dim*w2h,+dim*w2h, -dim,+dim, -dim,+dim);
   //  Switch to manipulating the model matrix
   glMatrixMode(GL_MODELVIEW);
   //  Undo previous transformations
   glLoadIdentity();
}

/*
 *  Main taken from example 6, modified
 */
int main(int argc,char* argv[])
{
  //  Initialize GLUT and process user parameters
   glutInit(&argc,argv);
   //  Request double buffered, true color window 
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
   //  Request 500 x 500 pixel window
   glutInitWindowSize(500,500);
   //  Create the window
   glutCreateWindow("Lorenz HW 2- Kieren Ng");
   //  Tell GLUT to call "display" when the scene should be drawn
   glutDisplayFunc(display);
  //  Tell GLUT to call "reshape" when the window is resized
   glutReshapeFunc(reshape);
   //  Tell GLUT to call "special" when an arrow key is pressed
   glutSpecialFunc(special);
   //  Tell GLUT to call "key" when a key is pressed
   glutKeyboardFunc(key);
   //  Pass control to GLUT so it can interact with the user
   glutMainLoop();
   //  Return code
   return 0;
}
