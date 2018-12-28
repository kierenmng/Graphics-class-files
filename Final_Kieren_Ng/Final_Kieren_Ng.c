/*
 *  Final Project Kieren Ng
 *
 *  Power rack and dumbbell portion of cu boulder rec
 *
 *  Key bindings:
 *  l          Toggle lighting on/off
 *  t          Change textures
 *  m          Toggles texture mode modulate/replace
 *  a/A        decrease/increase ambient light
 *  d/D        decrease/increase diffuse light
 *  s/S        decrease/increase specular light
 *  e/E        decrease/increase emitted light
 *  n/N        Decrease/increase shininess
 *  []         Lower/rise light
 *  x          Toggle axes
 *  arrows     Change view angle
 *  PgDn/PgUp  Zoom in and out
 *  0          Reset view angle
 *  ESC        Exit
 */
#include "CSCIx229.h"
int mode=0;       //  Texture mode
int ntex=0;       //  Cube faces
int axes=1;       //  Display axes
int th=0;         //  Azimuth of view angle
int ph=0;         //  Elevation of view angle
int light=1;      //  Lighting
int rep=1;        //  Repitition
double asp=1;     //  Aspect ratio
double dim=3.0;   //  Size of world
int move = 1;
// Light values
int emission  =   0;  // Emission intensity (%)
int ambient   =  30;  // Ambient intensity (%)
int diffuse   = 100;  // Diffuse intensity (%)
int specular  =   0;  // Specular intensity (%)
int shininess =   0;  // Shininess (power of two)
float shiny   =   1;    // Shininess (value)
int zh        =  90;  // Light azimuth
float ylight  =   0;  // Elevation of light
unsigned int texture[7]; // Texture names

/*
 * draw a cylinder
 * at (x,y,z)
 * dimensions (dx,dy,dz)
 * rotated th about the z axis
 */
static void cyl(double x, double y, double z,
                    double dx, double dy, double dz,
                    double th, double radius, double height)
{
  //  Set specular color to white
   float white[] = {1,1,1,1};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0};
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);
   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glRotated(th,0,0,1);
   glScaled(dx,dy,dz);
   // Enable textures
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[0]);

   int j;
   glBegin(GL_TRIANGLE_STRIP);
   for (j = 0; j <= 360; j++) {
      double x = radius * Cos(j);
      double y = height;
      double z = radius * Sin(j);

      //glColor3f(j/306, j/360, j/360);

      glNormal3d(Cos(j), 1, Sin(j));

      glVertex3d(x, y, z);
      glVertex3d(x, -y, z);
   }
   glEnd();
  
   //left side
   //draw top
   double i; 
   glNormal3d(0,1,0);
   
   glBegin(GL_TRIANGLE_FAN);
      glVertex3d(0.0, height, 0.0);

      for(i = 0.0; i < 360; i+=.125) {
         glVertex3d(radius * cos(i), height, radius * sin(i));
      }
   glEnd();

   //draw bottom
   glNormal3d(0,-1,0);
   glBegin(GL_TRIANGLE_FAN);
      glVertex3d(0.0, -height, 0.0);

      for(i = 0.0; i < 360; i+=.125) {
         glVertex3d(radius * cos(i), -height, radius * sin(i));
      }
   glEnd();
   glPopMatrix(); 
}

/*
 * draw a cylinder
 * at (x,y,z)
 * dimensions (dx,dy,dz)
 * rotated th about the z axis
 */
static void cyl2(double x, double y, double z,
                    double dx, double dy, double dz,
                    double th, double radius, double height)
{
  //  Set specular color to white
   float white[] = {1,1,1,1};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0};
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);
   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glRotated(th,1,0,0);
   glScaled(dx,dy,dz);
   // Enable textures
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[0]);

   int j;
   glBegin(GL_TRIANGLE_STRIP);
   for (j = 0; j <= 360; j++) {
      double x = radius * Cos(j);
      double y = height;
      double z = radius * Sin(j);

      //glColor3f(j/306, j/360, j/360);

      glNormal3d(Cos(j), 1, Sin(j));

      glVertex3d(x, y, z);
      glVertex3d(x, -y, z);
   }
   glEnd();

   //left side
   //draw top
   double i;
   glNormal3d(0,1,0);

   glBegin(GL_TRIANGLE_FAN);
      glVertex3d(0.0, height, 0.0);

      for(i = 0.0; i < 360; i+=.125) {
         glVertex3d(radius * cos(i), height, radius * sin(i));
      }
   glEnd();

   //draw bottom
   glNormal3d(0,-1,0);
   glBegin(GL_TRIANGLE_FAN);
      glVertex3d(0.0, -height, 0.0);

      for(i = 0.0; i < 360; i+=.125) {
         glVertex3d(radius * cos(i), -height, radius * sin(i));
      }
   glEnd();
   glPopMatrix();
}



/*
 * draw a tube
 * at (x,y,z)
 * dimensions (dx,dy,dz)
 * rotated th about the z axis
 */
static void tube(double x, double y, double z,
                    double dx, double dy, double dz,
                    double th, double radius, double height)
{
   //  Set specular color to white
   float white[] = {1,1,1,1};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0};
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);
   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glRotated(th,0,0,1);
   glScaled(dx,dy,dz);
   // Enable textures
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[0]);
   
   int j;
   glBegin(GL_TRIANGLE_STRIP);
   for (j = 0; j <= 360; j++) {
      double x = radius * Cos(j);
      double y = height;
      double z = radius * Sin(j);

      //glColor3f(j/306, j/360, j/360);

      glNormal3d(Cos(j), 1, Sin(j));

      glVertex3d(x, y, z);
      glVertex3d(x, -y, z);
   }
   glEnd();
   int m;
   glBegin(GL_TRIANGLE_STRIP);
   for (m = 0; m <= 360; m++) {
      double x = (radius/1.1) * Cos(m);
      double y = height;
      double z = (radius/1.1) * Sin(m);

      //glColor3f(j/306, j/360, j/360);

      glNormal3d(Cos(m), 1, Sin(m));

      glVertex3d(x, y, z);
      glVertex3d(x, -y, z);
   }
   glEnd();

   //draw top
   double i;
   glNormal3d(0,1,0);

   glBegin(GL_TRIANGLES);
      glVertex3d(0.0, height, 0.0);

      for(i = 0.0; i < 360; i+=.125) {
         glVertex3d(radius * cos(i),height, radius * sin(i));
         glVertex3d((radius/1.1) * cos(i),height, (radius/1.1) * sin(i));
      }
   glEnd();

   //draw bottom
   glNormal3d(0,-1,0);
   glBegin(GL_TRIANGLES);
      glVertex3d(0.0, -height, 0.0);

      for(i = 0.0; i < 360; i+=.125) {
         glVertex3d(radius * cos(i), -height, radius * sin(i));
         glVertex3d((radius/1.1) * cos(i),-height, (radius/1.1) * sin(i));
      }
   glEnd();


   glPopMatrix();

}


/*
 * draw a rectangle
 * at (x,y,z)
 * dimensions (dx,dy,dz)
 * rotated th about the z axis
 */

static void rect(double x, double y, double z,
                 double dx, double dy, double dz,
                 double th)
{
   //  Set specular color to white
   float white[] = {1,1,1,1};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0};
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);
   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glRotated(th,0,0,1);
   glScaled(dx,dy,dz);
   //  Enable textures
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[0]);
   //  Front
   glColor3f(0.5,0.5,0.5);
   if (ntex) glBindTexture(GL_TEXTURE_2D,texture[0]);
   glBegin(GL_QUADS);
   glNormal3f( 0, 0, 1);
   glTexCoord2f(0,0); glVertex3f(-1,-1, 1);
   glTexCoord2f(1,0); glVertex3f(+1,-1, 1);
   glTexCoord2f(1,1); glVertex3f(+1,+1, 1);
   glTexCoord2f(0,1); glVertex3f(-1,+1, 1);
   glEnd();
   //  Back
   glColor3f(0.5,0.5,0.5);
   if (ntex) glBindTexture(GL_TEXTURE_2D,texture[0]);
   glBegin(GL_QUADS);
   glNormal3f( 0, 0,-1);
   glTexCoord2f(0,0); glVertex3f(+1,-1,-1);
   glTexCoord2f(1,0); glVertex3f(-1,-1,-1);
   glTexCoord2f(1,1); glVertex3f(-1,+1,-1);
   glTexCoord2f(0,1); glVertex3f(+1,+1,-1);
   glEnd();
   //  Right
   glColor3f(0.5,0.5,0.5);
   if (ntex) glBindTexture(GL_TEXTURE_2D,texture[0]);
   glBegin(GL_QUADS);
   glNormal3f(+1, 0, 0);
   glTexCoord2f(0,0); glVertex3f(+1,-1,+1);
   glTexCoord2f(1,0); glVertex3f(+1,-1,-1);
   glTexCoord2f(1,1); glVertex3f(+1,+1,-1);
   glTexCoord2f(0,1); glVertex3f(+1,+1,+1);
   glEnd();
   //  Left
   glColor3f(0.5,0.5,0.5);
   if (ntex) glBindTexture(GL_TEXTURE_2D,texture[0]);
   glBegin(GL_QUADS);
   glNormal3f(-1, 0, 0);
   glTexCoord2f(0,0); glVertex3f(-1,-1,-1);
   glTexCoord2f(1,0); glVertex3f(-1,-1,+1);
   glTexCoord2f(1,1); glVertex3f(-1,+1,+1);
   glTexCoord2f(0,1); glVertex3f(-1,+1,-1);
   glEnd();
   //  Top
   glColor3f(0.5,0.5,0.5);
   if (ntex) glBindTexture(GL_TEXTURE_2D,texture[0]);
   glBegin(GL_QUADS);
   glNormal3f( 0,+1, 0);
   glTexCoord2f(0,0); glVertex3f(-1,+1,+1);
   glTexCoord2f(1,0); glVertex3f(+1,+1,+1);
   glTexCoord2f(1,1); glVertex3f(+1,+1,-1);
   glTexCoord2f(0,1); glVertex3f(-1,+1,-1);
   glEnd();
   //  Bottom
   glColor3f(0.5,0.5,0.5);
   if (ntex) glBindTexture(GL_TEXTURE_2D,texture[0]);
   glBegin(GL_QUADS);
   glNormal3f( 0,-1, 0);
   glTexCoord2f(0,0); glVertex3f(-1,-1,-1);
   glTexCoord2f(1,0); glVertex3f(+1,-1,-1);
   glTexCoord2f(1,1); glVertex3f(+1,-1,+1);
   glTexCoord2f(0,1); glVertex3f(-1,-1,+1);
   glEnd();
   //  Undo transformations and textures
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}

/*
 * draw a rectangle
 * at (x,y,z)
 * dimensions (dx,dy,dz)
 * rotated th about the z axis
 */

static void holder(double x, double y, double z,
                 double dx, double dy, double dz,
                 double th)
{
   //  Set specular color to white
   float white[] = {1,1,1,1};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0};
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);
   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glRotated(th,1,0,0);
   glScaled(dx,dy,dz);
   //  Enable textures
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[0]);
   glColor3f(1,1,1);
   if (ntex) glBindTexture(GL_TEXTURE_2D,texture[0]);
   glBegin(GL_QUADS);
   glNormal3f(-1, 0, 0);
   glTexCoord2f(0,0); glVertex3f(-1,-1,-1);
   glTexCoord2f(1,0); glVertex3f(-1,-1,+1);
   glTexCoord2f(1,1); glVertex3f(-1,+1,+1);
   glTexCoord2f(0,1); glVertex3f(-1,+1,-1);
   glEnd();
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}

/*
 * draw a power rack
 * at (x,y,z)
 * dimensions (dx,dy,dz)
 * rotated th about the z axis
 */
static void powerrack(double x, double y, double z)
{
   //verticals
   rect(x+1.5,y+6.5,z,0.2,6.5,0.3,0);
   rect(x+6.5,y+6.5,z,0.2,6.5,0.3,0);
   rect(x+1.5,y+6.5,z-6,0.2,6.5,0.3,0);
   rect(x+6.5,y+6.5,z-6,0.2,6.5,0.3,0);
   rect(x+1.5,y+6.5,z-11.5,0.2,6.5,0.3,0);
   rect(x+6.5,y+6.5,z-11.5,0.2,6.5,0.3,0);
   rect(x+1.5,y+6.5,z-17.3,0.2,6.5,0.3,0);
   rect(x+6.5,y+6.5,z-17.3,0.2,6.5,0.3,0);
   rect(x+1.5,y+6,z-8.7,0.2,5.7,0.3,0);
   rect(x+6.5,y+6,z-8.7,0.2,5.7,0.3,0);
   
   //horizontals
   rect(x+1.5,y,z-8.6,0.2,0.3,9.3,0);
   rect(x+6.5,y,z-8.6,0.2,0.3,9.3,0);
   rect(x+3.8,y+12.6,z,2.5,0.2,0.2,0);
   rect(x+3.8,y+12.6,z-6,2.5,0.2,0.2,0);
   rect(x+3.8,y+12.6,z-11.5,2.5,0.2,0.2,0);
   rect(x+3.8,y+12.6,z-17.3,2.5,0.2,0.2,0);
   rect(x+1.5,y+11.5,z-8.6,0.2,0.2,2.7,0);
   rect(x+6.5,y+11.5,z-8.6,0.2,0.2,2.7,0);
   rect(x+1.5,y+12.8,z-3,0.2,0.2,3,0);
   rect(x+6.5,y+12.8,z-3,0.2,0.2,3,0);
   rect(x+1.5,y+12.8,z-14.6,0.2,0.2,3,0);
   rect(x+6.5,y+12.8,z-14.6,0.2,0.2,3,0);

   //diagonals
   rect(x+2,y+12,z,0.8,0.15,0.15,45);
   rect(x+2,y+12,z-6,0.8,0.15,0.15,45);
   rect(x+2,y+12,z-11.5,0.8,0.15,0.15,45);
   rect(x+2,y+12,z-17.3,0.8,0.15,0.15,45);
   rect(x+6,y+12,z,0.8,0.15,0.15,135);
   rect(x+6,y+12,z-6,0.8,0.15,0.15,135);
   rect(x+6,y+12,z-11.5,0.8,0.15,0.15,135);
   rect(x+6,y+12,z-17.3,0.8,0.15,0.15,135);

   //diamond metal plate to hold small plates
   holder(x+2.2,y+9,z-8.7,1,1,1,45);
   holder(x+7.8,y+9,z-8.7,1,1,1,45);

   //holders for plate
   cyl(x+0.7,y+1.8,z-8.7,0.5,0.5,0.5,90,0.3,4);
   cyl(x+0.4,y+4,z-8.7,0.5,0.5,0.5,90,0.3,2);
   cyl(x+0.7,y+6.2,z-8.7,0.5,0.5,0.5,90,0.3,1.2);
   cyl(x+7.4,y+1.8,z-8.7,0.5,0.5,0.5,90,0.3,4);
   cyl(x+7.5,y+4,z-8.7,0.5,0.5,0.5,90,0.3,2);
   cyl(x+7.2,y+6.2,z-8.7,0.5,0.5,0.5,90,0.3,1.2);
   cyl(x+0.59,y+10,z-8.7,0.5,0.5,0.5,90,0.3,1.2);
   cyl(x+0.59,y+9,z-7.7,0.5,0.5,0.5,90,0.3,1.2);
   cyl(x+0.59,y+9,z-9.6,0.5,0.5,0.5,90,0.3,1.2);
   cyl(x+7.4,y+10,z-8.7,0.5,0.5,0.5,90,0.3,1.2);
   cyl(x+7.4,y+9,z-7.7,0.5,0.5,0.5,90,0.3,1.2);
   cyl(x+7.4,y+9,z-9.6,0.5,0.5,0.5,90,0.3,1.2);
  
   //pull up bars
   cyl2(x+3.3,y+12.6,z+0.4,0.5,0.5,0.5,90,0.18,0.8);
   cyl2(x+4.7,y+12.6,z+0.4,0.5,0.5,0.5,90,0.18,0.8);
   cyl(x+4,y+12.6,z+0.85,0.5,0.5,0.5,90,0.2,3);
   cyl(x+2.2,y+12.4,z+0.85,0.5,0.5,0.5,120,0.2,0.8);
   cyl(x+5.8,y+12.4,z+0.85,0.5,0.5,0.5,60,0.2,0.8);
   cyl2(x+3.3,y+12.6,z-17.6,0.5,0.5,0.5,90,0.18,0.8);
   cyl2(x+4.7,y+12.6,z-17.6,0.5,0.5,0.5,90,0.18,0.8);
   cyl(x+4,y+12.6,z-18,0.5,0.5,0.5,90,0.2,3);
   cyl(x+2.2,y+12.4,z-18,0.5,0.5,0.5,120,0.2,0.8);
   cyl(x+5.8,y+12.4,z-18,0.5,0.5,0.5,60,0.2,0.8);

   //upright bar holder tubes
   tube(x+1.5,y+0.5,z-7,0.5,0.5,0.5,0,0.25,0.5);
   tube(x+1.5,y+0.5,z-8,0.5,0.5,0.5,0,0.4,0.5);
   tube(x+1.5,y+0.5,z-9.5,0.5,0.5,0.5,0,0.4,0.5);
   tube(x+1.5,y+0.5,z-10.5,0.5,0.5,0.5,0,0.25,0.5);
   tube(x+6.5,y+0.5,z-9.5,0.5,0.5,0.5,0,0.4,0.5);
   tube(x+6.5,y+0.5,z-7,0.5,0.5,0.5,0,0.25,0.5);
   tube(x+6.5,y+0.5,z-8,0.5,0.5,0.5,0,0.4,0.5);
   tube(x+6.5,y+0.5,z-10.5,0.5,0.5,0.5,0,0.25,0.5);
   
}

/*
 * draw a barbell
 * at (x,y,z)
 * dimensions (dx,dy,dz)
 * rotated th about the z axis
 */

static void barbell(double x, double y, double z)
{
   //version for horizontal bar
   cyl(x,y,z,0.5,0.5,0.5,90,0.3,2);
   cyl(x+1,y,z,0.5,0.5,0.5,90,0.5,0.3);
   cyl(x+4,y,z,0.5,0.5,0.5,90,0.2,6);
   cyl(x+7,y,z,0.5,0.5,0.5,90,0.5,0.3);
   cyl(x+8,y,z,0.5,0.5,0.5,90,0.3,2);

   //version where bar is upright
   //cyl(x,y+1,z,0.5,0.5,0.5,0,0.3,2);
   //cyl(x,y+2,z,0.5,0.5,0.5,0,0.5,0.3);
   //cyl(x,y+5,z,0.5,0.5,0.5,0,0.2,6);
   //cyl(x,y+8,z,0.5,0.5,0.5,0,0.5,0.3);
   //cyl(x,y+9,z,0.5,0.5,0.5,0,0.3,2);
 
}

/*
 *  Draw a plate
 *     at (x,y,z)
 *     dimensions (dx,dy,dz)
 *     rotated th about the y axis
 */
static void plate(double x, double y, double z, double size)
{
   if(size == 45)
   {
       cyl(x,y,z,0.5,0.5,0.5,90,.83,0.5);
       cyl(x,y,z,0.5,0.5,0.5,90,2.4,0.4);
       tube(x,y,z,0.5,0.5,0.5,90,2.5,0.5);
   }
   else if (size == 25)
   {
       cyl(x,y,z,0.5,0.5,0.5,90,.83,0.25);
       cyl(x,y,z,0.5,0.5,0.5,90,2.4,0.15);
       tube(x,y,z,0.5,0.5,0.5,90,2.5,0.25);
   }
   else if (size == 10)
   {
       cyl(x,y,z,0.5,0.5,0.5,90,.83,0.15);
       cyl(x,y,z,0.5,0.5,0.5,90,2.4,0.05);
       tube(x,y,z,0.5,0.5,0.5,90,2.5,0.15);
   }
   else if (size == 5)
   {
       cyl(x,y,z,0.5,0.5,0.5,90,0.33,0.15);
       cyl(x,y,z,0.5,0.5,0.5,90,1,0.05);
       tube(x,y,z,0.5,0.5,0.5,90,1.1,0.15);
   }
   else if (size == 2.5)
   {
       cyl(x,y,z,0.5,0.5,0.5,90,.2,0.15);
       cyl(x,y,z,0.5,0.5,0.5,90,.7,0.05);
       tube(x,y,z,0.5,0.5,0.5,90,.8,0.15);

   }
}


/*
 *  Draw a dumbell
 *     at (x,y,z)
 *     dimensions (dx,dy,dz)
 *     rotated th about the y axis
 */
static void dumbell(double x,double y,double z,
                 double dx,double dy,double dz,
                 double th)
{
   //  Set specular color to white
   float white[] = {1,1,1,1};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0};
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);
   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glRotated(th,0,1,0);
   glScaled(dx,dy,dz);
   // Enable textures
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[0]);
   //  Front
   glColor3f(0.5,0.5,0.5);
   glBegin(GL_POLYGON);
   glNormal3f( 0, 0, 1);
   glVertex3f(-.4,-1, 3);
   glVertex3f(-1,-.4, 3);
   glVertex3f(-1,+.4, 3);
   glVertex3f(-.4,+1, 3);
   glVertex3f(+.4,+1, 3);
   glVertex3f(+1,+.4, 3);
   glVertex3f(+1,-.4, 3);
   glVertex3f(+.4,-1, 3);
   glVertex3f(-.4,+1, 3);
   glVertex3f(+1,+.4, 3);
   glVertex3f(+1,-.4, 3);
   glVertex3f(-.4,-1, 3);
   glEnd();
   //  Back
   glColor3f(0.5,0.5,0.5);
   glBegin(GL_POLYGON);
   glNormal3f( 0, 0,-1);
   glVertex3f(-.4,-1,1);
   glVertex3f(-1,-.4,1);
   glVertex3f(-1,+.4,1);
   glVertex3f(-.4,+1,1);
   glVertex3f(+.4,+1,1);
   glVertex3f(+1,+.4,1);
   glVertex3f(+1,-.4,1);
   glVertex3f(+.4,-1,1);
   glVertex3f(-.4,+1,1);
   glVertex3f(+1,+.4,1);
   glVertex3f(+1,-.4,1);
   glVertex3f(-.4,-1,1);
   glEnd();
   //  Right
   glColor3f(0.5,0.5,0.5);
   if (ntex) glBindTexture(GL_TEXTURE_2D,texture[0]);
   glBegin(GL_QUADS);
   glNormal3f(+1, 0, 0);
   glTexCoord2f(0,0); glVertex3f(+1,-.4,+3); //glTexCoord2f(0,0);
   glTexCoord2f(1,0); glVertex3f(+1,-.4,+1); //glTexCoord2f(1,0);
   glTexCoord2f(1,1); glVertex3f(+1,+.4,+1); //glTexCoord2f(1,1);
   glTexCoord2f(0,1); glVertex3f(+1,+.4,+3); //glTexCoord2f(0,1);
   glEnd();
   //glPopMatrix();
   //glDisable(GL_TEXTURE_2D);
   glColor3f(0.5,0.5,0.5);
   if (ntex) glBindTexture(GL_TEXTURE_2D,texture[0]);
   glBegin(GL_QUADS);
   glNormal3f(+.53, +0.53, 0);
   glTexCoord2f(0,0); glVertex3f(+.4,+1,+3);
   glTexCoord2f(1,0); glVertex3f(+.4,+1,+1);
   glTexCoord2f(1,1); glVertex3f(+1,+.4,+1);
   glTexCoord2f(0,1); glVertex3f(+1,+.4,+3);
   glEnd();
   glColor3f(0.5,0.5,0.5);
   if (ntex) glBindTexture(GL_TEXTURE_2D,texture[0]);
   glBegin(GL_QUADS);
   glNormal3f(+.53, -0.53, 0);
   glTexCoord2f(0,0); glVertex3f(+1,-.4,+3);
   glTexCoord2f(1,0); glVertex3f(+1,-.4,+1);
   glTexCoord2f(1,1); glVertex3f(+.4,-1,+1);
   glTexCoord2f(0,1); glVertex3f(+.4,-1,+3);
   glEnd();

   //  Left
   glColor3f(0.5,0.5,0.5);
   if (ntex) glBindTexture(GL_TEXTURE_2D,texture[0]);
   glBegin(GL_QUADS);
   glNormal3f(-1, 0, 0);
   glTexCoord2f(0,0); glVertex3f(-1,-.4,+1);
   glTexCoord2f(1,0); glVertex3f(-1,-.4,+3);
   glTexCoord2f(1,1); glVertex3f(-1,+.4,+3);
   glTexCoord2f(0,1); glVertex3f(-1,+.4,+1);
   glEnd();
   glColor3f(0.5,0.5,0.5);
   if (ntex) glBindTexture(GL_TEXTURE_2D,texture[0]);
   glBegin(GL_QUADS);
   glNormal3f(-0.53, -0.53, 0);
   glTexCoord2f(0,0); glVertex3f(-1,-.4,+1);
   glTexCoord2f(1,0); glVertex3f(-1,-.4,+3);
   glTexCoord2f(1,1); glVertex3f(-.4,-1,+3);
   glTexCoord2f(0,1); glVertex3f(-.4,-1,+1);
   glEnd();
   glColor3f(0.5,0.5,0.5);
   if (ntex) glBindTexture(GL_TEXTURE_2D,texture[0]);
   glBegin(GL_QUADS);
   glNormal3f(-0.53, +0.53, 0);
   glTexCoord2f(0,0); glVertex3f(-.4,+1,+1);
   glTexCoord2f(1,0); glVertex3f(-.4,+1,+3);
   glTexCoord2f(1,1); glVertex3f(-1,+.4,+3);
   glTexCoord2f(0,1); glVertex3f(-1,+.4,+1);
   glEnd();

   //  Top
   glColor3f(0.5,0.5,0.5);
   if (ntex) glBindTexture(GL_TEXTURE_2D,texture[0]);
   glBegin(GL_QUADS);
   glNormal3f( 0,+1, 0);
   glTexCoord2f(0,0); glVertex3f(-.4,+1,+3);
   glTexCoord2f(1,0); glVertex3f(+.4,+1,+3);
   glTexCoord2f(1,1); glVertex3f(+.4,+1,+1);
   glTexCoord2f(0,1); glVertex3f(-.4,+1,+1);
   glEnd();
   //  Bottom
   glColor3f(0.5,0.5,0.5);
   if (ntex) glBindTexture(GL_TEXTURE_2D,texture[0]);
   glBegin(GL_QUADS);
   glNormal3f( 0,-1, 0);
   glTexCoord2f(0,0); glVertex3f(-.4,-1,+1);
   glTexCoord2f(1,0); glVertex3f(+.4,-1,+1);
   glTexCoord2f(1,1); glVertex3f(+.4,-1,+3);
   glTexCoord2f(0,1); glVertex3f(-.4,-1,+3);
   glEnd();


   //  Handle
    //  Right
   glColor3f(0.3,0.3,0.3);
   if (ntex) glBindTexture(GL_TEXTURE_2D,texture[1]);
   glBegin(GL_QUADS);
   glNormal3f(+1, 0, 0);
   glTexCoord2f(0,0); glVertex3f(+.25,-.1,+1);
   glTexCoord2f(1,0); glVertex3f(+.25,-.1,-1);
   glTexCoord2f(1,1); glVertex3f(+.25,+.1,-1);
   glTexCoord2f(0,1); glVertex3f(+.25,+.1,+1);
   glEnd();
   glColor3f(0.3,0.3,0.3);
   if (ntex) glBindTexture(GL_TEXTURE_2D,texture[1]);
   glBegin(GL_QUADS);
   glNormal3f(+0.53, +0.53, 0);
   glTexCoord2f(0,0); glVertex3f(+.1,+.25,+1);
   glTexCoord2f(1,0); glVertex3f(+.1,+.25,-1);
   glTexCoord2f(1,1); glVertex3f(+.25,+.1,-1);
   glTexCoord2f(0,1); glVertex3f(+.25,+.1,+1);
   glEnd();
   glColor3f(0.3,0.3,0.3);
   if (ntex) glBindTexture(GL_TEXTURE_2D,texture[1]);
   glBegin(GL_QUADS);
   glNormal3f(+0.53, -0.53, 0);
   glTexCoord2f(0,0); glVertex3f(+.25,-.1,+1);
   glTexCoord2f(1,0); glVertex3f(+.25,-.1,-1);
   glTexCoord2f(1,1); glVertex3f(+.1,-.25,-1);
   glTexCoord2f(0,1); glVertex3f(+.1,-.25,+1);
   glEnd();
   //  Left
   glColor3f(0.3,0.3,0.3);
   if (ntex) glBindTexture(GL_TEXTURE_2D,texture[1]);
   glBegin(GL_QUADS);
   glNormal3f(-1, 0, 0);
   glTexCoord2f(0,0); glVertex3f(-.25,-.1,-1);
   glTexCoord2f(1,0); glVertex3f(-.25,-.1,+1);
   glTexCoord2f(1,1); glVertex3f(-.25,+.1,+1);
   glTexCoord2f(0,1); glVertex3f(-.25,+.1,-1);
   glEnd();
   glColor3f(0.3,0.3,0.3);
   if (ntex) glBindTexture(GL_TEXTURE_2D,texture[1]);
   glBegin(GL_QUADS);
   glNormal3f(-0.53, -0.53, 0);
   glTexCoord2f(0,0); glVertex3f(-.25,-.1,-1);
   glTexCoord2f(1,0); glVertex3f(-.25,-.1,+1);
   glTexCoord2f(1,1); glVertex3f(-.1,-.25,+1);
   glTexCoord2f(0,1); glVertex3f(-.1,-.25,-1);
   glEnd();
   glColor3f(0.3,0.3,0.3);
   if (ntex) glBindTexture(GL_TEXTURE_2D,texture[1]);
   glBegin(GL_QUADS);
   glNormal3f(-0.53, +0.53, 0);
   glTexCoord2f(0,0); glVertex3f(-.1,+.25,-1);
   glTexCoord2f(1,0); glVertex3f(-.1,+.25,+1);
   glTexCoord2f(1,1); glVertex3f(-.25,+.1,+1);
   glTexCoord2f(0,1); glVertex3f(-.25,+.1,-1);
   glEnd();
   //  Top
   glColor3f(0.3,0.3,0.3);
   if (ntex) glBindTexture(GL_TEXTURE_2D,texture[1]);
   glBegin(GL_QUADS);
   glNormal3f( 0,+1, 0);
   glVertex3f(-.1,+.25,+1);
   glVertex3f(+.1,+.25,+1);
   glVertex3f(+.1,+.25,-1);
   glVertex3f(-.1,+.25,-1);
   glEnd();
   //  Bottom
   glColor3f(0.3,0.3,0.3);
   if (ntex) glBindTexture(GL_TEXTURE_2D,texture[1]);
   glBegin(GL_QUADS);
   glNormal3f( 0,-1, 0);
   glVertex3f(-.1,-.25,-1);
   glVertex3f(+.1,-.25,-1);
   glVertex3f(+.1,-.25,+1);
   glVertex3f(-.1,-.25,+1);
   glEnd();

   // second weight
   //  Front
   glColor3f(0.5,0.5,0.5);
   glBegin(GL_POLYGON);
   glNormal3f( 0, 0, 1);
   glVertex3f(-.4,-1, -1);
   glVertex3f(-1,-.4, -1);
   glVertex3f(-1,+.4, -1);
   glVertex3f(-.4,+1, -1);
   glVertex3f(+.4,+1, -1);
   glVertex3f(+1,+.4, -1);
   glVertex3f(+1,-.4, -1);
   glVertex3f(+.4,-1, -1);
   glVertex3f(-.4,+1, -1);
   glVertex3f(+1,+.4, -1);
   glVertex3f(+1,-.4, -1);
   glVertex3f(-.4,-1, -1);
   glEnd();
   //  Back
   glColor3f(0.5,0.5,0.5);
   glBegin(GL_POLYGON);
   glNormal3f( 0, 0,-1);
   glVertex3f(-.4,-1,-3);
   glVertex3f(-1,-.4,-3);
   glVertex3f(-1,+.4,-3);
   glVertex3f(-.4,+1,-3);
   glVertex3f(+.4,+1,-3);
   glVertex3f(+1,+.4,-3);
   glVertex3f(+1,-.4,-3);
   glVertex3f(+.4,-1,-3);
   glVertex3f(-.4,+1,-3);
   glVertex3f(+1,+.4,-3);
   glVertex3f(+1,-.4,-3);
   glVertex3f(-.4,-1,-3);
   glEnd();
   //  Right
   glColor3f(0.5,0.5,0.5);
   if (ntex) glBindTexture(GL_TEXTURE_2D,texture[0]);
   glBegin(GL_QUADS);
   glNormal3f(+1, 0, 0);
   glTexCoord2f(0,0); glVertex3f(+1,-.4,-1);
   glTexCoord2f(1,0); glVertex3f(+1,-.4,-3);
   glTexCoord2f(1,1); glVertex3f(+1,+.4,-3);
   glTexCoord2f(0,1); glVertex3f(+1,+.4,-1);
   glEnd();
   glColor3f(0.5,0.5,0.5);
   if (ntex) glBindTexture(GL_TEXTURE_2D,texture[0]);
   glBegin(GL_QUADS);
   glNormal3f(+0.53, +0.53, 0);
   glTexCoord2f(0,0); glVertex3f(+.4,+1,-1);
   glTexCoord2f(1,0); glVertex3f(+.4,+1,-3);
   glTexCoord2f(1,1); glVertex3f(+1,+.4,-3);
   glTexCoord2f(0,1); glVertex3f(+1,+.4,-1);
   glEnd();
   glColor3f(0.5,0.5,0.5);
   if (ntex) glBindTexture(GL_TEXTURE_2D,texture[0]);
   glBegin(GL_QUADS);
   glNormal3f(+0.53, -0.53, 0);
   glTexCoord2f(0,0); glVertex3f(+1,-.4,-1);
   glTexCoord2f(1,0); glVertex3f(+1,-.4,-3);
   glTexCoord2f(1,1); glVertex3f(+.4,-1,-3);
   glTexCoord2f(0,1); glVertex3f(+.4,-1,-1);
   glEnd();
   //  Left
   glColor3f(0.5,0.5,0.5);
   if (ntex) glBindTexture(GL_TEXTURE_2D,texture[0]);
   glBegin(GL_QUADS);
   glNormal3f(-1, 0, 0);
   glTexCoord2f(0,0); glVertex3f(-1,-.4,-3);
   glTexCoord2f(1,0); glVertex3f(-1,-.4,-1);
   glTexCoord2f(1,1); glVertex3f(-1,+.4,-1);
   glTexCoord2f(0,1); glVertex3f(-1,+.4,-3);
   glEnd();
   glColor3f(0.5,0.5,0.5);
   if (ntex) glBindTexture(GL_TEXTURE_2D,texture[0]);
   glBegin(GL_QUADS);
   glNormal3f(-0.53, -0.53, 0);
   glTexCoord2f(0,0); glVertex3f(-1,-.4,-3);
   glTexCoord2f(1,0); glVertex3f(-1,-.4,-1);
   glTexCoord2f(1,1); glVertex3f(-.4,-1,-1);
   glTexCoord2f(0,1); glVertex3f(-.4,-1,-3);
   glEnd();
   glColor3f(0.5,0.5,0.5);
   if (ntex) glBindTexture(GL_TEXTURE_2D,texture[0]);
   glBegin(GL_QUADS);
   glNormal3f(-0.53, +0.53, 0);
   glTexCoord2f(0,0); glVertex3f(-.4,+1,-3);
   glTexCoord2f(1,0); glVertex3f(-.4,+1,-1);
   glTexCoord2f(1,1); glVertex3f(-1,+.4,-1);
   glTexCoord2f(0,1); glVertex3f(-1,+.4,-3);
   glEnd();
   //top
   glColor3f(0.5,0.5,0.5);
   if (ntex) glBindTexture(GL_TEXTURE_2D,texture[0]);
   glBegin(GL_QUADS);
   glNormal3f( 0,+1, 0);
   glTexCoord2f(0,0); glVertex3f(-.4,+1,-1);
   glTexCoord2f(1,0); glVertex3f(+.4,+1,-1);
   glTexCoord2f(1,1); glVertex3f(+.4,+1,-3);
   glTexCoord2f(0,1); glVertex3f(-.4,+1,-3);
   glEnd();
   //  Bottom
   glColor3f(0.5,0.5,0.5);
   if (ntex) glBindTexture(GL_TEXTURE_2D,texture[0]);
   glBegin(GL_QUADS);
   glNormal3f( 0,-1, 0);
   glTexCoord2f(0,0); glVertex3f(-.4,-1,-3);
   glTexCoord2f(1,0); glVertex3f(+.4,-1,-3);
   glTexCoord2f(1,1); glVertex3f(+.4,-1,-1);
   glTexCoord2f(0,1); glVertex3f(-.4,-1,-1);
   glEnd();





   //  Undo transformations and textures
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}

/*
 *  Draw a ball
 *     at (x,y,z)
 *     radius r
 */
static void ball(double x,double y,double z,double r)
{
   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glScaled(r,r,r);
   //  White ball
   glColor3f(1,1,1);
   glutSolidSphere(1.0,16,16);
   //  Undo transofrmations
   glPopMatrix();
}

/*
 *  OpenGL (GLUT) calls this routine to display the scene
 */
void display()
{
   //  Length of axes
   const double len=2.0;
   //  Eye position
   double Ex = -2*dim*Sin(th)*Cos(ph);
   double Ey = +2*dim        *Sin(ph);
   double Ez = +2*dim*Cos(th)*Cos(ph);
   //  Erase the window and the depth buffer
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   //  Enable Z-buffering in OpenGL
   glEnable(GL_DEPTH_TEST);
   //  Set perspective
   glLoadIdentity();
   gluLookAt(Ex,Ey,Ez , 0,0,0 , 0,Cos(ph),0);
   //  Light switch
   if (light)
   {
      //  Translate intensity to color vectors
      float Ambient[]   = {0.01*ambient ,0.01*ambient ,0.01*ambient ,1.0};
      float Diffuse[]   = {0.01*diffuse ,0.01*diffuse ,0.01*diffuse ,1.0};
      float Specular[]  = {0.01*specular,0.01*specular,0.01*specular,1.0};
      //  Light direction
      float Position[]  = {20*Cos(zh),ylight,20*Sin(zh),1};
      //float Position[]  = {-2,6,-8};
      //  Draw light position as ball (still no lighting here)
      glColor3f(1,1,1);
      ball(Position[0],Position[1],Position[2] , 0.1);
      //  OpenGL should normalize normal vectors
      glEnable(GL_NORMALIZE);
      //  Enable lighting
      glEnable(GL_LIGHTING);
      //  glColor sets ambient and diffuse color materials
      glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
      glEnable(GL_COLOR_MATERIAL);
      //  Enable light 0
      glEnable(GL_LIGHT0);
      //  Set ambient, diffuse, specular components and position of light 0
      glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
      glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);
      glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
      glLightfv(GL_LIGHT0,GL_POSITION,Position);
   }
   else
      glDisable(GL_LIGHTING);
   //  Draw scene

   powerrack(0,0,0);
   barbell(0,0,3);
   plate(0,3,0,45);
   plate(0,6,0,25);
   plate(0,9,0,10);
   plate(0,12,0,5);
   plate(0,15,0,2.5);
   

   //rect(x+7,y+5,z-6,0.2,5,0.3,0);

   dumbell(9,0,0 , 0.5,0.5,0.5 , 270);
   dumbell(9,0,-1 , 0.4,0.4,0.4 , 270);
   dumbell(9,0,-2 , 0.3,0.3,0.3 , 270);
   
   //  Draw axes - no lighting from here on
   glDisable(GL_LIGHTING);
   glColor3f(1,1,1);
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
   //  Display parameters
   glWindowPos2i(5,5);
   Print("Angle=%d,%d  Dim=%.1f Light=%s Texture=%s",th,ph,dim,light?"On":"Off",mode?"Replace":"Modulate");
   if (light)
   {
      glWindowPos2i(5,25);
      Print("Ambient=%d  Diffuse=%d Specular=%d Emission=%d Shininess=%.0f",ambient,diffuse,specular,emission,shiny);
   }
   //  Render the scene and make it visible
   ErrCheck("display");
   glFlush();
   glutSwapBuffers();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void idle()
{
   //  Elapsed time in seconds
   double t = glutGet(GLUT_ELAPSED_TIME)/1000.0;
   zh = fmod(90*t,360.0);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
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
   //  PageUp key - increase dim
   else if (key == GLUT_KEY_PAGE_DOWN)
      dim += 0.1;
   //  PageDown key - decrease dim
   else if (key == GLUT_KEY_PAGE_UP && dim>1)
      dim -= 0.1;
   //  Keep angles to +/-360 degrees
   th %= 360;
   ph %= 360;
   //  Update projection
   Project(45,asp,dim);
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
   //  Reset view angle
   else if (ch == '0')
      th = ph = 0;
   else if (ch == 'p')
      move = 1-move;
   else if (ch == 'c')
      zh += 3;
   else if (ch == 'v')
      zh -= 3;
   //  Toggle texture mode
   else if (ch == 'm' || ch == 'M')
      mode = 1-mode;
   //  Toggle axes
   else if (ch == 'x' || ch == 'X')
      axes = 1-axes;
   //  Toggle lighting
   else if (ch == 'l' || ch == 'L')
      light = 1-light;
   //  Toggle textures mode
   else if (ch == 't')
      ntex = 1-ntex;
   //  Light elevation
   else if (ch=='[')
      ylight -= 0.1;
   else if (ch==']')
      ylight += 0.1;
   //  Ambient level
   else if (ch=='a' && ambient>0)
      ambient -= 5;
   else if (ch=='A' && ambient<100)
      ambient += 5;
   //  Diffuse level
   else if (ch=='d' && diffuse>0)
      diffuse -= 5;
   else if (ch=='D' && diffuse<100)
      diffuse += 5;
   //  Specular level
   else if (ch=='s' && specular>0)
      specular -= 5;
   else if (ch=='S' && specular<100)
      specular += 5;
   //  Emission level
   else if (ch=='e' && emission>0)
      emission -= 5;
   else if (ch=='E' && emission<100)
      emission += 5;
   //  Shininess level
   else if (ch=='n' && shininess>-1)
      shininess -= 1;
   else if (ch=='N' && shininess<7)
      shininess += 1;
   //  Repitition
   else if (ch=='+')
      rep++;
   else if (ch=='-' && rep>1)
      rep--;
   //  Translate shininess power to value (-1 => 0)
   shiny = shininess<0 ? 0 : pow(2.0,shininess);
   //  Reproject
   Project(45,asp,dim);
   //  Tell GLUT it is necessary to redisplay the scene
   glutIdleFunc(move?idle:NULL);
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void reshape(int width,int height)
{
   //  Ratio of the width to the height of the window
   asp = (height>0) ? (double)width/height : 1;
   //  Set the viewport to the entire window
   glViewport(0,0, width,height);
   //  Set projection
   Project(45,asp,dim);
}

/*
 *  Start up GLUT and tell it what to do
 */
int main(int argc,char* argv[])
{
   //  Initialize GLUT
   glutInit(&argc,argv);
   //  Request double buffered, true color window with Z buffering at 600x600
   glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   glutInitWindowSize(1200,1200);
   glutCreateWindow("Final Project Kieren Ng");
   //  Set callbacks
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutSpecialFunc(special);
   glutKeyboardFunc(key);
   glutIdleFunc(idle);
   //  Load textures
   texture[0] = LoadTexBMP("concrete.bmp");
   texture[1] = LoadTexBMP("smoothmetal.bmp");
   //  Pass control to GLUT so it can interact with the user
   ErrCheck("init");
   glutMainLoop();
   return 0;
}