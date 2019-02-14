#ifndef CRITTER_H
#define CRITTER_H
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
//generic class for critters
class Critter
{
public:
   void drawOnMap(void);
   bool allowMove(char);
   bool isVisible(void);
   void coordMove(char);
   bool moveInDirection(char);
   void slideView(char);
   void centerView(void);
   void placeRandomly(void);

   int getXCoord(void);
   int getYCoord(void);
   void setCoords(int,int);
   int getTexture(void);
   void setTexture(int);
   void setHuman(bool);
   bool getHuman(void);

   class Map *parent;
   class Mq *top;

private:
   int xloc;
   int yloc;
   int texture;
   bool isPlayer;
};




//------------------------------------------------------------------------------
#endif