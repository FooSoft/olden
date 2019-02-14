#ifndef ART_H
#define ART_H
//------------------------------------------------------------------------------
#include "header\data\tiledata.h"
#include "header\critter.h"

////////////////////////////////////////////////////////////////////////////////
//art class does high level graphical stuff
class Art
{
public:
   Art(void);
   ~Art(void);
   void coverTile(int,int,int,int,char,int);
   void slideTile(int,int,int,int,int,char);
   void drawTile(int,int,int);
   void getTile(Bmp,int,Tile*);
   bool indexTiles(void);
   bool loadTiles(void);

   class GFX *parent;
   class Mq *top;

private:
   Tile *tiles;
   Bmp dungeonTiles;
   Bmp critterTiles;
};

//------------------------------------------------------------------------------
#endif