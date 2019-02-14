#ifndef TEXTDRAW_H
#define TEXTDRAW_H
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
//this class is used specifially for writing text in 0x13 graphics mode
class Textdraw
{
public:
   Textdraw(void);
   void setStatus(char[]);
   void drawString(int,int,char,char,char[]);
   void drawShadowString(int,int,char,char,char,char[]);
   void drawLetter(int,int,char,char,char);
   void drawShadowLetter(int,int,char,char,char,char);

   class GFX *parent;
   class Mq *top;

private:
   char *fontData;
   
};

//------------------------------------------------------------------------------
#endif