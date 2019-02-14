#include <stdio.h>
#include "header\geometry.h"

////////////////////////////////////////////////////////////////////////////////
//draw a rectangle
void Geometry::drawRectangle(int x1,int y1,int x2,int y2,char color)
{
   drawHLine(x1,y1,x2-x1,color);
   drawHLine(x1,y2,x2-x1,color);
   drawVLine(x1,y1,y2-y1,color);
   drawVLine(x2,y1,y2-y1,color);
   return;
}


////////////////////////////////////////////////////////////////////////////////
//flood fill a zone with a color
void Geometry::fillZone(int x1,int y1,int x2,int y2,char color)
{
   int x,y;
   for (x=0; x<=(x2-x1); x++)
      for (y=0; y<=(y2-y1); y++)
         parent->putPixel(x+x1,y+y1,color);

   return;
}


////////////////////////////////////////////////////////////////////////////////
//draw horizontal line on the screen
void Geometry::drawHLine(int x,int y,int length,char color)
{
   int xcycle;
   for (xcycle=0; xcycle<=length; xcycle++)
      parent->putPixel(x+xcycle,y,color);
   return;
}


////////////////////////////////////////////////////////////////////////////////
//draw vertical line on the screen
void Geometry::drawVLine(int x,int y,int length,char color)
{
   int ycycle;
   for (ycycle=0; ycycle<=length; ycycle++)
      parent->putPixel(x,y+ycycle,color);
   return;
}
