#include <stdlib.h>
#include "header\game.h"

////////////////////////////////////////////////////////////////////////////////
//game constructor prepares i/o routines
Game::Game(void)
{
   parent->input.setTypematic(TYPE_DELAY,TYPE_RATE);
   return;
}


////////////////////////////////////////////////////////////////////////////////
//run the game's interaction routines, start the game
void Game::interact(void)
{
   int ans;

   //prepare stuff
   parent->logic.map.prepareCurrent();
   parent->logic.map.drawDungeon();
   parent->gfx.textdraw.setStatus("MegaQuest");

   do
   {
      //get keyboard hit from player
      ans=parent->input.getExtended();

      //move player around
      if (ans==UP_ARROW)
         parent->logic.map.player.moveInDirection(NORTH);
      if (ans==LEFT_ARROW)
         parent->logic.map.player.moveInDirection(WEST);
      if (ans==RIGHT_ARROW)
         parent->logic.map.player.moveInDirection(EAST);
      if (ans==DOWN_ARROW)
         parent->logic.map.player.moveInDirection(SOUTH);

      //generate a new dungeon
      if (ans==FUNC1)
      {
         parent->logic.map.prepareCurrent();
         parent->logic.map.drawDungeon();
      }

      //move enemies around on map
      if (ans==FUNC2)
         parent->logic.map.foe.moveInDirection(rand()%4);
   }
   while (ans!=ESCAPE);

   return;
}
