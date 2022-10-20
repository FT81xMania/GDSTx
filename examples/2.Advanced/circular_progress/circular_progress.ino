//#include <GD23ZUTX.h>
//#include <GDT4Xv134.h>
#include <GDSTx.h>


// Tabla de colores
#define  BLACK          0x000000
#define RED             0xff0000
#define GREEN           0x07E000
#define BLUE            0x0000ff
#define CYAN            0x00ffFF
#define MAGENTA         0xFF00FF
#define YELLOW          0xFFFF00 
#define ORANGE          0xFF4500
#define GREENYELLOW     0x9acd32 
#define DARKGRAY        0x242424
#define WHITE           0xFFFFFF

void setup(){
  GD.begin();
  MP();
}
void loop(){}

float velP=0.1;

void MP()
{
  while(1)
  {
   GD.ClearColorRGB(0x000055);
   GD.Clear();
   GD.get_inputs();

   float percent=percent+velP;
   if (percent>=100){velP=-0.1;}
   if (percent<=0){velP=0.1;}

   GD.SaveContext();
      GD.Begin(POINTS);

      GD.PointSize(16*75);
      GD.ColorRGB(0xff0000);   GD.Vertex2f((GD.w/2)*16, (GD.h/2)*16);
      
      GD.PointSize(16*65);
      GD.ColorRGB(0x000055);   GD.Vertex2f((GD.w/2)*16, (GD.h/2)*16);
   GD.RestoreContext();

   
   cgaugef(50, 100, 50, percent, DARKGRAY, GREEN, WHITE, BLACK, 26);
   cgaugef(150, 100, 50, percent, DARKGRAY, GREEN, BLACK, WHITE, 26);
   cPie(300, 100, 50, percent, RED,0x001585,YELLOW, 26);
   
   GD.swap();
  }
}


void cgauge(int x, int y, int r, float fill, uint32_t colorextern, uint32_t colorfill, uint32_t colorempty, uint32_t sizeTXT, uint32_t colorTXT){
  char TXPorc[50];

 
  GD.SaveContext();
  GD.Begin(POINTS);
  
  GD.ColorRGB(colorextern);
  GD.PointSize(16*r);
  GD.Vertex2f(x*16,y*16);

  GD.ColorRGB(colorfill);
  GD.PointSize(16*(r-3));
  GD.Vertex2f(x*16,y*16);

  GD.ScissorXY(x - r, y - r);
  GD.ScissorSize(2 * r, (2 * r * (100-fill)) / 100);

  GD.ColorRGB(colorempty);
  GD.Vertex2f(16*(x), 16*(y));
  GD.RestoreContext();

  GD.SaveContext();
   GD.ColorRGB(colorTXT);
   //GD.printNfloat(x, y,fill,1,sizeTXT); //STM32
   GD.printNfloat(x, y, fill,1,sizeTXT,0); //Teensy 4.X
   //sprintf(TXPorc,"%d%%", fill);  GD.cmd_text(x, y, sizeTXT, OPT_CENTER, TXPorc);
  GD.RestoreContext();  
}


void cgaugef(float x, float y, float r, float fill, uint32_t colorextern, uint32_t colorfill, uint32_t colorempty, uint32_t colortext, uint32_t sizeTXT){
  char TXPorc[50];
  
  GD.SaveContext();
  GD.Begin(POINTS);
  
  GD.ColorRGB(colorextern);
  GD.PointSize(16*r);
  GD.Vertex2f(x*16,y*16);

  GD.ColorRGB(colorfill);
  GD.PointSize(16*(r-3));
  GD.Vertex2f(x*16,y*16);

  GD.ScissorXY(x - r, y - r);
  GD.ScissorSize(2 * r, (2 * r * (100-fill)) / 100);

  GD.ColorRGB(colorempty);
  GD.Vertex2f(16*(x), 16*(y));
  GD.RestoreContext();

  GD.SaveContext();
   GD.ColorRGB(colortext);
   //GD.printNfloat(x, y-15,fill,1,sizeTXT);
   GD.printNfloat(x, y-15,fill,1,sizeTXT,0);
   GD.cmd_text(x, y+r*0.3, sizeTXT, OPT_CENTER, "%");
  GD.RestoreContext();
}

void cPie(float x, float y, float r, float fill, uint32_t colorextern, uint32_t colorfill, uint32_t colortext, uint32_t sizeTXT){
  char TXPorc[50];
  
  GD.SaveContext();
  GD.Begin(POINTS);
   GD.ColorRGB(colorextern);
   GD.PointSize(16*r);
   GD.Vertex2f(x*16,y*16);
   GD.ColorRGB(colorfill);
   GD.PointSize(16*(r-3));
   GD.Vertex2f(x*16,y*16);
  GD.RestoreContext();

  GD.SaveContext();
   GD.Begin(LINES);
   GD.LineWidth(16 * 1);
   GD.ColorRGB(colorextern);
   float angle = 360*fill/100;
  
   GD.Vertex2f(x*16, y*16); GD.Vertex2f((x+r)*16, (y)*16);
   GD.Vertex2f(x*16, y*16); GD.Vertex2f((x+r*cos(angle*3.1415/180))*16, (y-r*sin(angle*3.1415/180))*16);
  GD.RestoreContext();

  GD.SaveContext();
   GD.ColorRGB(colortext);
   //GD.printNfloat(x+(r*cos(angle*3.1415/180))+r*(0), y-(r*0)-r*sin(angle*3.1415/180),fill,1,sizeTXT);
   GD.printNfloat(x+(r*cos(angle*3.1415/180))+r*(0), y-(r*0)-r*sin(angle*3.1415/180),fill,1,sizeTXT,0);
   //GD.printNfloat(x+r*.5, y+15,100-fill,1,sizeTXT);
   GD.printNfloat(x+r*.5, y+15,100-fill,1,sizeTXT,0);
   GD.cmd_text(x, y, sizeTXT, OPT_CENTER, "%");
  GD.RestoreContext();
}
