#ifndef DIALOG_H
#define DIALOG_H
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
//this class is in charge of drawing dialog boxes
class Dialog
{
public:
   void drawInfoDialog(char[],char,char);
   void drawTextBox(int,int,int,int,char[],char,char,char,int);
   void getCoords(int,int,int*,int*,int*,int*,char,char);
   void getTextDim(char[],int*,int*);

   class GFX *parent;
   class Mq *top;

private:


};

//------------------------------------------------------------------------------
#endif