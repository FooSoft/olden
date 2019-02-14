#ifndef MAP_H
#define MAP_H
//------------------------------------------------------------------------------
#include "header\data\mapdata.h"
#include "header\spawn.h"
#include "header\critter.h"

////////////////////////////////////////////////////////////////////////////////
//this class deals with everything related to maps
class Map
{
public:
   void prepareCurrent(void);
   void centerViewAt(int,int);
   void scrollDungeon(char);
   void drawDungeon(void);
   bool allowCritterAt(int,int);
   bool isValidRange(int,int);

   int getXOffset(void);
   int getYOffset(void);
   class Logic *parent;
   class Mq *top;
   Critter player;
   Critter foe;
   Spawn spawn;
   Mapdata current;

private:
   int mapXOffset;
   int mapYOffset;
};

//------------------------------------------------------------------------------
#endif