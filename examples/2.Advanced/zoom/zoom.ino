#include <GDSTx.h>

int X=0, Y=0;
double zoom = 0.05;

void setup()
{
  GD.begin();
  GD.cmd_loadimage(0, 0);
  GD.load("Ab3.jpg");  

  MP();
}
void loop(){}

void MP()
{
  while(1)
  {
   GD.get_inputs();   
   GD.Clear();
   
    GD.SaveContext();
     GD.ColorA(255); 
     fondoJPGZoom();
    GD.RestoreContext();

    GD.SaveContext();
    GD.ColorA(75); 
    GD.cmd_fgcolor(0x00ff00); 
    GD.ColorRGB(0x000000);     
    GD.Tag(5);  GD.cmd_button(10, 100, 60, 60, 26, 0,  "Zoom+");  GD.Tag(255);

    if (GD.inputs.tag==5){
          GD.Tag(5);  GD.cmd_button(10, 100, 60, 60, 26, OPT_FLAT,  "Zoom+");  GD.Tag(255);
          zoom=zoom+0.05; 
          if (zoom>=3.5){zoom=3.5;}
      }

    GD.Tag(6);  GD.cmd_button(10, 100+10+60, 60, 60, 26, 0,  "Zoom-");  GD.Tag(255);

    if (GD.inputs.tag==6){
          GD.Tag(6);  GD.cmd_button(10, 100+10+60, 60, 60, 26, OPT_FLAT,  "Zoom-");  GD.Tag(255);
          zoom=zoom-0.05; 
          if (zoom<=0.05){zoom=0.05;}
      }
    
    GD.cmd_fgcolor(0x0000ff); 
    GD.ColorRGB(0xffffff);     
    GD.Tag(1);  GD.cmd_button(10+60+10+60+10, 100, 60, 60, 26, 0,  "Up");   GD.Tag(255);

    if (GD.inputs.tag==1){
          GD.Tag(1);  GD.cmd_button(10+60+10+60+10, 100, 60, 60, 26, OPT_FLAT,  "Up");  GD.Tag(255);
          Y=Y-8; 
          if (Y<-480){Y=480;}
      }    
    
    GD.Tag(2);  GD.cmd_button(10+60+10+60+10, 100+10+60, 60, 60, 26, 0,  "Dw");    

    if (GD.inputs.tag==2){
          GD.Tag(2);  GD.cmd_button(10+60+10+60+10, 100+10+60, 60, 60, 26, OPT_FLAT,  "Dw");  GD.Tag(255);  
          Y=Y+8; 
          if (Y>=480){Y=-480;}
      }  

    GD.Tag(3);  GD.cmd_button(10+60+10, 100+5+30, 60, 60, 26, 0,  "Left");  GD.Tag(255);

    if (GD.inputs.tag==3){
          GD.Tag(3);  GD.cmd_button(10+60+10, 100+5+30, 60, 60, 26, OPT_FLAT,  "Left");  GD.Tag(255);
          X=X-8; 
          if (X<-800){X=800;}
      }    

    GD.Tag(4);  GD.cmd_button(10+60+10+60+10+60+10, 100+5+30, 60, 60, 26, 0,  "Right");  GD.Tag(255);

    if (GD.inputs.tag==4){
          GD.Tag(4);  GD.cmd_button(10+60+10+60+10+60+10, 100+5+30, 60, 60, 26, OPT_FLAT,  "Right");  GD.Tag(255);
          X=X+8; 
          if (X>=800){X=-800;}
      }    

    GD.Tag(7);  GD.cmd_button(10+60+10+60+10+60+10+10+60, 100, 20, 60+10+60, 26, 0,  "0");  GD.Tag(255);

    if (GD.inputs.tag==7){
          GD.Tag(7);  GD.cmd_button(10+60+10+60+10+60+10+10+60, 100, 20, 60+10+60, 26, OPT_FLAT,  "0");  GD.Tag(255);
          X=0;
          Y=0;
          zoom=0.05;
      }          
      
    GD.RestoreContext();
   
   GD.swap();
  }
}
