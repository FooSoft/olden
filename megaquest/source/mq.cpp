#include <stdlib.h>
#include <time.h>
#include <dos.h>
#include "header\mq.h"

////////////////////////////////////////////////////////////////////////////////
//megaquest constructor
Mq::Mq(void)
{
   printf("MegaQuest Engine Build on %s at %s\n",__DATE__,__TIME__);

   //seed random number generator
   srand((unsigned)time(NULL));

   //set parent and top properties for children
   gfx.parent=this;
   gfx.bitmap.parent=&gfx;
   gfx.bitmap.top=this;
   gfx.dialog.parent=&gfx;
   gfx.dialog.top=this;
   gfx.textdraw.parent=&gfx;
   gfx.textdraw.top=this;
   gfx.art.parent=&gfx;
   gfx.art.top=this;
   gfx.geometry.parent=&gfx;
   gfx.geometry.top=this;

   game.parent=this;
   input.parent=this;

   logic.parent=this;
   logic.map.parent=&logic;
   logic.map.top=this;

   logic.map.player.parent=&logic.map;
   logic.map.player.top=this;
   logic.map.foe.parent=&logic.map;
   logic.map.foe.top=this;

   logic.map.spawn.parent=&logic.map;
   logic.map.spawn.top=this;
   logic.map.current.parent=&logic.map;
   logic.map.current.top=this;

   delay(750);
   return;
}


////////////////////////////////////////////////////////////////////////////////
//megaquest destructor
Mq::~Mq(void)
{


   return;
}
