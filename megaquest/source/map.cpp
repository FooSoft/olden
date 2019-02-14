#include <stdlib.h>
#include <malloc.h>
#include "header\map.h"

////////////////////////////////////////////////////////////////////////////////
//draw a map
void Map::prepareCurrent(void)
{
   spawn.spawnMap(&current);

   //place player
   player.placeRandomly();
   player.setTexture(BASE_PLAYER+rand()%10);
   player.setHuman(true);

   //place enemies
   foe.placeRandomly();
   foe.setTexture(BASE_PLAYER+rand()%10);
   foe.setHuman(false);

   centerViewAt(player.getXCoord(),player.getYCoord());
   return;
}


////////////////////////////////////////////////////////////////////////////////
//center map view around map coordinates
void Map::centerViewAt(int x,int y)
{
   mapXOffset=x-(MAP_SHOW_WIDTH+MAP_SHOW_WIDTH%2)/2+1;
   mapYOffset=y-(MAP_SHOW_HEIGHT+MAP_SHOW_HEIGHT%2)/2+1;
   return;
}


////////////////////////////////////////////////////////////////////////////////
//scroll map around player
void Map::scrollDungeon(char direction)
{
   int texture1,texture2;
   int xtile,ytile;
   int xoffset[]={0,-1,0,1};
   int yoffset[]={-1,0,1,0};
   int xsprite,ysprite;
   int offset;

   for (offset=0; offset<=16; offset++)
   {
      //cycle through the map and draw it on the screen
      for (ytile=0; ytile<MAP_SHOW_HEIGHT; ytile++)
         for (xtile=0; xtile<MAP_SHOW_WIDTH; xtile++)
         {
            texture1=current.getLandscape(xtile+mapXOffset,ytile+mapYOffset);
            texture2=current.getLandscape(xtile+mapXOffset+xoffset[direction],ytile+mapYOffset+yoffset[direction]);
            top->gfx.art.coverTile(texture1,texture2,xtile*TILE_DIM,ytile*TILE_DIM,direction,offset);

            //move enemy citters, if necessary
            if ((xtile+mapXOffset+xoffset[direction]==foe.getXCoord())&&(ytile+mapYOffset+yoffset[direction]==foe.getYCoord()))
            {
               xsprite=(xtile+xoffset[direction])*TILE_DIM - xoffset[direction]*offset;
               ysprite=(ytile+yoffset[direction])*TILE_DIM - yoffset[direction]*offset;
               top->gfx.art.drawTile(foe.getTexture(),xsprite,ysprite);
            }

         }

      //delay screen drawing
      delay(SCROLL_DELAY);

      //draw player on screen
      if (player.isVisible())
         player.drawOnMap();

      //update display buffer
      top->gfx.drawBuffer();
   }

   return;
}


////////////////////////////////////////////////////////////////////////////////
//draw map on screen
void Map::drawDungeon(void)
{
   int atTileX,atTileY;
   int texture;

   //cycle through the map and draw it on the screen
   for (atTileY=0; atTileY<MAP_SHOW_HEIGHT; atTileY++)
      for (atTileX=0; atTileX<MAP_SHOW_WIDTH; atTileX++)
      {
         texture=current.getLandscape(atTileX+mapXOffset,atTileY+mapYOffset);
         top->gfx.art.drawTile(texture,atTileX*TILE_DIM,atTileY*TILE_DIM);
      }

   if (player.isVisible())
      player.drawOnMap();

   if (foe.isVisible())
      foe.drawOnMap();

   top->gfx.drawBuffer();
   return;
}


////////////////////////////////////////////////////////////////////////////////
//check to see if critter can be placed at coords
bool Map::allowCritterAt(int x,int y)
{
   int style=current.getFlag(x,y);
   bool good=true;

   //check clipping
   if(style&FLAG_CLIP)
      good=false;

   //make sure that the player is not a destination
   if ((player.getXCoord()==x)&&(player.getYCoord()==y))
      good=false;

   //make sure there are no enemies at destination
   if ((foe.getXCoord()==x)&&(foe.getYCoord()==y))
      good=false;

   return good;
}


////////////////////////////////////////////////////////////////////////////////
//check to see if coordinates are valid for this map size
bool Map::isValidRange(int x,int y)
{
   return bool((x>=0)&&(x<MAP_WIDTH)&&(y>=0)&&(y<MAP_HEIGHT));
}


////////////////////////////////////////////////////////////////////////////////
//get map x offset
int Map::getXOffset(void)
{
   return mapXOffset;
}


////////////////////////////////////////////////////////////////////////////////
//get map y offset
int Map::getYOffset(void)
{
   return mapYOffset;
}


