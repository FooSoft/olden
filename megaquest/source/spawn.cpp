#include <stdlib.h>
#include "header\spawn.h"

////////////////////////////////////////////////////////////////////////////////
//spawn a new map
void Spawn::spawnMap(Mapdata *mapdata)
{
   createLandscape(mapdata);
   generateMapTextures(mapdata);
   generateMapFlags(mapdata);
   generateLandscapeEffects(mapdata);
   return;
}


////////////////////////////////////////////////////////////////////////////////
//create map landscape, physical features
void Spawn::createLandscape(Mapdata *mapdata)
{
   int totalRooms,totalTunnels;
   int room=0,tunnel=0;

   //clear initial maze memory
   mapdata->clearAll();

   //enter a seed value for maze
   mapdata->setFlag(MAP_WIDTH/2,MAP_HEIGHT/2,FLAG_ROOM);

   //figure out the number of rooms and tunnels in map
   totalRooms=rand()%(MAX_ROOMS-MIN_ROOMS)+MIN_ROOMS;
   totalTunnels=rand()%(MAX_TUNNELS-MIN_TUNNELS)+MIN_TUNNELS;

   //keep adding rooms and tunnels until we met our quota
   while ((room<=totalRooms)&&(tunnel<totalTunnels))
   {
      //add tunnels
      if (tunnel!=totalTunnels)
      {
         addTunnel(mapdata);
         tunnel++;
      }

      //add rooms
      if (room++!=totalRooms)
      {
         addRoom(mapdata);
         room++;
      }
   }

   return;
}


////////////////////////////////////////////////////////////////////////////////
//add a room that is connected to a tunnel
void Spawn::addRoom(Mapdata *mapdata)
{
   int x1,y1,x2,y2;
   int dx,dy;

   //make sure that every room is connected to a tunnel
   do
      do
      {
         //find appropriate room dimentions and coordinates
         x1=rand()%(MAP_WIDTH-1)+1;
         y1=rand()%(MAP_HEIGHT-1)+1;
         dx=rand()%(MAX_ROOM_DIM-MIN_ROOM_DIM)+MIN_ROOM_DIM;
         dy=rand()%(MAX_ROOM_DIM-MIN_ROOM_DIM)+MIN_ROOM_DIM;
         x2=x1+dx;
         y2=y1+dy;
      }
      while ((x2>=MAP_WIDTH-1)||(y2>=MAP_HEIGHT-1));
   while (!connectedFlags(x1,y1,x2,y2,mapdata,FLAG_TUNNEL,FLAG_ROOM));

   //room is valid, so create it
   fillAreaFlags(x1,y1,x2,y2,mapdata,FLAG_ROOM);
   return;
}


////////////////////////////////////////////////////////////////////////////////
//add a tunnel that is connected to a room
void Spawn::addTunnel(Mapdata *mapdata)
{
   int xoffset[]={0,-1,0,1};
   int yoffset[]={-1,0,1,0};
   int x1,y1,x2,y2;   
   char direction;
   int length;   

   //make sure that tunnel is connected to room
   do
      do
      {
         //find appropriate tunnel dimentions and coordinates      
         x1=rand()%(MAP_WIDTH-1)+1;
         y1=rand()%(MAP_HEIGHT-1)+1;
         length=rand()%(MAX_TUNNEL_LENGTH-MIN_TUNNEL_LENGTH)+MIN_TUNNEL_LENGTH;
         direction=rand()%4;
         x2=x1+xoffset[direction]*length;
         y2=y1+yoffset[direction]*length;
      }
      while ((x2>=MAP_WIDTH-1)||(y2>=MAP_HEIGHT-1));
   while (!connectedFlags(x1,y1,x2,y2,mapdata,FLAG_ROOM,FLAG_TUNNEL));

   //tunnel is valid, so create it
   fillAreaFlags(x1,y1,x2,y2,mapdata,FLAG_TUNNEL);
   return;
}


////////////////////////////////////////////////////////////////////////////////
//see if one style "connects" to another
bool Spawn::connectedFlags(int x1,int y1,int x2,int y2,Mapdata *mapdata,int outerNeed,int innerBan)
{
   int inner,outer;
   int x,y;

   for (y=y1,inner=outer=0; y<=y2; y++)
      for (x=x1; x<=x2; x++)
      {
         //if tile is on one of the borders
         if ((y==y1)||(y==y2)||(x==x1)||(x==x2))
         {
            outer+=countTouchingFlags(x,y,mapdata,outerNeed,true);
            inner+=countTouchingFlags(x,y,mapdata,innerBan,false);
         }

         //tile is inside the area
         if (mapdata->getFlag(x,y)&innerBan)
            inner++;
      }

   return bool((inner==0)&&(outer>0)&&(outer<=CLAUSTROPHOBIA));
}


////////////////////////////////////////////////////////////////////////////////
//find out how many times a style appears in a given radius
int Spawn::countTouchingFlags(int x,int y,Mapdata *mapdata,int style,bool strict)
{
   int xoffset[]={0,-1,0,1,-1,-1,1,1};
   int yoffset[]={-1,0,1,0,-1,1,-1,1};
   int xnew,ynew,count,offset;

   for (offset=0,count=0; offset<(strict?4:8); offset++)
   {
      //get new coordinate pairs
      xnew=x+xoffset[offset];
      ynew=y+yoffset[offset];

      //see if new coordinate pair is the queried style
      if (parent->isValidRange(xnew,ynew))
         if (mapdata->getFlag(xnew,ynew)&style)
            count++;
   }

   return count;
}


////////////////////////////////////////////////////////////////////////////////
//add styles to the map, such as clipping and tile properties
void Spawn::generateMapFlags(Mapdata *mapdata)
{
   int x,y;

   for (y=0; y<MAP_HEIGHT; y++)
      for (x=0; x<MAP_WIDTH; x++)
      {
         //if it is a wall, add wall flag
         if (mapdata->getLandscape(x,y)>=BASE_WALL)
            mapdata->setFlag(x,y,FLAG_CLIP);
      }

   return;
}


////////////////////////////////////////////////////////////////////////////////
//add textures to map
void Spawn::generateMapTextures(Mapdata *mapdata)
{
   int x,y;
   unsigned flags;

   for (y=0; y<MAP_HEIGHT; y++)
      for (x=0; x<MAP_WIDTH; x++)
      {
         flags=mapdata->getFlag(x,y);
         if (flags==0)
            mapdata->setLandscape(x,y,WALL_GENERIC);
         else
            mapdata->setLandscape(x,y,FLOOR_GENERIC);
      }
}


////////////////////////////////////////////////////////////////////////////////
//create shadows on landscape
void Spawn::generateLandscapeEffects(Mapdata *mapdata)
{
   int x,y;
   int currentTile,shadowTile;

   for (y=0; y<MAP_HEIGHT; y++)
      for (x=0; x<MAP_WIDTH; x++)
      {
         currentTile=mapdata->getLandscape(x,y);

         //target tile is a floor
         if (currentTile<BASE_WALL)
            if (y-1>=0)
            {
               shadowTile=mapdata->getLandscape(x,y-1);
               if ((currentTile!=shadowTile)&&(currentTile%2==0)&&(shadowTile>=BASE_WALL))
                  mapdata->shadeLandscape(x,y);
            }

         //target tile is a wall
         if (currentTile>=BASE_WALL)
         {
            if (y+1<MAP_HEIGHT)
            {
               shadowTile=mapdata->getLandscape(x,y+1);
               if ((currentTile!=shadowTile)&&(currentTile%2==0)&&(shadowTile<BASE_WALL))
                  mapdata->shadeLandscape(x,y);
            }
            if (countTouchingFlags(x,y,mapdata,FLAG_CLIP,false)==8)
               mapdata->setLandscape(x,y,FOG_OF_WAR);
         }

      }

   return;
}


////////////////////////////////////////////////////////////////////////////////
//carve a rectangular area out of the landscape
void Spawn::fillAreaFlags(int x1,int y1,int x2,int y2,Mapdata *mapdata,int type)
{
   int x,y;

   //fill in from (x1,y1) to (x2,y2) using "tile" and style of "type"
   for (y=y1; y<=y2; y++)
      for (x=x1; x<=x2; x++)
         mapdata->setFlag(x,y,type);

   return;
}
