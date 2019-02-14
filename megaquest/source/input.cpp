#include <conio.h>
#include "header\input.h"

////////////////////////////////////////////////////////////////////////////////
//get extended keystrokes from user
int Input::getExtended(void)
{
   //flush out any previous characters in buffer
   while (kbhit())
      getch();
      
   //get scan code
   union REGS regs;
   regs.h.ah=0x10;
   int86(0x16,&regs,&regs);
   return regs.h.ah;
}


////////////////////////////////////////////////////////////////////////////////
//set typematic rate (delay and rate)
void Input::setTypematic(char delay,char rate)
{
   union REGS regs;
   regs.h.al=0x05;
   regs.h.bh=delay;
   regs.h.bl=rate;
   int86(0x16,&regs,&regs);
   return;
}
