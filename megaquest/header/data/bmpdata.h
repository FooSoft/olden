#ifndef FILEHEADER_H
#define FILEHEADER_H
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
//header structure for bitmaps
typedef struct Bmp
{
   unsigned height;
   unsigned width;
   unsigned colors;
   unsigned size;
   char palette[256*3];
   char *pixels;
}
Bmp;

//------------------------------------------------------------------------------
#endif
