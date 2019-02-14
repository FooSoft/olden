#include <stdlib.h>
#include "header\critter.h"

////////////////////////////////////////////////////////////////////////////////
//draw critter on the map
void Critter::drawOnMap(void)
{
   top->gfx.art.drawTile(texture,(xloc-parent->getXOffset())*TILE_DIM,(yloc-parent->getYOffset())*TILE_DIM);
   return;
}


////////////////////////////////////////////////////////////////////////////////
//see if critter can move in given direction
bool Critter::allowMove(char direction)
{
   int offsetX[]={0,-1,0,1};
   int offsetY[]={-1,0,1,0};
   return parent->allowCritterAt(xloc+offsetX[direction],yloc+offsetY[direction]);
}


////////////////////////////////////////////////////////////////////////////////
//determine if critter is visible in field of view
bool Critter::isVisible(void)
{
   int xvis,yvis;

   xvis=xloc-parent->getXOffset();
   yvis=yloc-parent->getYOffset();

   return bool((xvis>=0)&&(xvis<MAP_SHOW_WIDTH)&&(yvis>=0)&&(yvis<MAP_SHOW_HEIGHT));
}

////////////////////////////////////////////////////////////////////////////////
//update coordinates after moving in a direction
void Critter::coordMove(char direction)
{
   int offsetX[]={0,-1,0,1};
   int offsetY[]={-1,0,1,0};
   xloc+=offsetX[direction];
   yloc+=offsetY[direction];
   return;
}


////////////////////////////////////////////////////////////////////////////////
//move critter
bool Critter::moveInDirection(char direction)
{
   //check clipping at destination
   if (!allowMove(direction))
      return false;

   //different critter moving methods
   switch (isPlayer)
   {
   //only the player moves, used for NPCs
   case false:
      if (isVisible())
         slideView(direction);
      break;

   //whole map scrolls, used for PCs
   case true:
      centerView();
      parent->scrollDungeon(direction);
      break;
   }

   coordMove(direction);
   return true;
}


////////////////////////////////////////////////////////////////////////////////
//slide player around the map
void Critter::slideView(char direction)
{
   int texture1,texture2;
   int xoffset[]={0,-1,0,1};
   int yoffset[]={-1,0,1,0};

   texture1=parent->current.getLandscape(xloc,yloc);
   texture2=parent->current.getLandscape(xloc+xoffset[direction],yloc+yoffset[direction]);
   top->gfx.art.slideTile(texture1,texture2,texture,(xloc-parent->getXOffset())*TILE_DIM,(yloc-parent->getYOffset())*TILE_DIM,direction);

   return;
}


////////////////////////////////////////////////////////////////////////////////
//center view around current critter
void Critter::centerView(void)
{
   parent->centerViewAt(xloc,yloc);
   return;
}


////////////////////////////////////////////////////////////////////////////////
//place critter randomly on map
void Critter::placeRandomly(void)
{
   int x,y;

   //find an x,y pair that is not inside a wall
   do
   {
      x=rand()%MAP_WIDTH;
      y=rand()%MAP_HEIGHT;
   }
   while (!parent->allowCritterAt(x,y));

   //save critter location
   xloc=x;
   yloc=y;
   return;
}


////////////////////////////////////////////////////////////////////////////////
//get x coordinate of critter
int Critter::getXCoord(void)
{
   return xloc;
}


////////////////////////////////////////////////////////////////////////////////
//get y coordinate of critter
int Critter::getYCoord(void)
{
   return yloc;
}


////////////////////////////////////////////////////////////////////////////////
//set coordinates for critter
void Critter::setCoords(int x,int y)
{
   xloc=x;
   yloc=y;
   return;
}


////////////////////////////////////////////////////////////////////////////////
//get texture for current critter
int Critter::getTexture(void)
{
   return texture;
}


////////////////////////////////////////////////////////////////////////////////
//set texture for current critter
void Critter::setTexture(int useTexture)
{
   texture=useTexture;
   return;
}


////////////////////////////////////////////////////////////////////////////////
//set critter to be human or AI controlled
void Critter::setHuman(bool isHuman)
{
   isPlayer=isHuman;
   return;
}


////////////////////////////////////////////////////////////////////////////////
//determine who is controlling the critter
bool Critter::getHuman(void)
{
   return isPlayer;
}
