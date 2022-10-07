#include <GDSTx.h>

Bitmap Background,SaidHello;

void setup()
{
  GD.begin();
  Background.fromfile("dog.jpg");
  //SaidHello.fromtext(28, "Teensy 4@FT8XX");
  SaidHello.fromtext(28, "STM32@FT8XX");
  MP();
}
void loop(){}

void MP()
{
  int ANG=0;
  int minX = 0, minY = 0;
  int maxX = GD.w - minX, maxY = GD.h - minY;
  int startX = maxX / 2, startY = maxY / 2;
  int deltaX = 4, deltaY = 4;

while(1)
{
  ANG = ANG + 1;
  if (ANG>=360){ANG=0;}

   startX = startX + deltaX;   startY = startY + deltaY;
   if (startX >= maxX)
       deltaX = -deltaX;
   if (startX <= minX)
       deltaX = abs(deltaX);
   if (startY >= maxY)
       deltaY = -deltaY;
   if (startY <= minY)
       deltaY = abs(deltaY);
  
  GD.ClearColorRGB(0x000055);
  GD.Clear();

  GD.ColorA(144);
  Background.draw(GD.w / 2, GD.h / 2);
  GD.ColorA(255);
  
  GD.ColorRGB(0xffffff); SaidHello.draw(startX, startY, DEGREES(ANG));

  GD.swap(); 
 }
}
