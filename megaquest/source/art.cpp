#include <stdlib.h>
#include <stdio.h>
#include <alloc.h>
#include "header\art.h"

////////////////////////////////////////////////////////////////////////////////
//art constructor
Art::Art(void)
{
   //load tile library
   if (!loadTiles())
   {
      printf("Unable to open open one or more tile libraries\n");
      exit(EXIT_FAILURE);
   }

   //index tiles
   if (!indexTiles())
   {
      printf("Unable to index tile libraries\n");
      exit(EXIT_FAILURE);
   }
   
   return;
}


////////////////////////////////////////////////////////////////////////////////
//art destructor
Art::~Art(void)
{
   //free space used for bitmap storage
   free(critterTiles.pixels);
   free(dungeonTiles.pixels);

   //free space for storing tiles
   farfree(tiles);
   return;
}


////////////////////////////////////////////////////////////////////////////////
//cover a portion of a tile with another tile
void Art::coverTile(int tile1,int tile2,int xscreen,int yscreen,char direction,int overlap)
{
   char tilePixel;
   int x,y;

   //tile1 is sliding to the north
   //y - overlap + TILE_DIM
   if (direction==NORTH)
      for (y=0; y<TILE_DIM; y++)
         for (x=0; x<TILE_DIM; x++)
         {
            if(y>=overlap)
               tilePixel=tiles[tile1].pixels[CART(x,y-overlap,TILE_DIM)];
            else
               tilePixel=tiles[tile2].pixels[CART(x,y-overlap+TILE_DIM,TILE_DIM)];
            parent->putPixel(x+xscreen+POS_MAP_X,y+yscreen+POS_MAP_Y,tilePixel);
         }

   //tile1 is sliding to the south
   //y + overlap - TILE_DIM
   if (direction==SOUTH)
      for (y=0; y<TILE_DIM; y++)
         for (x=0; x<TILE_DIM; x++)
         {
            if (y<TILE_DIM-overlap)
               tilePixel=tiles[tile1].pixels[CART(x,y+overlap,TILE_DIM)];
            else
               tilePixel=tiles[tile2].pixels[CART(x,y+overlap-TILE_DIM,TILE_DIM)];
            parent->putPixel(x+xscreen+POS_MAP_X,y+yscreen+POS_MAP_Y,tilePixel);
         }

   //tile1 is sliding to the east
   //x + overlap - TILE_DIM
   if (direction==EAST)
      for (y=0; y<TILE_DIM; y++)
         for (x=0; x<TILE_DIM; x++)
         {
            if (x<TILE_DIM-overlap)
               tilePixel=tiles[tile1].pixels[CART(x+overlap,y,TILE_DIM)];
            else
               tilePixel=tiles[tile2].pixels[CART(x+overlap-TILE_DIM,y,TILE_DIM)];               
            parent->putPixel(x+xscreen+POS_MAP_X,y+yscreen+POS_MAP_Y,tilePixel);
         }

   //tile1 is sliding to the west
   //x - overlap + TILE_DIM
   if (direction==WEST)
      for (y=0; y<TILE_DIM; y++)
         for (x=0; x<TILE_DIM; x++)
         {
            if (x>=overlap)
               tilePixel=tiles[tile1].pixels[CART(x-overlap,y,TILE_DIM)];
            else
               tilePixel=tiles[tile2].pixels[CART(x-overlap+TILE_DIM,y,TILE_DIM)];
            parent->putPixel(x+xscreen+POS_MAP_X,y+yscreen+POS_MAP_Y,tilePixel);
         }

   return;
}


////////////////////////////////////////////////////////////////////////////////
//slide a tile
void Art::slideTile(int tile1,int tile2,int tile3,int xscreen,int yscreen,char direction)
{
   int xoffset[]={0,-1,0,1};
   int yoffset[]={-1,0,1,0};
   int x,y;

   //vertical sliding
   if ((direction==SOUTH)||(direction==NORTH))
      for (y=x=0; y<=abs(yoffset[direction]*TILE_DIM); y++)
      {
         drawTile(tile1,xscreen,yscreen);
         drawTile(tile2,xscreen+(signed)(xoffset[direction]*TILE_DIM),yscreen+(signed)(yoffset[direction]*TILE_DIM));
         drawTile(tile3,xscreen,yscreen+(signed)(yoffset[direction]*y));
         delay(SLIDE_DELAY);
         parent->drawBuffer();
      }

   //horizontal sliding
   if ((direction==WEST)||(direction==EAST))
      for (y=x=0; x<=abs(xoffset[direction]*TILE_DIM); x++)
      {
         drawTile(tile1,xscreen,yscreen);
         drawTile(tile2,xscreen+(signed)(xoffset[direction]*TILE_DIM),yscreen+(signed)(yoffset[direction]*TILE_DIM));
         drawTile(tile3,xscreen+(signed)(xoffset[direction]*x),yscreen);
         delay(SLIDE_DELAY);
         parent->drawBuffer();
      }

   return;
}


////////////////////////////////////////////////////////////////////////////////
//display a particular tile on the screen
void Art::drawTile(int index,int xscreen,int yscreen)
{
   int x,y;
   char tilePixel;

   for (y=0; y<TILE_DIM; y++)
      for (x=0; x<TILE_DIM; x++)
      {
         tilePixel=tiles[index].pixels[CART(x,y,TILE_DIM)];
         parent->putPixel(x+xscreen+POS_MAP_X,y+yscreen+POS_MAP_Y,tilePixel);
      }

   return;
}


////////////////////////////////////////////////////////////////////////////////
//get a tile from a bitmap structure at index
void Art::getTile(Bmp bitmap,int index,Tile *tile)
{
   int xtile=(index%(bitmap.width/TILE_DIM))*TILE_DIM;
   int ytile=(index/(bitmap.width/TILE_DIM))*TILE_DIM;
   char tilePixel;
   int x,y;

   for (y=0; y<TILE_DIM; y++)
      for (x=0; x<TILE_DIM; x++)
      {
         tilePixel=bitmap.pixels[CART(xtile+x,ytile+y,bitmap.width)];
         tile->pixels[CART(x,y,TILE_DIM)]=tilePixel;
      }

   return;
}


////////////////////////////////////////////////////////////////////////////////
//index all the tiles in one huge array
bool Art::indexTiles(void)
{
   int ctiles,dtiles,cycle,save=0;

   //count number of tiles in each bitmap
   ctiles=critterTiles.size/256;
   dtiles=dungeonTiles.size/256;

   //allocate memory for tiles
   tiles=(Tile far*)farcalloc(ctiles+dtiles,sizeof(Tile));
   if (tiles==NULL)
      return false;

   //get dungeon tiles
   for (cycle=0; cycle<dtiles; cycle++)
      getTile(dungeonTiles,cycle,&tiles[save++]);

   //get critter tiles
   for (cycle=0; cycle<ctiles; cycle++)
      getTile(critterTiles,cycle,&tiles[save++]);

   return true;
}


////////////////////////////////////////////////////////////////////////////////
//load tile files
bool Art::loadTiles(void)
{
   bool success=true;

   success&=parent->bitmap.load(TILE_LIB_DUNGEON,&dungeonTiles);
   success&=parent->bitmap.load(TILE_LIB_CRITTER,&critterTiles);

   return success;
}
