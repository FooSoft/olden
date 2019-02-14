#ifndef GEOMETRY_H
#define GEOMETRY_H
//------------------------------------------------------------------------------
#include "header\gfx.h"

////////////////////////////////////////////////////////////////////////////////
//geometry class does geometry stuff
class Geometry
{
public:
   void drawRectangle(int,int,int,int,char);
   void fillZone(int,int,int,int,char);
   void drawHLine(int,int,int,char);
   void drawVLine(int,int,int,char);

   class GFX *parent;
   class Mq *top;

private:



};

//------------------------------------------------------------------------------
#endif