#include <Wire.h>
#include <AT24Cxx.h>
//#include <STM32_GD2F103.h>
#include <GDSTx.h>

#define i2c_address 0x50  //57 EEPROM on DS3231
AT24Cxx eep(i2c_address, 32);

char Valor[20];

int Mensaje=0, PY=0;

void setup() {
   Wire.begin();
   GD.begin();
   BorraCal();
}

void loop() {}

void BorraCal()
{
  while(1)
  {
    GD.ClearColorRGB(127, 124, 28);
    GD.Clear();
    for (int i = 0 ; i < 25 ; i++) {
      eep.update(i, 0x00);
      sprintf(Valor, "Adress %04d : %03d", i, eep.read(i)); 
      GD.ColorRGB(0xffffff);   GD.cmd_text(65, 5+(i*9), 20, OPT_CENTER, Valor);
      
      if(i>=24){Mensaje=1;}
    }
   
   if(Mensaje==1)
   {
    GD.ColorRGB(0x00ff00);  GD.cmd_text(40+GD.w/2, GD.h/2, 26, OPT_CENTER, "CALIBRACION REINICIADA");
    sprintf(Valor, "Adress %04d : %03d", 0, eep.read(0)); 
    GD.ColorRGB(0xff0000);   GD.cmd_text(40+GD.w/2, 25+GD.h/2, 20, OPT_CENTER, Valor);
   }
   GD.swap();
  }
}
