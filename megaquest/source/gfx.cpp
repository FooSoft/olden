#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <mem.h>
#include "header\gfx.h"

////////////////////////////////////////////////////////////////////////////////
//GFX constructor prepares class for usage
GFX::GFX(void)
{
   //create pointer to vga
   vga=(char*)MK_FP(0xa000,0x0000);

   //store old display mode
   oldDisplayMode=getDisplayMode();

   //allocate memory for double buffer
   buffer=(char*)malloc(SCREEN_WIDTH*SCREEN_HEIGHT);
   if (buffer==NULL)
   {
      printf("Insufficient memory for double-buffering\n");
      exit(EXIT_FAILURE);
   }

   //load palette file
   if (!loadPalette(PAL_LIST))
   {
      printf("Unable to load palette\n");
      exit(EXIT_FAILURE);
   }

   return;
}


////////////////////////////////////////////////////////////////////////////////
//GFX destructor does cleanup
GFX::~GFX(void)
{
   //free memory used by GFX class
   free(buffer);
   free(palette);

   return;
}


////////////////////////////////////////////////////////////////////////////////
//set graphics mode
void GFX::startGraphics(void)
{
   //set graphics mode
   setDisplayMode(GFX_MODE);

   //set default display colors and palette
   setPalette(palette);
   setBorderColor(BORDER_COLOR);
   clearBuffer();
   drawBuffer();
   return;
}


////////////////////////////////////////////////////////////////////////////////
//return to old graphics mode
void GFX::stopGraphics(void)
{
   //if video mode has not been restored, do it here
   if (getDisplayMode()!=oldDisplayMode)
      setDisplayMode(oldDisplayMode);
      
   return;
}


////////////////////////////////////////////////////////////////////////////////
//set video display mode (text/graphics)
void GFX::setDisplayMode(char mode)
{
   union REGS regs;
   regs.h.ah=0x00;
   regs.h.al=mode;
   int86(0x10,&regs,&regs);
   return;
}


////////////////////////////////////////////////////////////////////////////////
//get current display mode
char GFX::getDisplayMode(void)
{
   union REGS regs;
   regs.h.ah=0x0f;
   int86(0x10,&regs,&regs);
   return regs.h.al;
}


////////////////////////////////////////////////////////////////////////////////
//put a pixel onto the screen
inline void GFX::putPixel(int x,int y,char color)
{
   if (color!=TRANS)
      buffer[(unsigned)(SCART(x,y))]=color;
   return;
}


////////////////////////////////////////////////////////////////////////////////
//get a pixel's color off the screen
inline char GFX::getPixel(int x,int y)
{
   char color;
   color=buffer[(unsigned)(SCART(x,y))];
   return color;
}


////////////////////////////////////////////////////////////////////////////////
//fade colors from one palette to another
void GFX::fadePalette(char currpal[],char newpal[])
{
   int swatch;

   //keep on tweaking palette until it is just right
   while (memcmp(currpal,newpal,256*3)!=0)
   {
      //cycle through swatches
      for (swatch=0; swatch<256*3; swatch++)
         if (currpal[swatch]!=newpal[swatch])
         {
            if (currpal[swatch]>newpal[swatch])
               currpal[swatch]--;

            if (currpal[swatch]<newpal[swatch])
               currpal[swatch]++;
         }

      //update current palette
      setPalette(currpal);
      delay(FADE_DELAY);
   }

   return;
}


////////////////////////////////////////////////////////////////////////////////
//set color palette
void GFX::setPalette(const char palette[])
{
   int swatch;

   //set bitmap and custom colors
   outp(0x03c8,0);
   for (swatch=0; swatch<256*3; swatch++)
      outp(0x03c9,palette[swatch]);

   return;
}


////////////////////////////////////////////////////////////////////////////////
//get current color palette
void GFX::getPalette(char palette[])
{
   int swatch;

   outp(0x3C7,0);
   for (swatch=0; swatch<256*3; swatch++)
      palette[swatch]=inp(0x3c9);

   return;
}


////////////////////////////////////////////////////////////////////////////////
//load color palette from a file
bool GFX::loadPalette(char filename[])
{
   int byte;
   FILE *fp;

   //open palette file
   fp=fopen(filename,"rb");
   if (fp==NULL)
      return false;

   //allocate memory for palette
   palette=(char*)malloc(256*3);
   if (palette==NULL)
      return false;

   //find out how many colors are in palette
   fseek(fp,768,SEEK_SET);
   fread(&colors,1,sizeof(int),fp);
   colors/=256;
   rewind(fp);

   //read palette
   for (byte=0; byte<256*3; byte++)
      palette[byte]=(byte<colors*3)?(fgetc(fp)/4):0;

   fclose(fp);
   return true;
}


////////////////////////////////////////////////////////////////////////////////
//change the color of the screen border
void GFX::setBorderColor(char color)
{
   union REGS regs;
   regs.h.ah=0x10;
   regs.h.al=0x01;
   regs.h.bh=color;
   int86(0x10,&regs,&regs);
   return;
}


////////////////////////////////////////////////////////////////////////////////
//draw the contents of the buffer onto the screen
void GFX::drawBuffer(void)
{
   //wait until done with vertical retrace
   while  ((inp(0x03da)&0x08));
   //wait until done refreshing
   while (!(inp(0x03da)&0x08));
   //copy contents of buffer to vga
   memcpy(vga,buffer,320*200);
   return;
}


////////////////////////////////////////////////////////////////////////////////
//set buffer to one constant to clear it
void GFX::clearBuffer()
{
   memset(buffer,BACK_COLOR,SCREEN_WIDTH*SCREEN_HEIGHT);
   return;
}

