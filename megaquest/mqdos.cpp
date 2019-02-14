#include <stdio.h>
#include <conio.h>
//------------------------------------------------------------------------------
#include "header\defines.h"
#include "source\mq.cpp"
//------------------------------------------------------------------------------
#include "source\gfx.cpp"
#include "source\geometry.cpp"
#include "source\textdraw.cpp"
#include "source\dialog.cpp"
#include "source\bitmap.cpp"
#include "source\art.cpp"
//------------------------------------------------------------------------------
#include "source\game.cpp"
#include "source\input.cpp"
//------------------------------------------------------------------------------
#include "source\logic.cpp"
#include "source\map.cpp"
#include "source\data\mapdata.cpp"
#include "source\spawn.cpp"
#include "source\critter.cpp"

//global variables
Mq mq;

//program entry point
int main(void)
{
   Bmp menu;
   mq.gfx.startGraphics();

   //draw menu background
   mq.gfx.bitmap.load("images\\menu.bmp",&menu);
   mq.gfx.bitmap.draw(0,0,menu);
   mq.gfx.drawBuffer();
   mq.game.interact();

   mq.gfx.stopGraphics();
   return 0;
}

