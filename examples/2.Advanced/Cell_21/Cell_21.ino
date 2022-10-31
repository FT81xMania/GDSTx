#include <GDSTx.h>
#include "ico21.h"
int SEPx=48, SEPy=48;
int PosX[25], PosY[25];
int Figura[100];
int velX[25], velY[25];

void setup() {
  GD.begin();
  LOAD_ASSETS();
  GD.BitmapLayout(ARGB4, 2 * 45, 45);

  GD.BitmapHandle(15);
  GD.cmd_loadimage(ASSETS_END, 0);
  GD.load("Ab5.jpg");

  GD.ClearColorRGB(0x000000);
  GD.Clear();
  GD.get_inputs();
  GD.SaveContext();  
   for (int j=0; j<22; j++)
     { 
       int PXX = GD.random(0,GD.w-45);  int PYY = GD.random(0,GD.h-45);
       PosX[j]=PXX; PosY[j]=PYY;
       int Imagen = GD.random(0,20);
       velX[j] = GD.random(1,4);
       velY[j] = velX[j];
       
       Figura[j]=Imagen;
     }
   GD.RestoreContext();  
  GD.swap();
}



void loop()
{
  GD.ClearColorRGB(0x000000);
  GD.Clear();
  GD.get_inputs();

   GD.SaveContext();
     GD.Begin(BITMAPS);
     GD.ColorA(85);
     GD.Vertex2ii(0, 14, 15);
   GD.RestoreContext(); 

  GD.SaveContext();  
  GD.Begin(BITMAPS);
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
  
   PosX[0] = PosX[0]+velX[0];
   if(PosX[0]>=GD.w-45){velX[0]=-1*velX[0];}
   if(PosX[0]<=0){velX[0]=-1*velX[0];}
   
   PosY[0] = PosY[0]+velY[0];
   if(PosY[0]>=GD.h-45){velY[0]=-1*velY[0];}  
   if(PosY[0]<=0){velY[0]=-1*velY[0];}

   PosX[15] = PosX[15]+velX[15];
   if(PosX[15]>=GD.w-45){velX[15]=-1*velX[15];}
   if(PosX[15]<=0){velX[15]=-1*velX[15];}
   
   PosY[15] = PosY[15]+velY[15];
   if(PosY[15]>=GD.h-45){velY[15]=-1*velY[15];}  
   if(PosY[15]<=0){velY[15]=-1*velY[15];}   

  GD.ColorA(145);
  
  GD.SaveContext();
     GD.Begin(BITMAPS);
     GD.VertexTranslateX(16*(PosX[0]));  GD.VertexTranslateY(16*(PosY[0]));
     GD.Vertex2ii(0, 0, 0, 0);
  GD.RestoreContext();
  
  GD.SaveContext();
     GD.Begin(BITMAPS);
     GD.VertexTranslateX(16*(PosX[15]));  GD.VertexTranslateY(16*(PosY[15]));
     GD.Vertex2ii(0, 0, 0, 15);
  GD.RestoreContext();

   PosX[1] = PosX[1]+velX[1];
   if(PosX[1]>=GD.w-45){velX[1]=-1*velX[1];}
   if(PosX[1]<=0){velX[1]=-1*velX[1];}
   
   PosY[1] = PosY[1]+velY[1];
   if(PosY[1]>=GD.h-45){velY[1]=-1*velY[1];}  
   if(PosY[1]<=0){velY[1]=-1*velY[1];}

  GD.SaveContext();
     GD.Begin(BITMAPS);
     GD.VertexTranslateX(16*(PosX[1]));  GD.VertexTranslateY(16*(PosY[1]));
     GD.Vertex2ii(0, 0, 0, 1);
  GD.RestoreContext(); 

   PosX[2] = PosX[2]+velX[2];
   if(PosX[2]>=GD.w-45){velX[2]=-1*velX[2];}
   if(PosX[2]<=0){velX[2]=-1*velX[2];}
   
   PosY[2] = PosY[2]+velY[2];
   if(PosY[2]>=GD.h-45){velY[2]=-1*velY[2];}  
   if(PosY[2]<=0){velY[2]=-1*velY[2];}

  GD.SaveContext();
     GD.Begin(BITMAPS);
     GD.VertexTranslateX(16*(PosX[2]));  GD.VertexTranslateY(16*(PosY[2]));
     GD.Vertex2ii(0, 0, 0, 2);
  GD.RestoreContext();

   PosX[3] = PosX[3]+velX[3];
   if(PosX[3]>=GD.w-45){velX[3]=-1*velX[3];}
   if(PosX[3]<=0){velX[3]=-1*velX[3];}
   
   PosY[3] = PosY[3]+velY[3];
   if(PosY[3]>=GD.h-45){velY[3]=-1*velY[3];}  
   if(PosY[3]<=0){velY[3]=-1*velY[3];}

  GD.SaveContext();
     GD.Begin(BITMAPS);
     GD.VertexTranslateX(16*(PosX[3]));  GD.VertexTranslateY(16*(PosY[3]));
     GD.Vertex2ii(0, 0, 0, 3);
  GD.RestoreContext();  

   PosX[4] = PosX[4]+velX[4];
   if(PosX[4]>=GD.w-45){velX[4]=-1*velX[4];}
   if(PosX[4]<=0){velX[4]=-1*velX[4];}
   
   PosY[4] = PosY[4]+velY[4];
   if(PosY[4]>=GD.h-45){velY[4]=-1*velY[4];}  
   if(PosY[4]<=0){velY[4]=-1*velY[4];}

  GD.SaveContext();
     GD.Begin(BITMAPS);
     GD.VertexTranslateX(16*(PosX[4]));  GD.VertexTranslateY(16*(PosY[4]));
     GD.Vertex2ii(0, 0, 0, 4);
  GD.RestoreContext();

   PosX[5] = PosX[5]+velX[5];
   if(PosX[5]>=GD.w-45){velX[5]=-1*velX[5];}
   if(PosX[5]<=0){velX[5]=-1*velX[5];}
   
   PosY[5] = PosY[5]+velY[5];
   if(PosY[5]>=GD.h-45){velY[5]=-1*velY[5];}  
   if(PosY[5]<=0){velY[5]=-1*velY[5];}

  GD.SaveContext();
     GD.Begin(BITMAPS);
     GD.VertexTranslateX(16*(PosX[5]));  GD.VertexTranslateY(16*(PosY[5]));
     GD.Vertex2ii(0, 0, 0, 5);
  GD.RestoreContext();

   PosX[6] = PosX[6]+velX[6];
   if(PosX[6]>=GD.w-45){velX[6]=-1*velX[6];}
   if(PosX[6]<=0){velX[6]=-1*velX[6];}
   
   PosY[6] = PosY[6]+velY[6];
   if(PosY[6]>=GD.h-45){velY[6]=-1*velY[6];}  
   if(PosY[6]<=0){velY[6]=-1*velY[6];}

  GD.SaveContext();
     GD.Begin(BITMAPS);
     GD.VertexTranslateX(16*(PosX[6]));  GD.VertexTranslateY(16*(PosY[6]));
     GD.Vertex2ii(0, 0, 0, 6);
  GD.RestoreContext();

   PosX[7] = PosX[7]+velX[7];
   if(PosX[7]>=GD.w-45){velX[7]=-1*velX[7];}
   if(PosX[7]<=0){velX[7]=-1*velX[7];}
   
   PosY[7] = PosY[7]+velY[7];
   if(PosY[7]>=GD.h-45){velY[7]=-1*velY[7];}  
   if(PosY[7]<=0){velY[7]=-1*velY[7];}

  GD.SaveContext();
     GD.Begin(BITMAPS);
     GD.VertexTranslateX(16*(PosX[7]));  GD.VertexTranslateY(16*(PosY[7]));
     GD.Vertex2ii(0, 0, 0, 7);
  GD.RestoreContext();
    
   PosX[8] = PosX[8]+velX[8];
   if(PosX[8]>=GD.w-45){velX[8]=-1*velX[8];}
   if(PosX[8]<=0){velX[8]=-1*velX[8];}
   
   PosY[8] = PosY[8]+velY[8];
   if(PosY[8]>=GD.h-45){velY[8]=-1*velY[8];}  
   if(PosY[8]<=0){velY[8]=-1*velY[8];}

  GD.SaveContext();
     GD.Begin(BITMAPS);
     GD.VertexTranslateX(16*(PosX[8]));  GD.VertexTranslateY(16*(PosY[8]));
     GD.Vertex2ii(0, 0, 0, 8);
  GD.RestoreContext();

   PosX[9] = PosX[9]+velX[9];
   if(PosX[9]>=GD.w-45){velX[9]=-1*velX[9];}
   if(PosX[9]<=0){velX[9]=-1*velX[9];}
   
   PosY[9] = PosY[9]+velY[9];
   if(PosY[9]>=GD.h-45){velY[9]=-1*velY[9];}  
   if(PosY[9]<=0){velY[9]=-1*velY[9];}

  GD.SaveContext();
     GD.Begin(BITMAPS);
     GD.VertexTranslateX(16*(PosX[9]));  GD.VertexTranslateY(16*(PosY[9]));
     GD.Vertex2ii(0, 0, 0, 9);
  GD.RestoreContext();

   PosX[10] = PosX[10]+velX[10];
   if(PosX[10]>=GD.w-45){velX[10]=-1*velX[10];}
   if(PosX[10]<=0){velX[10]=-1*velX[10];}
   
   PosY[10] = PosY[10]+velY[10];
   if(PosY[10]>=GD.h-45){velY[10]=-1*velY[10];}  
   if(PosY[10]<=0){velY[10]=-1*velY[10];}

  GD.SaveContext();
     GD.Begin(BITMAPS);
     GD.VertexTranslateX(16*(PosX[10]));  GD.VertexTranslateY(16*(PosY[10]));
     GD.Vertex2ii(0, 0, 0, 10);
  GD.RestoreContext();

   PosX[11] = PosX[11]+velX[11];
   if(PosX[11]>=GD.w-45){velX[11]=-1*velX[11];}
   if(PosX[11]<=0){velX[11]=-1*velX[11];}
   
   PosY[11] = PosY[11]+velY[11];
   if(PosY[11]>=GD.h-45){velY[11]=-1*velY[11];}  
   if(PosY[11]<=0){velY[11]=-1*velY[11];}

  GD.SaveContext();
     GD.Begin(BITMAPS);
     GD.VertexTranslateX(16*(PosX[11]));  GD.VertexTranslateY(16*(PosY[11]));
     GD.Vertex2ii(0, 0, 0, 11);
  GD.RestoreContext();

   PosX[12] = PosX[12]+velX[12];
   if(PosX[12]>=GD.w-45){velX[12]=-1*velX[12];}
   if(PosX[12]<=0){velX[12]=-1*velX[12];}
   
   PosY[12] = PosY[12]+velY[12];
   if(PosY[12]>=GD.h-45){velY[12]=-1*velY[12];}  
   if(PosY[12]<=0){velY[12]=-1*velY[12];}

  GD.SaveContext();
     GD.Begin(BITMAPS);
     GD.VertexTranslateX(16*(PosX[12]));  GD.VertexTranslateY(16*(PosY[12]));
     GD.Vertex2ii(0, 0, 0, 12);
  GD.RestoreContext();  

   PosX[13] = PosX[13]+velX[13];
   if(PosX[13]>=GD.w-45){velX[13]=-1*velX[13];}
   if(PosX[13]<=0){velX[13]=-1*velX[13];}
   
   PosY[13] = PosY[13]+velY[13];
   if(PosY[13]>=GD.h-45){velY[13]=-1*velY[13];}  
   if(PosY[13]<=0){velY[13]=-1*velY[13];}

  GD.SaveContext();
     GD.Begin(BITMAPS);
     GD.VertexTranslateX(16*(PosX[13]));  GD.VertexTranslateY(16*(PosY[13]));
     GD.Vertex2ii(0, 0, 0, 13);
  GD.RestoreContext();

   PosX[14] = PosX[14]+velX[14];
   if(PosX[14]>=GD.w-45){velX[14]=-1*velX[14];}
   if(PosX[14]<=0){velX[14]=-1*velX[14];}
   
   PosY[14] = PosY[14]+velY[14];
   if(PosY[14]>=GD.h-45){velY[14]=-1*velY[14];}  
   if(PosY[14]<=0){velY[14]=-1*velY[14];}

  GD.SaveContext();
     GD.Begin(BITMAPS);
     GD.VertexTranslateX(16*(PosX[14]));  GD.VertexTranslateY(16*(PosY[14]));
     GD.Vertex2ii(0, 0, 0, 14);
  GD.RestoreContext();

   PosX[16] = PosX[16]+velX[16];
   if(PosX[16]>=GD.w-45){velX[16]=-1*velX[16];}
   if(PosX[16]<=0){velX[16]=-1*velX[16];}
   
   PosY[16] = PosY[16]+velY[16];
   if(PosY[16]>=GD.h-45){velY[16]=-1*velY[16];}  
   if(PosY[16]<=0){velY[16]=-1*velY[16];}

  GD.SaveContext();
     GD.Begin(BITMAPS);
     GD.VertexTranslateX(16*(PosX[16]));  GD.VertexTranslateY(16*(PosY[16]));
     GD.Vertex2ii(0, 0, 0, 16);
  GD.RestoreContext();

   PosX[17] = PosX[17]+velX[17];
   if(PosX[17]>=GD.w-45){velX[17]=-1*velX[17];}
   if(PosX[17]<=0){velX[17]=-1*velX[17];}
   
   PosY[17] = PosY[17]+velY[17];
   if(PosY[17]>=GD.h-45){velY[17]=-1*velY[17];}  
   if(PosY[17]<=0){velY[17]=-1*velY[17];}

  GD.SaveContext();
     GD.Begin(BITMAPS);
     GD.VertexTranslateX(16*(PosX[17]));  GD.VertexTranslateY(16*(PosY[17]));
     GD.Vertex2ii(0, 0, 0, 17);
  GD.RestoreContext();

   PosX[18] = PosX[18]+velX[18];
   if(PosX[18]>=GD.w-45){velX[18]=-1*velX[18];}
   if(PosX[18]<=0){velX[18]=-1*velX[18];}
   
   PosY[18] = PosY[18]+velY[18];
   if(PosY[18]>=GD.h-45){velY[18]=-1*velY[18];}  
   if(PosY[18]<=0){velY[18]=-1*velY[18];}

  GD.SaveContext();
     GD.Begin(BITMAPS);
     GD.VertexTranslateX(16*(PosX[18]));  GD.VertexTranslateY(16*(PosY[18]));
     GD.Vertex2ii(0, 0, 0, 18);
  GD.RestoreContext();

   PosX[19] = PosX[19]+velX[19];
   if(PosX[19]>=GD.w-45){velX[19]=-1*velX[19];}
   if(PosX[19]<=0){velX[19]=-1*velX[19];}
   
   PosY[19] = PosY[19]+velY[19];
   if(PosY[19]>=GD.h-45){velY[19]=-1*velY[19];}  
   if(PosY[19]<=0){velY[19]=-1*velY[19];}

  GD.SaveContext();
     GD.Begin(BITMAPS);
     GD.VertexTranslateX(16*(PosX[19]));  GD.VertexTranslateY(16*(PosY[19]));
     GD.Vertex2ii(0, 0, 0, 19);
  GD.RestoreContext();

   PosX[20] = PosX[20]+velX[20];
   if(PosX[20]>=GD.w-45){velX[20]=-1*velX[20];}
   if(PosX[20]<=0){velX[20]=-1*velX[20];}
   
   PosY[20] = PosY[20]+velY[20];
   if(PosY[20]>=GD.h-45){velY[20]=-1*velY[20];}  
   if(PosY[20]<=0){velY[20]=-1*velY[20];}

  GD.SaveContext();
     GD.Begin(BITMAPS);
     GD.VertexTranslateX(16*(PosX[20]));  GD.VertexTranslateY(16*(PosY[20]));
     GD.Vertex2ii(0, 0, 0, 20);
  GD.RestoreContext();
  GD.swap();  
}
