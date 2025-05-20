#include <Wire.h>
#include <GDSTx.h>

int MCUID;

void setup()
{
  Wire.begin();
  GD.begin();

  IDEMCU();

  Searching();
}
void loop() {}

char ID[50];
int Sep=1,Dispositivo;

void Searching()
{
  byte error, address;
  int nDevices;

  GD.ClearColorRGB(0x000040);
   GD.Clear();
    //STM32();
    GD.ColorRGB(0xffffff);  GD.cmd_text((GD.w/2)-20, 0, 29, OPT_CENTERX, "i2C Scanner");
    GD.ColorRGB(0x00ffff);  GD.cmd_text(GD.w/2, 25, 28, OPT_CENTERX, "Scanning...");

 
  nDevices = 0;
  for (address = 1; address < 127; address++ )
  {
    Wire.beginTransmission(address);
    Wire.write(0);
    error = Wire.endTransmission();

    if (error == 0)
    {
      GD.ColorRGB(0xffff00); GD.cmd_text(90, 50, 20, OPT_CENTERX, "i2C device found at address:");
      if (address << 16) sprintf(ID,"0x%02x", address); GD.ColorRGB(0x00ff00); GD.cmd_text(125, 50+(Sep*15), 20, 0, ID);
      Dispositivo=address;
      GD.ColorRGB(0x00ffff);  GD.cmd_number(125+65, 50+(Sep*15), 20, OPT_RIGHTX | OPT_SIGNED, Dispositivo);
      Tipo();
      Sep=Sep+1;
      nDevices++;
    }
    else if (error == 4)
    {
      //Report adress with 0 devices
    }
  }

  if (nDevices == 0)
  {
    GD.ColorRGB(0xff0000); GD.cmd_text(25, 52, 29, 0, "No I2C devices found...");
    GD.ColorRGB(0xffffff); GD.cmd_text(0, 95+18*1, 26, 0, "Did you configure the right pinout for your device?");
    GD.ColorRGB(0xffffff); GD.cmd_text(0, 95+18*2, 26, 0, "Please check your hardware.");
    GD.ColorRGB(0xffffff); GD.cmd_text(0, 95+18*3, 26, 0, "Restart your MCU for a new search.");
  }
  else
    
  GD.ColorRGB(0x00ff00);  GD.cmd_text((GD.w/2)+80, 25, 28, OPT_CENTERX, "Done");


  Parametros();
  GD.swap();
}
