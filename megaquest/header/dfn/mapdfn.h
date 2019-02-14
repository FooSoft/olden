#ifndef MAPDFN_H
#define MAPDFN_H
//------------------------------------------------------------------------------
//directions
#define NORTH 0
#define WEST  1
#define SOUTH 2
#define EAST  3

//flags
#define FLAG_NONE   0
#define FLAG_TUNNEL 1
#define FLAG_ROOM   2
#define FLAG_CLIP   4

//discovery
#define DISC_UNKNOWN 0
#define DISC_VISITED 1
#define DISC_VISIBLE 2

//show this many tiles on the screen at a time
#define MAP_SHOW_WIDTH  13
#define MAP_SHOW_HEIGHT 11

//claustrophobia factor determines openess of dungeon
#define CLAUSTROPHOBIA 10

//the actual dimentions of the map
#define MAP_WIDTH  150
#define MAP_HEIGHT 150

//path information
#define MIN_TUNNEL_LENGTH 5
#define MAX_TUNNEL_LENGTH 15
#define MIN_TUNNELS 15
#define MAX_TUNNELS 30

//room information
#define MIN_ROOM_DIM 4
#define MAX_ROOM_DIM 6
#define MIN_ROOMS 15
#define MAX_ROOMS 30
//------------------------------------------------------------------------------
#endif
