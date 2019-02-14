#ifndef GFX_H
#define GFX_H
//------------------------------------------------------------------------------
#include "header\geometry.h"
#include "header\dialog.h"
#include "header\bitmap.h"
#include "header\art.h"
#include "header\textdraw.h"

////////////////////////////////////////////////////////////////////////////////
//graphics class containing all of the functions used by program
class GFX
{
public:
   GFX(void);
   ~GFX(void);
   void startGraphics(void);
   void stopGraphics(void);
   
   void setDisplayMode(char mode);
   char getDisplayMode(void);
   inline void putPixel(int,int,char);
   inline char getPixel(int,int);
   void fadePalette(char[],char[]);
   void setPalette(const char[]);
   void getPalette(char[]);
   bool loadPalette(char[]);
   void setBorderColor(char);
   void drawBuffer(void);
   void clearBuffer(void);

   class Mq *parent;
   Dialog dialog;
   Textdraw textdraw;
   Geometry geometry;
   Bitmap bitmap;
   Art art;
   
private:
   char *vga;
   char *buffer;
   char *palette;

   char oldDisplayMode;
   int colors;
};

//------------------------------------------------------------------------------
#endif
