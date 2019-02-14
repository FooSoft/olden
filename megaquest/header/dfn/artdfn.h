#ifndef ARTDFN_H
#define ARTDFN_H
//------------------------------------------------------------------------------
//sizes of tiles
#define TILE_DIM 16

//beginning offsets of wall and floor tiles in the library
#define BASE_FLOOR  0  //start of dungeon floor tiles
#define BASE_WALL   12 //start of dungeon wall tiles
#define BASE_PLAYER 36 //start for player sprites

//special tiles
#define FOG_OF_WAR  35 //fog of war tile
#define TRANS_TILE  34 //transparent tile

//programmer-friendly texture names
#define FLOOR_GENERIC BASE_FLOOR+0
#define WALL_GENERIC  BASE_WALL+0

//various delays used for graphical stuff
#define SLIDE_DELAY  5
#define SCROLL_DELAY 5
#define FADE_DELAY   5
//------------------------------------------------------------------------------
#endif
