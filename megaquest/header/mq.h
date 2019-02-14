#ifndef MQ_H
#define MQ_H
//------------------------------------------------------------------------------
#include "header\logic.h"
#include "header\gfx.h"
#include "header\game.h"

////////////////////////////////////////////////////////////////////////////////
//central class, contains everything in the game
class Mq
{
public:
   Mq(void);
   ~Mq(void);
   Logic logic;
   GFX gfx;
   Game game;
   Input input;

   private:
};

//------------------------------------------------------------------------------
#endif