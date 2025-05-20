/*Basado en el ejemplo SdInfo de la libreria SDFat, 
 * Modificado por TFTLCDCyg -- 27 de Septiembre 2022 
*/

#include <GDSTx.h>
#include "sdios.h"
/*
  Set DISABLE_CS_PIN to disable a second SPI device.
  For example, with the Ethernet shield, set DISABLE_CS_PIN
  to 10 to disable the Ethernet controller.
*/
const int8_t DISABLE_CS_PIN = -1;

// Try to select the best SD card configuration.
#if HAS_SDIO_CLASS
 #define SD_CONFIG SdioConfig(FIFO_SDIO)
#elif ENABLE_DEDICATED_SPI

#if defined(ARDUINO_ARCH_STM32)

  #if (STM32_CPU==411)
   const uint8_t SD_CS_PIN = PB12;
   static SPIClass SPI_2(SPI2, PB15, PB14, PB13);
   #define SD_CONFIG SdSpiConfig(SD_CS_PIN, DEDICATED_SPI, SD_SCK_MHZ(18), &SPI_2)
   #define mySerialPort2 SerialUART2
   #define Serial mySerialPort2
  #endif

  #if (STM32_CPU==4073)
   const uint8_t SD_CS_PIN = PB12;
   static SPIClass SPI_2(SPI2, PB15, PB14, PB10);
   #define SD_CONFIG SdSpiConfig(SD_CS_PIN, DEDICATED_SPI, SD_SCK_MHZ(18), &SPI_2)
   #define mySerialPort2 SerialUART2
   #define Serial mySerialPort2
  #endif 

  #if (STM32_CPU==767)
   const uint8_t SD_CS_PIN = PB11;
   static SPIClass SPI_3(SPI3, PB2, PB4, PB3);
   #define SD_CONFIG SdSpiConfig(SD_CS_PIN, DEDICATED_SPI, SD_SCK_MHZ(18), &SPI_3)
   #define mySerialPort3 SerialUART3
   #define Serial mySerialPort3
  #endif
  
#endif
#endif

#if defined(ARDUINO_ARCH_RP2040)
  //const uint8_t SD_PIN = 13;         //SPI-1
  #define SD_CONFIG SdSpiConfig(13, DEDICATED_SPI, SD_SCK_MHZ(24), &SPI1)     //Bus SPI-1
#endif

//------------------------------------------------------------------------------
SdFs sd;
cid_t cid;
csd_t csd;
scr_t scr;
uint8_t cmd6Data[64];
uint32_t eraseSize;
uint32_t ocr;
static ArduinoOutStream cout(Serial);
//-----------------------------------------------------------------------------

char doubleTXT[40];
int TipoMicroSD = 0, SDSystem = 0, SpeedMode = 0, TVolume=0;
double Inicio = 0, MicroSDSize;

void setup() {
  IDEMCU();
  //#if defined(ARDUINO_ARCH_STM32)
  //if (STM32_CPU==767)
  // {
  //   Serial.stm32SetRX(PD9);
  //   Serial.stm32SetTX(PD8);
  // }
  // #endif
   
  Serial.begin(9600);

  cout << F("SdFat version: ") << SD_FAT_VERSION_STR << endl;
  printConfig(SD_CONFIG);
  InfoMicroSD();
  
  GD.begin();
     GD.cmd_loadimage(0, 0);
     GD.load("Fondo010.jpg");
  MP();

}
//------------------------------------------------------------------------------
void loop(){}

int X0=45, Y0=45, Y1 = 85, sepY=17, sizeTX=27;

void MP()
{
  
  while(1)
  {
    GD.ClearColorRGB(0x100020);
    GD.Clear();

    GD.SaveContext();
     GD.Begin(BITMAPS);
     GD.ColorA(50);
     GD.Vertex2f(0*16, 0*16);
    GD.RestoreContext();
    
     GD.cmd_text(X0-20, Y0-25, 26, 0, "SDInfo        SdFat version: ");
     GD.cmd_text(X0+175, Y0-10, 30, 0, SD_FAT_VERSION_STR);  
        
        if(SDSystem == 0)
          {
            GD.cmd_text(X0, Y1+sepY*1, sizeTX, 0,    "Interface:                   SPI device"); 
            #if defined(ARDUINO_ARCH_STM32)
            if (STM32_CPU==411)
            {
              GD.cmd_text(X0, Y1+sepY*2, sizeTX, 0, "Bus: SPI-2                  SD_CS = PB12");    
            }			
            if (STM32_CPU==767)
            {
              GD.cmd_text(X0, Y1+sepY*2, sizeTX, 0, "Bus: SPI-3                  SD_CS = PB11");    
            }
            #endif
          }
        
        if(SDSystem == 1){GD.cmd_text(X0, Y1+sepY*1, sizeTX, 0,    "Interface:                    SDIO"); }        

                                                 //sprintf(doubleTXT,"init time:                    %.0f ms",Inicio); GD.cmd_text(X0, Y1+sepY*2, sizeTX, 0, doubleTXT);
          
        if(TipoMicroSD == 0){GD.cmd_text(X0, Y1+sepY*3, sizeTX, 0, "Card type:                  Unknown"); }
        if(TipoMicroSD == 1){GD.cmd_text(X0, Y1+sepY*3, sizeTX, 0, "Card type:                  SD1"); }
        if(TipoMicroSD == 2){GD.cmd_text(X0, Y1+sepY*3, sizeTX, 0, "Card type:                  SD2"); }
        if(TipoMicroSD == 3){GD.cmd_text(X0, Y1+sepY*3, sizeTX, 0, "Card type:                  SDHC"); }
        if(TipoMicroSD == 4){GD.cmd_text(X0, Y1+sepY*3, sizeTX, 0, "Card type:                  SDXC"); }

        if(TVolume == 0){GD.cmd_text(X0, Y1+sepY*4, sizeTX, 0,     "Volume is                   FAT"); }
        if(TVolume == 1){GD.cmd_text(X0, Y1+sepY*4, sizeTX, 0,     "Volume is                   exFAT"); }

        if(SpeedMode == 0){GD.cmd_text(X0, Y1+sepY*5, sizeTX, 0,    "HighSpeedMode:      false"); }
        if(SpeedMode == 1){GD.cmd_text(X0, Y1+sepY*5, sizeTX, 0,    "HighSpeedMode:      true"); }           

        sprintf(doubleTXT,"cardsize: %.2f MB",MicroSDSize); GD.cmd_text(X0, Y1+sepY*6, sizeTX, 0, doubleTXT);

    GD.Begin(LINES);
     GD.ColorRGB(255,255,255);
     GD.Vertex2f(0*16, 0*16);    GD.Vertex2f((GD.w)*16, 0*16);  //Superior
     GD.Vertex2f(0*16, (GD.h-1)*16);  GD.Vertex2f((GD.w)*16, (GD.h-1)*16); //inferior
     GD.Vertex2f(0*16, 0*16);  GD.Vertex2f(0*16, (GD.h-1)*16); //izquierda
     GD.Vertex2f((GD.w-1)*16, 0*16);  GD.Vertex2f((GD.w-1)*16, (GD.h-1)*16); //derecha  

    IDEMCU();
    Parametros();
    
    GD.swap();
  }
}
