#ifndef MAPDATA_H
#define MAPDATA_H
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
//structure to hold map information
class Mapdata
{
public:
   Mapdata(void);
   ~Mapdata(void);
   int getLandscape(int,int);
   void setLandscape(int,int,int);
   void shadeLandscape(int,int);
   int getFlag(int,int);
   void setFlag(int,int,int);
   void clearAll(void);
   class Map *parent;
   class Mq *top;

private:
   int *overlay;
   int *landscape;
   int *flags;
};

//------------------------------------------------------------------------------
#endif
