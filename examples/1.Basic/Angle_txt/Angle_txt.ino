#include <GDSTx.h>
                     //       0       1
char MCUTXT[60][22]={"F411CE", "Teesy 4.1"};
int MCUbase=1;

Bitmap Background,SaidHello;

void setup()
{
  GD.begin();
  Background.fromfile("dog.jpg");
  SaidHello.fromtext(20, MCUTXT[MCUbase]);
  MP();
}
void loop(){}

void MP()
{
  int ANG=0;

  int minPX = 15; int maxPX = GD.w-minPX;
  int movX = minPX;
  int deltaenX = 1;

  int minPY = 15; int maxPY = GD.h-minPY;
  int movY = minPY;
  int deltaenY = 1;  

while(1)
{
  ANG = ANG + 1;
  if (ANG>=360){ANG=0;}

  movX = movX + deltaenX;
  if(movX >= maxPX){deltaenX = -1;}
  if(movX <= minPX){deltaenX = 1;}

  movY = movY + deltaenY;
  if(movY >= maxPY){deltaenY = -1;}
  if(movY <= minPY){deltaenY = 1;}  
  
  GD.ClearColorRGB(0x000055);
  GD.Clear();
  GD.SaveContext();
  GD.ColorA(144);
  Background.draw(GD.w / 2, GD.h / 2);
   GD.ColorA(255);
   GD.ColorRGB(0xffffff); SaidHello.draw(10, 180, DEGREES(270));
   GD.ColorRGB(0xffffff); SaidHello.draw(movX, movY, DEGREES(ANG*(-1)));
  GD.RestoreContext();
  GD.swap(); 
 }
}
