#include <stdlib.h>
#include <stdio.h>
#include <mem.h>
#include "header\bitmap.h"

////////////////////////////////////////////////////////////////////////////////
//draw currently loaded bitmap to buffer
void Bitmap::draw(unsigned xbase,unsigned ybase,Bmp bmp)
{
   unsigned x,y;

   for (y=0; y<bmp.height; y++)
      for (x=0; x<bmp.width; x++)
         parent->putPixel(x+xbase,y+ybase,bmp.pixels[CART(x,y,bmp.width)]);

   return;
}


////////////////////////////////////////////////////////////////////////////////
//load bitmap file
bool Bitmap::load(char filename[],Bmp *bmp)
{
   long index;
   int x;
   FILE *fp;

   //open bitmap file
   fp=fopen(filename,"rb");
   if (fp==NULL)
      return false;

   //invalid bitmap file
   if ((fgetc(fp)!='B')||(fgetc(fp)!='M'))
   {
      fclose(fp);
      return false;
   }

   //get bitmap information
   fseek(fp,16,SEEK_CUR);
   fread(&bmp->width,1,sizeof(int),fp);
   fseek(fp,2,SEEK_CUR);
   fread(&bmp->height,1,sizeof(int),fp);
   fseek(fp,22,SEEK_CUR);
   fread(&bmp->colors,sizeof(int),1,fp);
   fseek(fp,6,SEEK_CUR);

   //assume we are working with an 8-bit file
   if (bmp->colors==0)
      bmp->colors=256;

   //allocate memory for bitmap data
   bmp->pixels=(char*)malloc((unsigned)(bmp->width*bmp->height));
   if (bmp->pixels==NULL)
   {
      fclose(fp);
      return false;
   }

   //get bitmap palette
   for(index=0; index<bmp->colors; index++)
   {
      bmp->palette[(int)(index*3+2)]=fgetc(fp)/4;
      bmp->palette[(int)(index*3+1)]=fgetc(fp)/4;
      bmp->palette[(int)(index*3+0)]=fgetc(fp)/4;
      fgetc(fp);
   }

   //get bitmap data
   for (index=(bmp->height-1)*bmp->width; index>=0; index-=bmp->width)
      for (x=0; x<bmp->width; x++)
         bmp->pixels[(unsigned)(index+x)]=fgetc(fp);

   //save bitmap size
   bmp->size=bmp->height*bmp->width;

   fclose(fp);
   return true;
}
