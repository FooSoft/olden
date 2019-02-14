#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "header\textdraw.h"

////////////////////////////////////////////////////////////////////////////////
//load pointer for font data
Textdraw::Textdraw(void)
{
   fontData=(char*)MK_FP(0xf000,0xfa6e);
   return;
}


////////////////////////////////////////////////////////////////////////////////
//set statusbar text
void Textdraw::setStatus(char string[])
{
   drawString(POS_STATUS_X,POS_STATUS_Y,SILVER,GRAY,string);
   parent->drawBuffer();
   return;
}


////////////////////////////////////////////////////////////////////////////////
//draw string at coords
void Textdraw::drawString(int xbase,int ybase,char fgcolor,char bgcolor,char string[])
{
   int vletter,hletter;
   int atLetter;

   for (atLetter=0,hletter=0,vletter=0; atLetter<strlen(string); atLetter++)
   {
      if ( (isalnum(string[atLetter])) || (ispunct(string[atLetter])) || (string[atLetter]==' ') )
         drawLetter(xbase+(hletter++)*LETTER_WIDTH,ybase+vletter*LETTER_HEIGHT,fgcolor,bgcolor,string[atLetter]);

      else if (string[atLetter]=='\n')
      {
         hletter=0;
         vletter++;
      }

   }

   return;
}


////////////////////////////////////////////////////////////////////////////////
//draw a shadow string at coords
void Textdraw::drawShadowString(int xbase,int ybase,char fgcolor,char bgcolor,char shcolor,char string[])
{
   int atLetter;

   for (atLetter=0; atLetter<strlen(string); atLetter++)
      drawShadowLetter(xbase+atLetter*LETTER_WIDTH,ybase,fgcolor,bgcolor,shcolor,string[atLetter]);

   return;
}


////////////////////////////////////////////////////////////////////////////////
//draw letter at coords
void Textdraw::drawLetter(int xbase,int ybase,char fgcolor,char bgcolor,char letter)
{
   unsigned x,y;
   unsigned fontOffset=letter*8;
   char useColor;
   int byte,bit;

   for (byte=0,y=0; byte<8; byte++,y++)
      for (bit=128,x=0; bit>=1; bit/=2,x++)
      {
         useColor=(fontData[byte+fontOffset]&bit)?fgcolor:bgcolor;
         if (useColor!=TRANS)
            parent->putPixel(xbase+x,ybase+y,useColor);
      }

   return;
}


////////////////////////////////////////////////////////////////////////////////
//draw shadow letter at coords
void Textdraw::drawShadowLetter(int xbase,int ybase,char fgcolor,char bgcolor,char shcolor,char letter)
{
   int x,y;
   int fontOffset=letter*8;
   int byte,bit;

   for (byte=0,y=0; byte<8; byte++,y++)
      for (bit=128,x=0; bit>=1; bit/=2,x++)
      {
         if (fontData[byte+fontOffset]&bit)
         {
            if (shcolor!=TRANS)
               parent->putPixel(xbase+x+1,ybase+y+1,shcolor);
            if (fgcolor!=TRANS)
               parent->putPixel(xbase+x,ybase+y,fgcolor);
         }

         else if (parent->getPixel(xbase+x,ybase+y)!=shcolor)
            if (bgcolor!=TRANS)
               parent->putPixel(xbase+x,ybase+y,bgcolor);
      }

   return;
}

