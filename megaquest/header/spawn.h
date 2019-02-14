#ifndef MAPSPAWN_H
#define MAPSPAWN_H
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
//this class create maps
class Spawn
{
public:
   void spawnMap(Mapdata*);
   class Map *parent;
   class Mq *top;

private:
   void createLandscape(Mapdata*);
   void addRoom(Mapdata*);
   void addTunnel(Mapdata*);
   bool connectedFlags(int,int,int,int,Mapdata*,int,int);
   int countTouchingFlags(int,int,Mapdata*,int,bool);
   void generateMapFlags(Mapdata*);
   void generateMapTextures(Mapdata*);
   void generateLandscapeEffects(Mapdata*);
   void fillAreaFlags(int,int,int,int,Mapdata*,int);
   
};


//------------------------------------------------------------------------------
#endif