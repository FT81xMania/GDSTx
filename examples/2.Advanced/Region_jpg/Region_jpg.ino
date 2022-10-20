//#include <GD23ZUTX.h>
#include <GDSTx.h>

void setup()
{
  GD.begin();

  GD.cmd_loadimage(0, 0);
  GD.load("Gasol_01b.jpg");

  MP();
}
void loop(){}

int XIMG=-100, YIMG=-100, Speed=2;
char TX[50];
 
void MP()
{
  while(1)
 {
   GD.Clear();
   GD.get_inputs();

   GD.SaveContext();
   GD.Begin(BITMAPS);
   GD.VertexTranslateX(XIMG*16);
   GD.VertexTranslateY(YIMG*16);
       GD.Vertex2f(0*16, 0*16);
   GD.RestoreContext();

  

   GD.SaveContext();
   GD.ColorA(180);
     GD.Tag(205); GD.cmd_fgcolor(0x005000);   GD.cmd_button(50, 200, 100, 30, 26, OPT_FLAT, "L");  GD.Tag(255);
    GD.Tag(206); GD.cmd_fgcolor(0x005000);  GD.cmd_button(170, 200, 100, 30, 26, OPT_FLAT, "R");  GD.Tag(255);
    
    GD.Tag(207); GD.cmd_fgcolor(0x005000);  GD.cmd_button(10, 150, 30, 80, 26, OPT_FLAT, "D");  GD.Tag(255);
    GD.Tag(208); GD.cmd_fgcolor(0x005000);   GD.cmd_button(10, 50, 30, 80, 26, OPT_FLAT, "U");  GD.Tag(255);    
   GD.RestoreContext();

   if (GD.inputs.tag==205)
   {
     XIMG=XIMG-Speed;
     if(XIMG<=-480){XIMG=-480;} //NHD35
     //if(XIMG<=-800){XIMG=-800;} //NHD5
   }

   if (GD.inputs.tag==206)
   {
     XIMG=XIMG+Speed;
     if(XIMG>=0){XIMG=0;}
   }   

   if (GD.inputs.tag==208)
   {
     YIMG=YIMG-Speed;
     if(YIMG<=-159){YIMG=-159;}
   }

   if (GD.inputs.tag==207)
   {
     YIMG=YIMG+Speed;
     if(YIMG>=0){YIMG=0;}
   }   

GD.SaveContext();
GD.Begin(RECTS);
GD.ColorRGB(0, 0, 0); 
GD.Vertex2f(280*16, 0*16); GD.Vertex2f(800*16, 480*16);
GD.Vertex2f(0*16, 240*16); GD.Vertex2f(800*16, 480*16);
//GD.ColorRGB(0x4cc417); // apple green
//GD.Vertex2ii(10, 140); GD.Vertex2ii(470, 260);
GD.RestoreContext();

sprintf(TX,"x=%d, y=%d", XIMG,YIMG);  GD.cmd_text(180, 0, 26, 0, TX);
    
   GD.swap();
 }
}
