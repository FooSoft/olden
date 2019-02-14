#include <string.h>
#include "header\dialog.h"

////////////////////////////////////////////////////////////////////////////////
//draw a basic dialog on the screen
void Dialog::drawInfoDialog(char text[],char hpos,char vpos)
{
   int x1,y1,x2,y2;
   int textHeight,textWidth;
   getTextDim(text,&textWidth,&textHeight);
   getCoords(textWidth,textHeight,&x1,&y1,&x2,&y2,hpos,vpos);

   //draw text
   drawTextBox(x1,y1,(x2-x1)/8,(y2-y1)/8,text,DLG_FORE,DLG_BACK,DLG_BORDER,PADDING);
   parent->drawBuffer();
   
   return;
}


////////////////////////////////////////////////////////////////////////////////
//draw a box with text in it
void Dialog::drawTextBox(int x,int y,int width,int height,char text[],char fgcolor,char bgcolor,char bordercolor,int padding)
{
   int x1,y1,x2,y2;
   x1=x; y1=y;
   x2=x+width*LETTER_WIDTH+padding;
   y2=y+height*LETTER_HEIGHT+padding;

   parent->geometry.drawRectangle(x1,y1,x2,y2,bordercolor);
   parent->geometry.fillZone(x1+1,y1+1,x2-1,y2-1,bgcolor);
   parent->textdraw.drawString(x1+(padding/2)+1,y1+(padding/2)+1,fgcolor,bgcolor,text);

   return;
}


////////////////////////////////////////////////////////////////////////////////
//get coordinates for dialog
void Dialog::getCoords(int width,int height,int *x1,int *y1,int *x2,int *y2,char hpos,char vpos)
{
   int xbonus=PADDING+1;
   int ybonus=PADDING+1;

   //horizontal align left
   if (hpos==POS_LEFT)
      *x1=xbonus;
   //horizontal align center
   else if (hpos==POS_CENTER)
      *x1=(SCREEN_WIDTH-(width+xbonus))/2;
   //horizontal align right
   else if (hpos==POS_RIGHT)
      *x1=SCREEN_WIDTH-(width+xbonus*2);

   //vertical align top
   if (vpos==POS_TOP)
      *y1=ybonus;
   //vertical align middle
   else if (vpos==POS_MIDDLE)
      *y1=(SCREEN_HEIGHT-(height+ybonus))/2;
   //vertical align right
   else if (vpos==POS_BOTTOM)
      *y1=SCREEN_HEIGHT-(height+ybonus*2);

   //calculate ending coordinates
   *x2=*x1+xbonus+width+1;
   *y2=*y1+ybonus+height+1;
   return;
}

////////////////////////////////////////////////////////////////////////////////
//get dimentions for current string
void Dialog::getTextDim(char text[],int *xsize,int *ysize)
{
   int atChar;
   *xsize=0;
   *ysize=LETTER_HEIGHT;

   for (atChar=0; atChar<strlen(text); atChar++)
   {
      if (text[atChar]!='\n')
         *xsize+=LETTER_WIDTH;
      else if (text[atChar]=='\n')
         *ysize+=LETTER_HEIGHT;
   }

   return;
}
