#include <stdlib.h>
#include "header\data\mapdata.h"

////////////////////////////////////////////////////////////////////////////////
//mapdata constructor
Mapdata::Mapdata(void)
{
   //allocate memory for the current map
   overlay=(int*)calloc(MAP_WIDTH*MAP_HEIGHT,sizeof(int));
   landscape=(int*)calloc(MAP_WIDTH*MAP_HEIGHT,sizeof(int));
   flags=(int*)calloc(MAP_WIDTH*MAP_HEIGHT,sizeof(int));

   //if not enough memory, bitch then exit
   if ((landscape==NULL)||(flags==NULL)||(overlay==NULL))
   {
      printf("Insufficient memory to generate map\n");
      exit(EXIT_FAILURE);
   }

   return;
}


////////////////////////////////////////////////////////////////////////////////
//mapdata destructor
Mapdata::~Mapdata(void)
{
   //free the space used by current map
   free(flags);
   free(landscape);
   free(overlay);
   return;
}


////////////////////////////////////////////////////////////////////////////////
//get landscape at coordinate
int Mapdata::getLandscape(int x,int y)
{
   return landscape[MCART(x,y)];
}


////////////////////////////////////////////////////////////////////////////////
//set landscape at coordinate
void Mapdata::setLandscape(int x,int y,int useTexture)
{
   landscape[MCART(x,y)]=useTexture;
   return;
}


////////////////////////////////////////////////////////////////////////////////
//add a shadow to texture at coordinate
void Mapdata::shadeLandscape(int x,int y)
{
   landscape[MCART(x,y)]++;
   return;
}


////////////////////////////////////////////////////////////////////////////////
//get flags at coordinate
int Mapdata::getFlag(int x,int y)
{
   return flags[MCART(x,y)];
}


////////////////////////////////////////////////////////////////////////////////
//set flag at coordinate
void Mapdata::setFlag(int x,int y,int addFlag)
{
   flags[MCART(x,y)]|=addFlag;
   return;
}


////////////////////////////////////////////////////////////////////////////////
//clear all map data
void Mapdata::clearAll(void)
{
   memset(overlay,0,MAP_WIDTH*MAP_HEIGHT*sizeof(int));
   memset(landscape,0,MAP_WIDTH*MAP_HEIGHT*sizeof(int));
   memset(flags,0,MAP_WIDTH*MAP_HEIGHT*sizeof(int));   
   return;
}

