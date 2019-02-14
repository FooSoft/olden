#ifndef BITMAP_H
#define BITMAP_H
//------------------------------------------------------------------------------
#include "header\data\bmpdata.h"

////////////////////////////////////////////////////////////////////////////////
//this class is used for bitmap loading and manipulation
class Bitmap
{
public:
   void draw(unsigned,unsigned,Bmp);
   bool save(char[],Bmp);
   bool load(char[],Bmp*);

   class GFX *parent;
   class Mq *top;

private:

};

//------------------------------------------------------------------------------
#endif