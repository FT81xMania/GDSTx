#include <GDSTx.h>

char TXP[50];
char LoadTime[40];
uint32_t startJPG=0, endJPG=0, drawT=0;

void setup()
{
  GD.begin();

  startJPG = millis();
   GD.cmd_loadimage(0, 0);
   GD.load("tree.jpg");
  endJPG = millis();
  
  drawT=endJPG-startJPG;
  sprintf(LoadTime, "Load time: %d millis", drawT);

   MP();
}
void loop(){}

void MP()
{
  while(1)
 {
   GD.Clear();
   
   GD.SaveContext();
    GD.Begin(BITMAPS);
    GD.Vertex2f(0*16, 0*16);
   GD.RestoreContext();

   GD.SaveContext();
    GD.ColorRGB(0xff,0x00,0x00);
    GD.cmd_text(GD.w/2, (GD.h)-20, 29, OPT_CENTER, LoadTime);
   GD.RestoreContext();    

#if defined(__MK64FX512__) || defined(__MK66FX1M0__)
sprintf(TXP,"F_BUS: %d MHz", (F_BUS/1000000));  GD.cmd_text(GD.w-43, (GD.h)-20-30, 20, OPT_CENTER, TXP);
#endif

sprintf(TXP,"F_CPU: %d MHz", (F_CPU/1000000));  GD.cmd_text(GD.w-43, (GD.h)-22, 20, OPT_CENTER, TXP);
sprintf(TXP,"TFT-SPI speed: %d MHz", (SetSPISpeed/1000000));  GD.cmd_text(GD.w-55, (GD.h)-36, 20, OPT_CENTER, TXP);

#if defined(ARDUINO_ARCH_STM32)
sprintf(TXP,"SD-SPI speed: %d MHz", (SetSDSpeed));  GD.cmd_text(GD.w-54, (GD.h)-36-14, 20, OPT_CENTER, TXP);
#endif
   
   GD.swap();
 }
}