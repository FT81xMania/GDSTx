#include <GDSTx.h>

#include "ico21.h"

void setup() {
  GD.begin();
  LOAD_ASSETS();
  GD.BitmapLayout(ARGB4, 2 * 45, 45); // override the bitmap layout

  GD.BitmapHandle(15);
  GD.cmd_loadimage(ASSETS_END, 0);
  GD.load("Ab5.jpg");
}

int SEPx=48, SEPy=48;

void loop() {
 GD.ClearColorRGB(0x000070);
 GD.Clear();

  GD.SaveContext();  
  GD.Begin(BITMAPS);
   GD.Vertex2ii(0, 14, 15);
   //GD.Vertex2ii(0, 0, 15);
   GD.Vertex2ii(0, SEPy*0, 0, 0);
   GD.Vertex2ii(0, SEPy*1, 0, 1);
   GD.Vertex2ii(0, SEPy*2, 0, 2);
   GD.Vertex2ii(0, SEPy*3, 0, 3);
   GD.Vertex2ii(0, SEPy*4, 0, 4);
   
   GD.Vertex2ii(SEPx*1, SEPy*0, 0, 5);
   GD.Vertex2ii(SEPx*1, SEPy*1, 0, 6);
   GD.Vertex2ii(SEPx*1, SEPy*2, 0, 7);
   GD.Vertex2ii(SEPx*1, SEPy*3, 0, 8);
   GD.Vertex2ii(SEPx*1, SEPy*4, 0, 9);

   GD.Vertex2ii(SEPx*2, SEPy*0, 0, 10);
   GD.Vertex2ii(SEPx*2, SEPy*1, 0, 11);
   GD.Vertex2ii(SEPx*2, SEPy*2, 0, 12);
   GD.Vertex2ii(SEPx*2, SEPy*3, 0, 13);
   GD.Vertex2ii(SEPx*2, SEPy*4, 0, 14);   

   GD.Vertex2ii(SEPx*3, SEPy*0, 0, 15);
   GD.Vertex2ii(SEPx*3, SEPy*1, 0, 16);
   GD.Vertex2ii(SEPx*3, SEPy*2, 0, 17);
   GD.Vertex2ii(SEPx*3, SEPy*3, 0, 18);
   GD.Vertex2ii(SEPx*3, SEPy*4, 0, 19);

   GD.Vertex2ii(SEPx*4, SEPy*0, 0, 20);
  GD.RestoreContext();
 GD.swap();
}
