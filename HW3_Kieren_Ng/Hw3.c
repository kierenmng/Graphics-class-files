#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
//  OpenGL with prototypes for glext
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


//Globals
int th=0;         //  Azimuth of view angle
int ph=0;         //  Elevation of view angle
int axes = 1;     // Display axes
double dim = 2;

//Adapted from example 8
//  Cosine and Sine in degrees
#define Cos(x) (cos((x)*3.1415927/180))
#define Sin(x) (sin((x)*3.1415927/180))

#define LEN 8192  //  Maximum length of text string
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

/*
 *  Draw vertex in polar coordinates
 */
static void Vertex(double th,double ph)
{
   glVertex3d(Sin(th)*Cos(ph) , Sin(ph) , Cos(th)*Cos(ph));
}


//trying to make pisachio shell idk

static void pistachio(double x, double y, double z, double angle,
        double rx, double ry, double rz, double s)
{
   int th,ph;
   int d = 5;
    
   glPushMatrix();
   glTranslated(x,y,z);
   glRotated(angle,rz,ry,rz);
   glScaled(s*2,s,s);
 
   //One shell
   for (ph=180;ph<360;ph+=d)
   {
      glBegin(GL_QUAD_STRIP);
      glColor3f(1.0,0.85,0.25);
      for (th=-0;th<=180;th+=d)
      {
         Vertex(th,ph);
         Vertex(th,ph+d);
      }
      glEnd();
   }

   glPopMatrix();
   glPushMatrix();

   //One shell
   glPushMatrix();
   glTranslated(x,y,z);
   glRotated(angle+180,rz,ry,rz);
   glScaled(s*2,s,s);

   for (ph=180;ph<360;ph+=d)
   {
      glBegin(GL_QUAD_STRIP);
      glColor3f(1.0,0.85,0.25);
      for (th=-0;th<=180;th+=d)
      {
         Vertex(th,ph);
         Vertex(th,ph+d);
      }
      glEnd();
   }

   glPopMatrix();
   glPushMatrix();



   //inside of shell, not going to be hollow
   glTranslated(x,y,z);
   glRotated(angle,rz,ry,rz);
   glScaled(s*2,s,s);
   glBegin(GL_TRIANGLE_FAN);
   glColor3f(0.33,0.99,0.50);
   glVertex3f(0,0,0);
   for(int i = 0;i <= 100;i++) {
      glVertex3f(
         (cos(i*2.0*3.15159/100)),
         0,
         (sin(i*2.0*3.14159/100))
      );
   }
   glEnd();
   glPopMatrix();
 
 
   //  Undo transformations
   glPopMatrix();    
   
   glPushMatrix();

   //drawing 2d circle which closes the top of the semi circle
   glTranslated(x,y,z);
   glRotated(angle,rz,ry,rz);
   glScaled(s*2,s,s);
   glBegin(GL_TRIANGLE_FAN);
   glColor3f(0.543,0.270,0.074);
   glVertex3f(0,0,0);
   for(int i = 0;i <= 100;i++) {
      glVertex3f(
         (cos(i*2.0*3.15159/100)),
         0,
         (sin(i*2.0*3.14159/100))
      );
   }
   glEnd();
   glPopMatrix();
}  


void display()
{
   const double len=1.5;  //  Length of axes
   //  Erase the window and the depth buffer
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   //  Enable Z-buffering in OpenGL
   glEnable(GL_DEPTH_TEST);
   //  Undo previous transformations
   glLoadIdentity();
   //  Set view angle
   glRotatef(ph,1,0,0);
   glRotatef(th,0,1,0);

   pistachio(0,0,0,0,0,0,0,1);
   pistachio(2,2,2,200,0,1,1,1.5);
   pistachio(3,1,-2,78,1,0,1,.5);

   //  White
   glColor3f(1,1,1);
   //  Draw axes
   if (axes)
   {
      glBegin(GL_LINES);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(len,0.0,0.0);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(0.0,len,0.0);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(0.0,0.0,len);
      glEnd();
      //  Label axes
      glRasterPos3d(len,0.0,0.0);
      Print("X");
      glRasterPos3d(0.0,len,0.0);
      Print("Y");
      glRasterPos3d(0.0,0.0,len);
      Print("Z");
   }
   //  Five pixels from the lower left corner of the window
   glWindowPos2i(5,25);
   //  Print the text string
   Print("Angle=%d,%d",th,ph);
   //  Render the scene
   glFlush();
   //  Make the rendered scene visible
   glutSwapBuffers();
}

/*
 *  GLUT calls this routine when an arrow key is pressed
 */
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
   //  Keep angles to +/-360 degrees
   th %= 360;
   ph %= 360;
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when a key is pressed
 */
void key(unsigned char ch,int x,int y)
{
   //  Exit on ESC
   if (ch == 27)
      exit(0);
   else if (ch == '1')
      dim += .05;
   else if (ch == '2')
      dim -= .05;
   //  Reset view angle
   else if (ch == '0')
      th = ph = 0;
   //  Toggle axes
   else if (ch == 'a' || ch == 'A')
      axes = 1-axes;
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void reshape(int width,int height)
{
   const double dim=2.5;
   //  Ratio of the width to the height of the window
   double w2h = (height>0) ? (double)width/height : 1;
   //  Set the viewport to the entire window
   glViewport(0,0, width,height);
   //  Tell OpenGL we want to manipulate the projection matrix
   glMatrixMode(GL_PROJECTION);
   //  Undo previous transformations
   glLoadIdentity();
   //  Orthogonal projection
   glOrtho(-w2h*dim,+w2h*dim, -dim,+dim, -dim,+dim);
   //  Switch to manipulating the model matrix
   glMatrixMode(GL_MODELVIEW);
   //  Undo previous transformations
   glLoadIdentity();
}

/*
 *  GLUT calls this routine when there is nothing else to do
 */
void idle()
{
   double t = glutGet(GLUT_ELAPSED_TIME)/1000.0;
   glutPostRedisplay();
}

/*
 *  Start up GLUT and tell it what to do
 */
int main(int argc,char* argv[])
{
   //  Initialize GLUT and process user parameters
   glutInit(&argc,argv);
   //  Request double buffered, true color window with Z buffering at 600x600
   glutInitWindowSize(600,600);
   glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   //  Create the window
   glutCreateWindow("Hw3 Kieren Ng");
   //  Tell GLUT to call "idle" when there is nothing else to do
   glutIdleFunc(idle);
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
   return 0;
}
