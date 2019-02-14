#ifndef MACRODFN_H
#define MACRODFN_H
//------------------------------------------------------------------------------
//cartesian conversion macros
#define CART(X,Y,WIDTH) (X)+((Y)*WIDTH)
#define MCART(X,Y) CART(X,Y,MAP_WIDTH)
#define SCART(X,Y) CART(X,Y,SCREEN_WIDTH)
//------------------------------------------------------------------------------
#endif