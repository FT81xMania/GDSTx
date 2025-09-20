/* Copyright (C) 2013-2021 by James Bowman <jamesb@excamera.com>
 * Gameduino 2/3 library for Arduino, Arduino Due, Raspberry Pi,
 * Teensy 3.x/4.0, ESP8266 and ESP32.
 * https://github.com/jamesbowman/gd2-lib
 *
 * In memory of mi brother Thomas (lighcalamar). THX bro for your teachings
 * Modified by TFTLCDCyg to Teensy 4/4.1 SDIO system               							    -- 09 March 2021
 * Riverdi FT801@4.3"                                                                    0
 * Riverdi FT813@5"                                                                     51
 * Riverdi FT813@7"                                                                     71
 * NHD FT813@3.5"                                                                       35
 * NHD FT813@4.3"                                                                       43
 * NHD FT813@5"                                                                          5
 * NHD FT813@7"                                                                          7
 * Support for SdFat V2 (Greimann)                               							    -- 12 April 2021
 * source: https://github.com/greiman/SdFat
 * Added timmings for Riverdi BT817@5"                               					    54	-- 01 Sept  2021
 * source: https://riverdi.com/download/RVT50HQBNWC00-B/DS_RVT50HQBNWC00-B_Rev.1.4.pdf                  p-13
 * Added STM32 boards support (for F411CE and F407VG, STM32-Danieleff Core) 		 411, 4073 	-- 13 April 2022
 * source: https://github.com/danieleff/STM32GENERIC 
 * Added BT817 for STM32 and teensy 4.1                              							-- 25 June  2022
 * Asset loading fix and renaming library to GDSTx, fixes for VET6, M3DEMO and M4DEMO		    -- 31 Aug   2022
 * Added STM32 boards (support for Core7XXI and Nucleo-F767ZI, STM32-Danieleff Core)  746,767	-- 31 Aug   2022
 * Added Matrix Orbital EVE3 BT815@5"		                                                52 	-- 03 Oct   2022
 * Added config.h; entry SizeFT813 renamed to SizeEVE   FT800/FT801-respond                     -- 28 Oct   2022
 * Added support for Core7XXI-F746IG (STM32 Core official 1.9.0, Nucleo F746ZG)         7460    -- 05 Nov   2022 
 * Added support for Nucleo H743ZI and Nucleo F767ZI (STM32 Core official 1.9.0)        7670    -- 05 Nov   2022
 * json path: https://github.com/stm32duino/BoardManagerFiles/raw/master/STM32/package_stm_index.json
 * Correction of the timing tables for the NHD TFT-EVE 2                                        -- 07 Nov   2022
 * source: https://github.com/NewhavenDisplay/EVE2-TFT-Gamduino2-Library/blob/main/NHD-Gameduino2-AppNotes.pdf
 * Test for Gameduino3-shield on STM32                                                          -- 09 Dec   2022
 * Rename SizeFT813 to SizeEVE and add config.h file                                            -- 06 Jan   2023
 * Update to version 2.01                                                                       -- 06 Jan   2023
 * Added MO EVE3x-43 timings                                                                    -- 06 Jun   2023
 * Added Riverdi RVT70HSBNWN00 timings                                                          -- 29 Nov   2023
 * Added STM32 board support: Black F446RE (Danieleff Core) 		                       446 	-- 14 Feb   2024
 * Added Raspberry Pi Pico RP2040                                                               -- 29 March 2024
 * Added MO 5" BT815 (SizeEVE=53)                                                               -- 19 May   2024  
 * SdFat/SdFs SD to SdFat/SdFs SSD To avoid conflicts with the SD-Class of SD.h library         -- 14 Nov   2024
  * VectorTactil_BT817 example is added to correct use of the BT817 touch panel for the first
   time. Possible failure between the GDSTx library and the first records of the EEPROM of
   the teensy 4.1. Later you can use self_calibrate to fine-tune the touch vector               -- 09 Jan   2025
 */
//FT81xmania team	

#include <Arduino.h>
#include "SPI.h"

#if defined(ARDUINO_ARCH_RP2040)                              //*******************************************************RP2040-Pico
 #define DISABLE_FS_H_WARNING  // Disable warning for type File not defined.
#endif

#if defined(ARDUINO_ARCH_STM32)  
 #define DISABLE_FS_H_WARNING  // Disable warning for type File not defined.
#endif

#include "SdFat.h"
#include <GDSTx.h>

#ifdef TEENSYDUINO 
 #include "EEPROM.h"
  #if defined(ARDUINO_TEENSY32)
   #define SD_CONFIG SdSpiConfig(SD_PIN, DEDICATED_SPI, SD_SCK_MHZ(18))
   SdFat SSD;    //In order to avoid conflict declaration with the SD Class of SD.h from teensyduino libraries
   //pinMode(SD_PIN, OUTPUT);
   //digitalWrite(SD_PIN, HIGH);
  #else 
   SdFs SSD; 
  #endif 
#endif

#if defined(ARDUINO_ARCH_STM32)

 #if(STM32_CPU == 103)
//                             MOSI  MISO  SCK
   static SPIClass SPI_2(SPI2, PB15, PB14, PB13);    //F103C8
   #define SD_CONFIG SdSpiConfig(SD_PIN, DEDICATED_SPI, SD_SCK_MHZ(SetSDSpeed), &SPI_2)
 #endif  

 #if(STM32_CPU == 411)
//                             MOSI  MISO  SCK
   extern SPIClass SPI_2(SPI2, PB15, PB14, PB13);   //F411CE
   #define SD_CONFIG SdSpiConfig(SD_PIN, DEDICATED_SPI, SD_SCK_MHZ(SetSDSpeed), &SPI_2)
 #endif  

 #if(STM32_CPU == 446)
//                             MOSI  MISO  SCK 
   extern SPIClass SPI_2(SPI2, PB15, PB14, PB13);   //F446RE      si funciona XD
   #define SD_CONFIG SdSpiConfig(SD_PIN, DEDICATED_SPI, SD_SCK_MHZ(SetSDSpeed), &SPI_2)
 #endif  

 #if(STM32_CPU == 4110)
//                       MOSI  MISO  SCK
   static SPIClass SPI_2(PB15, PB14, PB13);
   #define SD_CONFIG SdSpiConfig(SD_PIN, DEDICATED_SPI, SD_SCK_MHZ(SetSDSpeed), &SPI_2)
 #endif

 #if(STM32_CPU == 4073)
//                             MOSI  MISO  SCK
   extern SPIClass SPI_2(SPI2, PB15, PB14, PB10);   //M4DEMO, F407VG
   #define SD_CONFIG SdSpiConfig(SD_PIN, DEDICATED_SPI, SD_SCK_MHZ(SetSDSpeed), &SPI_2)
 #endif  
 
 #if(STM32_CPU == 4074)     //funciona en core STM32 Oficial
//                             MOSI  MISO  SCK
   extern SPIClass SPI_2(PB15, PB14, PB10);   //M4DEMO, F407VG
   #define SD_CONFIG SdSpiConfig(SD_PIN, DEDICATED_SPI, SD_SCK_MHZ(SetSDSpeed), &SPI_2)
 #endif   

 #if(STM32_CPU == 746)
//                            MOSI  MISO  SCK
   extern SPIClass SPI_3(SPI3, PB2, PB4, PB3);
   #define SD_CONFIG SdSpiConfig(SD_PIN, DEDICATED_SPI, SD_SCK_MHZ(SetSDSpeed), &SPI_3)
 #endif


 #if(STM32_CPU == 7460)
//                            MOSI  MISO  SCK
   extern SPIClass SPI_3(PB2, PB4, PB3);
   #define SD_CONFIG SdSpiConfig(SD_PIN, DEDICATED_SPI, SD_SCK_MHZ(SetSDSpeed), &SPI_3)
 #endif

 #if(STM32_CPU == 767)
//                            MOSI  MISO SCK
   extern SPIClass SPI_3(SPI3, PB2, PB4, PB3);
   #define SD_CONFIG SdSpiConfig(SD_PIN, DEDICATED_SPI, SD_SCK_MHZ(SetSDSpeed), &SPI_3)
 #endif


  #if(STM32_CPU == 7670)
   //SdFat beta 2  on Official core STM32
   static SPIClass SPI_3(PB2, PB4, PB3);
   #define SD_CONFIG SdSpiConfig(SD_PIN, DEDICATED_SPI, SD_SCK_MHZ(SetSDSpeed), &SPI_3)
   //#define SD_CONFIG SdSpiConfig(SD_PIN, ENABLE_DEDICATED_SPI, SD_SCK_MHZ(SetSDSpeed), &SPI_3)
  #endif

 SdFs SSD;  //type 3
#endif 

#if defined(ARDUINO_ARCH_RP2040)                              //*******************************************************RP2040-Pico
   #include "EEPROM.h"
   #define SD_CONFIG SdSpiConfig(SD_PIN, DEDICATED_SPI, SD_SCK_MHZ(SetSDSpeed), &SPI1)     //Bus SPI-1
   SdFs SSD;                                                              //type 3   
#endif                                                        //*******************************************************RP2040-Pico

#if defined(ARDUINO_UNOR4_MINIMA)                             //******************************************************Arduino UNO R4 MINIMA
   #include "EEPROM.h"
   #define SD_CONFIG SdSpiConfig(SD_PIN, DEDICATED_SPI, SD_SCK_MHZ(SetSDSpeed))     //Bus SPI-1
   SdFs SSD;                                                              //type 3   
#endif                                                       //*******************************************************Arduino UNO R4 MINIMA


//FT81xmania team

byte ft8xx_model;
uint16_t BT8XX; // 0x00:FT800/0x10:FT810/0x11:FT811/0x12:FT812/0x13:FT813/0x15:BT815/0x16:BT816/0x17:BT817     Función interna de la libreria
#include "transports/wiring.h"

////////////////////////////////////////////////////////////////////////

void xy::set(int _x, int _y)
{
  x = _x;
  y = _y;
}

void xy::rmove(int distance, int angle)
{
  x -= GD.rsin(distance, angle);
  y += GD.rcos(distance, angle);
}

int xy::angleto(class xy &other)
{
  int dx = other.x - x, dy = other.y - y;
  return GD.atan2(dy, dx);
}

void xy::draw(byte offset)
{
  GD.Vertex2f(x - PIXELS(offset), y - PIXELS(offset));
}

int xy::onscreen(void)
{
  return (0 <= x) &&
         (x < PIXELS(GD.w)) &&
         (0 <= y) &&
         (y < PIXELS(GD.h));
}

class xy xy::operator+=(class xy &other)
{
  x += other.x;
  y += other.y;
  return *this;
}

class xy xy::operator-=(class xy &other)
{
  x -= other.x;
  y -= other.y;
  return *this;
}

class xy xy::operator<<=(int d)
{
  x <<= d;
  y <<= d;
  return *this;
}

long xy::operator*(class xy &other)
{
  return (long(x) * other.x) + (long(y) * other.y);
}

class xy xy::operator*=(int s)
{
  x *= s;
  y *= s;
  return *this;
}

int xy::nearer_than(int distance, xy &other)
{
  int lx = abs(x - other.x);
  if (lx > distance)
    return 0;
  int ly = abs(y - other.y);
  if (ly > distance)
    return 0;

  // trivial accept: 5/8 is smaller than 1/sqrt(2)
  int d2 = (5 * distance) >> 3;
  if ((lx < d2) && (ly < d2))
    return 1;

#define SQ(c) (long(c) * (c))
  return (SQ(lx) + SQ(ly)) < SQ(distance);
#undef SQ
}

void xy::rotate(int angle)
{
  // the hardware's convention that rotation is clockwise
  int32_t s = GD.rsin(32767, angle);
  int32_t c = GD.rcos(32767, angle);

  int xr = ((x * c) - (y * s)) >> 15;
  int yr = ((x * s) + (y * c)) >> 15;
  x = xr;
  y = yr;
}

////////////////////////////////////////////////////////////////////////

void Bitmap::fromtext(int font, const char* s)
{
  GD.textsize(size.x, size.y, font, s);
  int pclk = GD.rd16(REG_PCLK);
  int vsize = GD.rd16(REG_VSIZE);
  int hsize = GD.rd16(REG_HSIZE);

  GD.finish();
  GD.wr(REG_PCLK, 0);
  delay(1);
  GD.wr16(REG_HSIZE, size.x);
  GD.wr16(REG_VSIZE, size.y);

  GD.cmd_dlstart();
  GD.Clear();
  GD.BlendFunc(1,1);
  GD.cmd_text(0, 0, font, 0, s);
  GD.swap();

  GD.loadptr = (GD.loadptr + 1) & ~1;
  GD.cmd_snapshot(GD.loadptr);
  GD.finish();

  GD.wr16(REG_HSIZE, hsize);
  GD.wr16(REG_VSIZE, vsize);
  GD.wr16(REG_PCLK, pclk);
  defaults(ARGB4);
}

void Bitmap::fromfile(const char* filename, int format)
{
  GD.loadptr = (GD.loadptr + 1) & ~1;
  GD.cmd_loadimage(GD.loadptr, OPT_NODL);
  GD.load(filename);
  uint32_t ptr, w, h;
  GD.cmd_getprops(ptr, w, h);
  GD.finish();
  size.x = GD.rd16(w);
  size.y = GD.rd16(h);
  defaults(format);
}

static const PROGMEM uint8_t bpltab[] = {
/* 0  ARGB1555  */ 0xff,
/* 1  L1        */ 3,
/* 2  L4        */ 1,
/* 3  L8        */ 0,
/* 4  RGB332    */ 0,
/* 5  ARGB2     */ 0,
/* 6  ARGB4     */ 0xff,
/* 7  RGB565    */ 0xff,
/* 8  PALETTED  */ 0,
/* 9  TEXT8X8   */ 0xff,
/* 10 TEXTVGA   */ 0xff,
/* 11 BARGRAPH  */ 0,
/* 12           */ 0xff,
/* 13           */ 0xff,
/* 14           */ 0xff,
/* 15           */ 0xff,
/* 16           */ 0xff,
/* 17 L2        */ 2
};

static uint16_t stride(uint8_t format, uint16_t w)
{
  uint8_t k = pgm_read_byte_near(bpltab + format);
  if (k == 0xff)
    return w << 1;
  uint16_t r = (1 << k) - 1;
  return (w + r) >> k;
}

void Bitmap::defaults(uint8_t f)
{
  source = GD.loadptr;
  format = f;
  handle = -1;
  center.x = size.x / 2;
  center.y = size.y / 2;
  GD.loadptr += stride(format, size.x) * size.y;
}

void Bitmap::setup(void)
{
  GD.BitmapSource(source);
  GD.BitmapLayout(format, stride(format, size.x), size.y);
  GD.BitmapSize(NEAREST, BORDER, BORDER, size.x, size.y);
}

void Bitmap::bind(uint8_t h)
{
  handle = h;

  GD.BitmapHandle(handle);
  setup();
}

#define IS_POWER_2(x) (((x) & ((x) - 1)) == 0)

void Bitmap::wallpaper()
{
  if (handle == -1) {
    GD.BitmapHandle(15);
    setup();
  } else {
    GD.BitmapHandle(handle);
  }
  GD.Begin(BITMAPS);
  // if power-of-2, can just use REPEAT,REPEAT
  // otherwise must draw it across whole screen
  if (IS_POWER_2(size.x) && IS_POWER_2(size.y)) {
    GD.BitmapSize(NEAREST, REPEAT, REPEAT, GD.w, GD.h);
    GD.Vertex2f(0, 0);
  } else {
    for (int x = 0; x < GD.w; x += size.x)
      for (int y = 0; y < GD.h; y += size.y)
        GD.Vertex2f(x << 4, y << 4);
  }
}

void Bitmap::draw(int x, int y, int16_t angle)
{
  xy pos;
  pos.set(x, y);
  pos <<= GD.vxf;
  draw(pos, angle);
}

void Bitmap::draw(const xy &p, int16_t angle)
{
  xy pos = p;
  if (handle == -1) {
    GD.BitmapHandle(15);
    setup();
  } else {
    GD.BitmapHandle(handle);
  }
  GD.Begin(BITMAPS);

  if (angle == 0) {
    xy c4 = center;
    c4 <<= GD.vxf;
    pos -= c4;
    GD.BitmapSize(NEAREST, BORDER, BORDER, size.x, size.y);
    GD.Vertex2f(pos.x, pos.y);
  } else {
    // Compute the screen positions of 4 corners of the bitmap
    xy corners[4] = {
      {0,0              },
      {size.x,  0       },
      {0,       size.y  },
      {size.x,  size.y  },
    };
    for (int i = 0; i < 4; i++) {
      xy &c = corners[i];
      c -= center;
      c <<= GD.vxf;
      c.rotate(angle);
      c += pos;
    }

    // Find top-left and bottom-right boundaries
    xy topleft, bottomright;
    topleft.set(
      min(min(corners[0].x, corners[1].x), min(corners[2].x, corners[3].x)),
      min(min(corners[0].y, corners[1].y), min(corners[2].y, corners[3].y)));
    bottomright.set(
      max(max(corners[0].x, corners[1].x), max(corners[2].x, corners[3].x)),
      max(max(corners[0].y, corners[1].y), max(corners[2].y, corners[3].y)));

    // span is the total size of this region
    xy span = bottomright;
    span -= topleft;
    GD.BitmapSize(BILINEAR, BORDER, BORDER,
                  (span.x + 15) >> GD.vxf, (span.y + 15) >> GD.vxf);

    // Set up the transform and draw the bitmap
    pos -= topleft;
    GD.SaveContext();
    GD.cmd_loadidentity();
    int s = 16 - GD.vxf;
    GD.cmd_translate((int32_t)pos.x << s, (int32_t)pos.y << s);
    GD.cmd_rotate(angle);
    GD.cmd_translate(F16(-center.x), F16(-center.y));
    GD.cmd_setmatrix();
    GD.Vertex2f(topleft.x, topleft.y);
    GD.RestoreContext();
  }
}

class Bitmap __fromatlas(uint32_t a)
{
  Bitmap r;
  r.size.x    = GD.rd16(a);
  r.size.y    = GD.rd16(a + 2);
  r.center.x  = GD.rd16(a + 4);
  r.center.y  = GD.rd16(a + 6);
  r.source    = GD.rd32(a + 8);
  r.format    = GD.rd(a + 12);
  r.handle    = -1;
  return r;
}

////////////////////////////////////////////////////////////////////////

static GDTransport GDTR;

GDClass GD;

////////////////////////////////////////////////////////////////////////

// The GD3 has a tiny configuration EEPROM - AT24C01D
// It is programmed at manufacturing time with the setup
// commands for the connected panel. The SCL,SDA lines
// are connected to the FT81x GPIO0, GPIO1 signals.
// This is a read-only driver for it.  A single method
// 'read()' initializes the RAM and reads all 128 bytes
// into an array.

class ConfigRam {
private:
  uint8_t gpio, gpio_dir, sda;
  void set_SDA(byte n)
  {
    if (sda != n) {
      GDTR.__wr16(REG_GPIO_DIR, gpio_dir | (0x03 - n));    // Drive SCL, SDA low
      sda = n;
    }
  }

  void set_SCL(byte n)
  {
    GDTR.__wr16(REG_GPIO, gpio | (n << 1));
  }

  int get_SDA(void)
  {
    return GDTR.__rd16(REG_GPIO) & 1;
  }

  void i2c_start(void)
  {
    set_SDA(1);
    set_SCL(1);
    set_SDA(0);
    set_SCL(0);
  }

  void i2c_stop(void)
  {
    set_SDA(0);
    set_SCL(1);
    set_SDA(1);
    set_SCL(1);
  }

  int i2c_rx1()
  {
    set_SDA(1);
    set_SCL(1);
    byte r = get_SDA();
    set_SCL(0);
    return r;
  }

  void i2c_tx1(byte b)
  {
    set_SDA(b);
    set_SCL(1);
    set_SCL(0);
  }

  int i2c_tx(byte x)
  {
    for (byte i = 0; i < 8; i++, x <<= 1)
      i2c_tx1(x >> 7);
    return i2c_rx1();
  }

  int i2c_rx(int nak)
  {
    byte r = 0;
    for (byte i = 0; i < 8; i++)
      r = (r << 1) | i2c_rx1();
    i2c_tx1(nak);
    return r;
  }

public:
  void read(byte *v)
  {
    GDTR.__end();
    gpio = GDTR.__rd16(REG_GPIO) & ~3;
    gpio_dir = GDTR.__rd16(REG_GPIO_DIR) & ~3;
    sda = 2;

    // 2-wire software reset
    i2c_start();
    i2c_rx(1);
    i2c_start();
    i2c_stop();

    int ADDR = 0xa0;

    i2c_start();
    if (i2c_tx(ADDR))
      return;
    if (i2c_tx(0))
      return;

    i2c_start();
    if (i2c_tx(ADDR | 1))
      return;
    for (int i = 0; i < 128; i++) {
      *v++ = i2c_rx(i == 127);
     
    }
    i2c_stop();
    GDTR.resume();
  }
};

//RndMnkIII, FT81xmania Team
const uint16_t GDClass::TAM_BUFFER_SD=8192;  //8192
const uint16_t GDClass::TAM_BUFFER_FT=2048;  //2048  
byte GDClass::buf[TAM_BUFFER_SD];
byte GDClass::FTbuf[TAM_BUFFER_FT];
//RndMnkIII, FT81xmania Team

void GDClass::flush(void)
{
  GDTR.flush();
}

void GDClass::swap(void) {
  Display();
  cmd_swap();
  cmd_loadidentity();
  cmd_dlstart();
  GDTR.flush();
}

uint32_t GDClass::measure_freq(void)
{
  unsigned long t0 = GDTR.rd32(REG_CLOCK);
  delayMicroseconds(15625);
  unsigned long t1 = GDTR.rd32(REG_CLOCK);
  
  return (t1 - t0) << 6;
}

//#define LOW_FREQ_BOUND  47040000UL
//#define LOW_FREQ_BOUND  32040000UL

void GDClass::tune(void)
{
	
  if (BT8XX==1)
 {
  Serial.print("FT80");  Serial.println(BT8XX, HEX);
 }
 
 if (BT8XX==19)
 {
  Serial.print("FT8");  Serial.println(BT8XX, HEX); 
 }
 
 if (BT8XX>19)
 {
  Serial.print("BT8");  Serial.println(BT8XX, HEX); 
 } 
 //Serial.print("TFT id: ");  Serial.println(SizeEVE);  Serial.print("SPI-1 speed: ");   Serial.println(SetSPISpeed);
 //Serial.print("TFT id: ");  Serial.println(SizeEVE);  
 //Serial.print("SPI-1 speed (MHz): ");   Serial.println(SetSPISpeed/1000000);
 //Serial.print(rd32(REG_HSIZE));  Serial.print("x");   Serial.print(rd32(REG_VSIZE));    Serial.println(" px");	
	
 uint32_t LOW_FREQ_BOUND = 32040000UL;  //FT801/801
 LOW_FREQ_BOUND = 47040000UL;           //FT81X/BT815/BT816

if (SizeEVE==0){                  //FT801   XD
LOW_FREQ_BOUND =  32040000UL;     //
}

if (SizeEVE==71){                 //FT813
LOW_FREQ_BOUND =  47040000UL;     //
}

if (SizeEVE==5){                  //FT813
LOW_FREQ_BOUND =  47040000UL;     //
//LOW_FREQ_BOUND =    55000000UL; //
}

if (SizeEVE==510){                //FT810
LOW_FREQ_BOUND =  47040000UL;     //
//LOW_FREQ_BOUND =    55000000UL; //
}

if (SizeEVE==7){                  //FT813
LOW_FREQ_BOUND =  47040000UL;     //
}

if (SizeEVE==38){                 //FT813
LOW_FREQ_BOUND =  47040000UL;     //
}

if (SizeEVE==35){                 //FT813
LOW_FREQ_BOUND =  47040000UL;     //
}

if (SizeEVE==43){                 //FT813
LOW_FREQ_BOUND =  47040000UL;     //
}

if (SizeEVE==431){                // BT815/16
LOW_FREQ_BOUND =  59000000UL;     // 
}

if (SizeEVE==51){                 //FT813
LOW_FREQ_BOUND =  47040000UL;     //
}

if (SizeEVE==52){                 //BT815
LOW_FREQ_BOUND =  59000000UL;     //a mayor frecuencia posible inestabilidad de la pantalla al reproducir videos MO-52; este TFT es demasiado sensible, no conectar GND al conector de audio de 3.5 mm
}

if (SizeEVE==53){                 //BT815-test MO 5"
LOW_FREQ_BOUND =  47040000UL;     // mejor para reproducción de video
//LOW_FREQ_BOUND =  60000000UL;   // acelera salida de audio e incrementa el ruido en el monitor FFT
}

if (SizeEVE==434){                 //BT817/BT818
LOW_FREQ_BOUND =  60000000UL;     // 59000000UL   óptimo
}

if (SizeEVE==54){                 //BT817/BT818
LOW_FREQ_BOUND =  59000000UL;     // 59000000UL   óptimo
}

if (SizeEVE==74){                 //BT817/BT818
LOW_FREQ_BOUND =  60000000UL;     // 59000000UL   óptimo
}

if (SizeEVE==100){                //BT817/BT818
LOW_FREQ_BOUND =  59000000UL;     //  59000000UL   óptimo
}
 
 //Serial.println("****");
 
  uint32_t f;
  for (byte i = 0; (i < 31) && ((f = measure_freq()) < LOW_FREQ_BOUND); i++) {
    GDTR.wr(REG_TRIM, i);
  }
  
  //Serial.print("REG_FREQUENCY: ");   Serial.println(REG_FREQUENCY);
  //Serial.println("****");
  //Serial.println(" ");
}

void GDClass::begin(int cs) {

  GDTR.begin0(cs);
  //byte external_crystal = 0;
  
  //#if defined(ARDUINO_TEENSY32)
#if defined(ARDUINO_ARCH_STM32)

  #if(STM32_CPU == 746)
    //delay(400);  //mejora el inicio de la microSD para videos en la CoreXXI  ----experimental
  #endif  
   //SD.begin( SdSpiConfig(SD_PIN, DEDICATED_SPI, SD_SCK_MHZ(36)) );
  SSD.begin(SD_CONFIG);
   

#endif	

#ifdef TEENSYDUINO
 #if defined(ARDUINO_TEENSY32)
   //pinMode(SD_PIN, OUTPUT);
   //digitalWrite(SD_PIN, HIGH);
   //SSD.begin(SD_CONFIG);
   SSD.begin(SD_PIN);
 #else    
	SSD.begin(SdioConfig(FIFO_SDIO));
 #endif
#endif


#if defined(ARDUINO_ARCH_RP2040)                              //*******************************************************RP2040-Pico
	SSD.begin(SD_CONFIG);
#endif                                                        //*******************************************************RP2040-Pico


#if defined(ARDUINO_UNOR4_MINIMA)                              //*******************************************************ARDUINO_UNOR4_MINIMA
	SSD.begin(SD_CONFIG);
#endif                                                        //*******************************************************ARDUINO_UNOR4_MINIMA
  
  //begin1:
  GDTR.begin1();

  Clear();
  swap();
  finish();

//#if 0
  //Serial.print("cs: ");
  //Serial.println(cs, DEC);
  //Serial.print("model: ");
  //Serial.println(ft8xx_model, HEX);
  //Serial.print("ID REGISTER: ");
  //Serial.println(GDTR.rd32(REG_ID), HEX);
  //Serial.print("READ PTR:");
  //Serial.println(GDTR.rd32(REG_CMD_READ), HEX);
  //Serial.print("WRITE PTR:");
  //Serial.println(GDTR.rd32(REG_CMD_WRITE), HEX);
  //Serial.print("CMDB SPACE:");
  //Serial.println(GDTR.rd32(REG_CMDB_SPACE), HEX);
//#endif

  GDTR.wr(REG_PWM_DUTY, 0);
  GDTR.wr(REG_GPIO_DIR, 0x83);
  GDTR.wr(REG_GPIO, GDTR.rd(REG_GPIO) | 0x80);

  Clear(); swap();
{
  //switch (ft8xx_model) {
  //tune();	  

    #if(STM32_CPU == 767)
		Serial.stm32SetRX(PD9);
		Serial.stm32SetTX(PD8);
		Serial.begin(115200);
    #endif	
  
  

 if (SizeEVE==0)
 {
	 #if 0
     #endif

//Gameduino3 shield
if (GameduinoX==1){
	GD.wr32(REG_HCYCLE,        548);
	GD.wr32(REG_VCYCLE,        292);    
    cmd_regwrite(REG_OUTBITS,  666);
    cmd_regwrite(REG_DITHER,     1);
    cmd_regwrite(REG_ROTATE,     ROTACION);
    cmd_regwrite(REG_SWIZZLE,    3); //3 gameduino 23X   
    cmd_regwrite(REG_PCLK_POL,   1); //1 gameduino 23X   
    cmd_regwrite(REG_PCLK,       5);
   }

//NHD43 and FT843    FT801
if (GameduinoX==0){
	GD.wr32(REG_HCYCLE,        548);
	GD.wr32(REG_VCYCLE,        292);    
    cmd_regwrite(REG_OUTBITS,  666);
    cmd_regwrite(REG_DITHER,     1);
    cmd_regwrite(REG_ROTATE,     ROTACION);
    cmd_regwrite(REG_SWIZZLE,    0);
    cmd_regwrite(REG_PCLK_POL,   0);
    cmd_regwrite(REG_PCLK,       5);	
   }
	
 }


//TFT Riverdi 5"
if (SizeEVE==51){
	cmd_setrotate(ORIENTACION);
    GD.wr32(REG_HCYCLE, 1056);    
    GD.wr32(REG_HOFFSET,  46);     
    GD.wr32(REG_HSIZE,   800);
    GD.wr32(REG_HSYNC0,    0);
    GD.wr32(REG_HSYNC1,   10);      
    GD.wr32(REG_VCYCLE,  525);     
    GD.wr32(REG_VOFFSET,  23);     
    GD.wr32(REG_VSIZE,   480);
    GD.wr32(REG_VSYNC0,    0);
    GD.wr32(REG_VSYNC1,   10);

    GD.wr32(REG_PCLK,      2);
    GD.wr32(REG_PCLK_POL,  0);
    GD.wr32(REG_CSPREAD,   0);      
    GD.wr32(REG_DITHER,    1);       
}
//TFT Riverdi 5"

//TFT Riverdi 5"             EVE4     Datasheet Rev.0.1 2020-12-29   p.15/21      BT817
if (SizeEVE==541){
	cmd_setrotate(ORIENTACION);
    GD.wr32(REG_HSIZE,  800);  //      Thdisp       visible horizontal line length 
    GD.wr32(REG_VSIZE,  480);  //      Tvdisp       number of visible lines 

    GD.wr32(REG_HCYCLE, 816 ); //808 816 896  816  Th       Period time H One Horizontal Line length (visible/invisible)  816
    GD.wr32(REG_HOFFSET,  8);  //4   8   48   8     Thbp      HS Back porch         8
    GD.wr32(REG_HSYNC0,   0);  //4   8   48   8     Thfp      HS front porch        8   
    GD.wr32(REG_HSYNC1,   4);  //2   4   8    4     Thw       HS pulse width        4   
	
    GD.wr32(REG_VCYCLE, 496);  //488 496 504  504  Tv        Period time V       496 
	GD.wr32(REG_VOFFSET,  8);  //4   8   12   12   Tvbp      VS Back porch        12
    GD.wr32(REG_VSYNC0,   0);  //4   8   12   12    Tvfp      VS front porch        8 
    GD.wr32(REG_VSYNC1,   4);  //2   4   8    8     Tvw       VS pulse width        4 

    GD.wr32(REG_PCLK,     2);  //2, 1, 0       2:REG_PCLK_FREQ              2
	GD.wr32(REG_SWIZZLE,  0);  //0 1  3                                     0        
	GD.wr32(REG_PCLK_POL, 1);  //1, 0    0 to off vertical lines on horizontal gradients    1
	GD.wr32(REG_CSPREAD,  0);  //0                                                          0                 
	GD.wr32(REG_DITHER,   1);  //1, 0                                                       1
	//GD.wr32(REG_PCLK_FREQ, 0xD14);        //0                                      0xD14
		
	//GD.wr32(REG_OUTBITS,  0xfff);      //0x360  0xff0                               
		
	//cmd_regwrite(REG_PWM_DUTY, 128);
	//test with cmd_testcard() in order to correct the timmings   p189, BRT_AN_033_BT81X
}
//TFT Riverdi 5"             EVE4     Datasheet Rev.0.1 2020-12-29   p.15/21      BT817

if (SizeEVE==434){
	cmd_setrotate(ORIENTACION);
    GD.wr32(REG_HSIZE,   480);  // 800     Thdisp       visible horizontal line length 
    GD.wr32(REG_VSIZE,   272);  //480      Tvdisp       number of visible lines 

    GD.wr32(REG_HCYCLE,  531); //485    531    598  Th       Period time H One Horizontal Line length (visible/invisible) 531
    GD.wr32(REG_HOFFSET,  43);  // 3     43     43     Thbp      HS Back porch      43
    GD.wr32(REG_HSYNC0,    0);   //2      8     75     Thfp      HS front porch      0   
    GD.wr32(REG_HSYNC1,    4);   //2      4     43     Thw       HS pulse width      4   
	
    GD.wr32(REG_VCYCLE,  292);  //276   292     321   Tv        Period time V       292 
	GD.wr32(REG_VOFFSET,  12);  //  2    12      12   Tvbp      VS Back porch        0
    GD.wr32(REG_VSYNC0,    0);   // 2     8      37   Tvfp      VS front porch       0 
    GD.wr32(REG_VSYNC1,    4);   // 2     4      12     Tvw       VS pulse width     4 

    GD.wr32(REG_PCLK,      1);          //2, 1, 0       2:REG_PCLK_FREQ              1
	GD.wr32(REG_SWIZZLE,   0);          //0 1  3                                     0        
	GD.wr32(REG_PCLK_POL,  1);          //1, 0    0 to off vertical lines on horizontal gradients    1
	GD.wr32(REG_CSPREAD,   0);          //0                                          0                 
	GD.wr32(REG_DITHER,    1);          //1, 0                                       1
	GD.wr32(REG_PCLK_FREQ, 0xD14);      //0                                        0xD14
		
	//GD.wr32(REG_OUTBITS, 0xfff);      //0x360  0xff0                               
		
	//cmd_regwrite(REG_PWM_DUTY, 128);
	//test with cmd_testcard() in order to correct the timmings   p189, BRT_AN_033_BT81X
}
//TFT Riverdi 5"             EVE4     Datasheet Rev.0.1 2020-12-29   p.15/21      BT817


if (SizeEVE==54){
	cmd_setrotate(ORIENTACION);
    GD.wr32(REG_HSIZE,   800);  //      Thdisp       visible horizontal line length 
    GD.wr32(REG_VSIZE,   480);  //      Tvdisp       number of visible lines 

    GD.wr32(REG_HCYCLE,  816 ); //808 816 896  816  Th       Period time H One Horizontal Line length (visible/invisible)  816
    GD.wr32(REG_HOFFSET,   8);  //4   8   48   8     Thbp      HS Back porch         8
    GD.wr32(REG_HSYNC0,    8);   //4   8   48   8     Thfp      HS front porch       0   
    GD.wr32(REG_HSYNC1,    4);   //2   4   8    4     Thw       HS pulse width       4   
	
    GD.wr32(REG_VCYCLE,  496);  //488 496 504  504  Tv        Period time V        496 
	GD.wr32(REG_VOFFSET,  8);  //4   8   12   12   Tvbp      VS Back porch          8
    GD.wr32(REG_VSYNC0,   8);   //4   8   12   12    Tvfp      VS front porch       0 
    GD.wr32(REG_VSYNC1,    4);   //2   4   8    8     Tvw       VS pulse width       4 

    GD.wr32(REG_PCLK,      1);             //2, 1, 0       2:REG_PCLK_FREQ           1
	GD.wr32(REG_SWIZZLE,   0);          //0 1  3                                     0        
	GD.wr32(REG_PCLK_POL,  1);         //1, 0    0 to off vertical lines on horizontal gradients    1
	GD.wr32(REG_CSPREAD,   0);          //0                                          0                 
	GD.wr32(REG_DITHER,    1);           //1, 0                                      1
	GD.wr32(REG_PCLK_FREQ, 0xD14);    //0                                        0xD14
		
	//GD.wr32(REG_OUTBITS, 0xfff);      //0x360  0xff0                               
		
	//cmd_regwrite(REG_PWM_DUTY, 128);
	//test with cmd_testcard() in order to correct the timmings   p189, BRT_AN_033_BT81X
}
//TFT Riverdi 5"             EVE4     Datasheet Rev.0.1 2020-12-29   p.15/21      BT817


if (SizeEVE==74){
	cmd_setrotate(ORIENTACION);
    GD.wr32(REG_HSIZE,   1024);  
    GD.wr32(REG_VSIZE,    600);  

    GD.wr32(REG_HCYCLE,  1344); 
    GD.wr32(REG_HOFFSET,  160);  
    GD.wr32(REG_HSYNC0,     0);  
    GD.wr32(REG_HSYNC1,    70);  
	
    GD.wr32(REG_VCYCLE,   635);  
	GD.wr32(REG_VOFFSET,   23);  
    GD.wr32(REG_VSYNC0,     0);  
    GD.wr32(REG_VSYNC1,    10);  

    GD.wr32(REG_PCLK,       1);  
	GD.wr32(REG_SWIZZLE,    0);  
	GD.wr32(REG_PCLK_POL,   1);  
	GD.wr32(REG_CSPREAD,    0);  
	GD.wr32(REG_DITHER,     0);  
	GD.wr32(REG_PCLK_FREQ,  0xD12);
		
	//test with cmd_testcard() in order to correct the timmings   p189, BRT_AN_033_BT81X
}
//TFT Riverdi 7"             EVE4     Datasheet Rev.1.7 2022-11-30   p.14/19      BT817


//TFT Riverdi 10"    12.1"            EVE4     Datasheet Rev.0.1 2020-12-29   p.15/21
if (SizeEVE==100){                    //  Experimental
	cmd_setrotate(ORIENTACION);
    GD.wr32(REG_HSIZE,  1280);   //      Thd       visible horizontal line length 
    GD.wr32(REG_VSIZE,   800);   //      Tvd       number of visible lines 

    GD.wr32(REG_HCYCLE, 1440);   //808 816 896  816 Th        One Horizontal Line length (visible/invisible)
    GD.wr32(REG_HOFFSET,  88);   //4   8   48   8   Thbp       HS Blanking            
    GD.wr32(REG_HSYNC0,   72);   //4   8   48   8   Thfp      HS front porch         
    GD.wr32(REG_HSYNC1,    4);   //2   4   8    4   Thpw/Thw  HS pulse width         
	
    GD.wr32(REG_VCYCLE,  838);   //488 496 504  504 Tv        VS period time         
    GD.wr32(REG_VOFFSET,  23);   //4   8   12   12   Tvb       VS Blanking            
    GD.wr32(REG_VSYNC0,   15);   //4   8   12   12   Tvfp      VS front porch         
    GD.wr32(REG_VSYNC1,    4);   //2   4   8    8   Tvpw/Tvw  VS pulse width         

    GD.wr32(REG_PCLK,      1);   //2, 1, 0       1:REG_PCLK_FREQ
	GD.wr32(REG_SWIZZLE,   0);   //0 1  3
	GD.wr32(REG_PCLK_POL,  1);         //1, 0    0 to off vertical lines on horizontal gradients    1
	GD.wr32(REG_CSPREAD,   0);          //0                                          0                 
	GD.wr32(REG_DITHER,    1);           //1, 0                                      1
	GD.wr32(REG_PCLK_FREQ, 0xD14);    //0                                        0xD14

	//cmd_regwrite(REG_PWM_DUTY, 128);
}
//TFT Riverdi 10"   EVE4



//TFT MO BT815 5"
if (SizeEVE==53){
	cmd_setrotate(ORIENTACION);
    GD.wr32(REG_HSIZE,  800);
    GD.wr32(REG_VSIZE,  480);

    GD.wr32(REG_HCYCLE, 928);
    GD.wr32(REG_HOFFSET, 88);
    GD.wr32(REG_HSYNC0,   0);
    GD.wr32(REG_HSYNC1,  48); 

    GD.wr32(REG_VCYCLE, 525);
    GD.wr32(REG_VOFFSET, 32);
    GD.wr32(REG_VSYNC0,   0);
    GD.wr32(REG_VSYNC1,   3);

    GD.wr32(REG_PCLK,     2);
    GD.wr32(REG_SWIZZLE,  0);
    GD.wr32(REG_PCLK_POL, 1);
    GD.wr32(REG_CSPREAD,  0);
    GD.wr32(REG_DITHER,   1);
    GD.wr16(REG_TOUCH_CONFIG, 0x05D1);  //funciona en BT815
	//GD.wr16(REG_TOUCH_CONFIG, 0x05d0);  //funciona en BT815
}
//TFT MO BT815 5"

if (SizeEVE==35)
  {
	  cmd_setrotate(ORIENTACION);
	GD.wr32(REG_HSIZE,  320);//320
	GD.wr32(REG_HCYCLE, 408);//408
	GD.wr32(REG_HOFFSET, 70);//70
	GD.wr32(REG_HSYNC0,   0);//0
	GD.wr32(REG_HSYNC1,  10);//10

	GD.wr32(REG_VSIZE,  240);//240
	GD.wr32(REG_VCYCLE, 263);//263
	GD.wr32(REG_VOFFSET, 13);//13
	GD.wr32(REG_VSYNC0,   0);//0
	GD.wr32(REG_VSYNC1,   2);//2

	GD.wr32(REG_PCLK,     8);//6
	GD.wr32(REG_SWIZZLE,  2);//2     3 for GD2
	GD.wr32(REG_PCLK_POL, 0);//1
	GD.wr32(REG_CSPREAD,  1);//0
	GD.wr32(REG_DITHER,   1);//0
	//GD.wr(REG_ROTATE, 0);
  }


if (SizeEVE==510)
  {
	  //datasheet    https://www.haoyuelectronics.com/Attachment/HY5-LCD-HD/KD50G21-40NT-A1.pdf
	cmd_setrotate(ORIENTACION);
    GD.wr32(REG_HSIZE,   800);   //  thd       visible horizontal line length 
    GD.wr32(REG_VSIZE,   480);   //  tvd       number of visible lines 

    GD.wr32(REG_HCYCLE,  928 );  //  Th        Period time H One Horizontal Line length (visible/invisible)  Min 889   typ  928    Max    1143
    GD.wr32(REG_HOFFSET,  88);   //  Thb      HS Back porch           88
    GD.wr32(REG_HSYNC0,   40);   //  Thfp      HS front porch         Min 1     typ   40    Max    255     
    GD.wr32(REG_HSYNC1,   48);   //  Thpw       HS pulse width        Min 1     typ   48    Max    255       
	
    GD.wr32(REG_VCYCLE,  525);   //  Tv        Period time V          Min 513   typ  525    Max    767
	GD.wr32(REG_VOFFSET,  32);    // Tvb       VS Back porch          32
    GD.wr32(REG_VSYNC0,   13);    // Tvfp       VS front porch        Min 1      typ  13    Max    255
    GD.wr32(REG_VSYNC1,    3);   //  Tvpw       VS pulse width        Min 3      typ   3    Max    255

    GD.wr32(REG_PCLK,      2);   //       
	GD.wr32(REG_SWIZZLE,   0);   //        
	GD.wr32(REG_PCLK_POL,  1);   //  
	GD.wr32(REG_CSPREAD,   0);   // 
	GD.wr32(REG_DITHER,    1);   //
	
	
//	  cmd_setrotate(ORIENTACION);
//    GD.wr32(REG_HCYCLE, 1056);//1056    // 900 //548
//    GD.wr32(REG_HOFFSET,  46);//88     // 46
//    GD.wr32(REG_HSIZE,   800);//800
//    GD.wr32(REG_HSYNC0,    0);//0
//    GD.wr32(REG_HSYNC1,   10);//10      // 41
    
// 	  GD.wr32(REG_VCYCLE,  525);//525     // 500
//    GD.wr32(REG_VOFFSET,  23);//32     // 23
//    GD.wr32(REG_VSIZE,   480);//480
//    GD.wr32(REG_VSYNC0,    0);//0
//    GD.wr32(REG_VSYNC1,   10);//10
	
//    GD.wr32(REG_PCLK,      2);//2
//	  GD.wr32(REG_SWIZZLE,   0);//0  //3 for GD2
//    GD.wr32(REG_PCLK_POL,  0);//0
//    GD.wr32(REG_CSPREAD,   0);//0
//    GD.wr32(REG_DITHER,    1);//1 	
	
  }


//TFT Riverdi FT813 7"
if (SizeEVE==71)
  {
	cmd_setrotate(ORIENTACION);
	GD.wr32(REG_HSIZE,   800);
	GD.wr32(REG_HCYCLE, 1056);//1000
	GD.wr32(REG_HOFFSET,  46);
	GD.wr32(REG_HSYNC0,    0);
	GD.wr32(REG_HSYNC1,   10); //41
	
     GD.wr32(REG_VSIZE,  480);
     GD.wr32(REG_VCYCLE, 525);
	GD.wr32(REG_VOFFSET,  23);
	GD.wr32(REG_VSYNC0,    0);
	GD.wr32(REG_VSYNC1,   10);
	
	GD.wr32(REG_SWIZZLE,   0);//3 for GD2
	
     GD.wr32(REG_PCLK,     2);//5
     GD.wr32(REG_PCLK_POL, 1);//1
	GD.wr32(REG_CSPREAD,   0);
	GD.wr32(REG_DITHER,    0);
  }


//TFT NHD FT813 7"
if (SizeEVE==7)
  {
	cmd_setrotate(ORIENTACION);
    GD.wr32(REG_HCYCLE, 1056);    
    GD.wr32(REG_HOFFSET,  46);     
    GD.wr32(REG_HSIZE,   800);
    GD.wr32(REG_HSYNC0,    0);
    GD.wr32(REG_HSYNC1,   10);      
    GD.wr32(REG_VCYCLE,  525);     
    GD.wr32(REG_VOFFSET,  23);     
    GD.wr32(REG_VSIZE,   480);
    GD.wr32(REG_VSYNC0,    0);
    GD.wr32(REG_VSYNC1,   10);

    GD.wr32(REG_PCLK,      2);
    GD.wr32(REG_PCLK_POL,  0);
    GD.wr32(REG_CSPREAD,   0);      
    GD.wr32(REG_DITHER,    1);      
	
//	cmd_setrotate(ORIENTACION);
//    GD.wr32(REG_HCYCLE,  928);//1056    // 900 //548
//    GD.wr32(REG_HOFFSET,  88);//88     // 46
//    GD.wr32(REG_HSIZE,   800);//800
//    GD.wr32(REG_HSYNC0,    0);//0
//    GD.wr32(REG_HSYNC1,   48);//10      // 41
    
//	GD.wr32(REG_VCYCLE,  525);//525     // 500
//    GD.wr32(REG_VOFFSET,  32);//32     // 23
//    GD.wr32(REG_VSIZE,   480);//480
//    GD.wr32(REG_VSYNC0,    0);//0
//    GD.wr32(REG_VSYNC1,    3);//10
	
//    GD.wr32(REG_PCLK,      2);//2
//	GD.wr32(REG_SWIZZLE,   0);//0  //3 for GD2
//    GD.wr32(REG_PCLK_POL,  0);//0
//    GD.wr32(REG_CSPREAD,   1);//0
//    GD.wr32(REG_DITHER,    1);//1     
  }

//TFT NHD FT813   4.3"
if (SizeEVE==43)
  {
	cmd_setrotate(ORIENTACION);
	GD.wr32(REG_HSIZE,  480);//480
	GD.wr32(REG_HCYCLE, 548);//548
	GD.wr32(REG_HOFFSET, 43);//43
	GD.wr32(REG_HSYNC0,   0);//0
	GD.wr32(REG_HSYNC1,  41);//41

	GD.wr32(REG_VSIZE,  272);//272
	GD.wr32(REG_VCYCLE, 292);//292
	GD.wr32(REG_VOFFSET, 12);//12
	GD.wr32(REG_VSYNC0,   0);//0
	GD.wr32(REG_VSYNC1,  10);//10

	GD.wr32(REG_PCLK,     5);//5
	if (GameduinoX==0)
     {
 	    GD.wr32(REG_SWIZZLE,  0);//0  NHD43    //3 for GD3
	 }
	if (GameduinoX==1)
     {
 	    GD.wr32(REG_SWIZZLE,  3);//0  NHD43    //3 for GD3
	 }	 
	 
	GD.wr32(REG_PCLK_POL, 1);//1
	GD.wr32(REG_CSPREAD,  1);//1
	GD.wr32(REG_DITHER,   1);//1
	//GD.wr(REG_ROTATE, 0);
  }


//TFT MO EVE3x-43    4.3"   BT815/GT911
if (SizeEVE==431)
  {
	cmd_setrotate(ORIENTACION);
	GD.wr32(REG_HSIZE,  480);
    GD.wr32(REG_VSIZE,  272);
	GD.wr32(REG_HCYCLE, 548);
	GD.wr32(REG_HOFFSET, 43);
	GD.wr32(REG_HSYNC0,   0);
	GD.wr32(REG_HSYNC1,  41);
	GD.wr32(REG_VCYCLE, 292);
	GD.wr32(REG_VOFFSET, 12);
	GD.wr32(REG_VSYNC0,   0);
	GD.wr32(REG_VSYNC1,  10);
	GD.wr32(REG_PCLK,     5);
	GD.wr32(REG_SWIZZLE,  0);
	GD.wr32(REG_PCLK_POL, 1);
	GD.wr32(REG_CSPREAD,  1);
	GD.wr32(REG_DITHER,   1);
	GD.wr16(REG_TOUCH_CONFIG, 0x05d0);
  }
//TFT MO EVE3x-43    4.3"   BT815/GT911

//TFT MO FT813 5"   GT911
if (SizeEVE==52){
	cmd_setrotate(ORIENTACION);
   GD.wr32(REG_HSIZE,       800);
    GD.wr32(REG_VSIZE,      480);

    GD.wr32(REG_HCYCLE,     928);
    GD.wr32(REG_HOFFSET,     88);
    GD.wr32(REG_HSYNC0,       0);
    GD.wr32(REG_HSYNC1,      48); 

    GD.wr32(REG_VCYCLE,     525);
    GD.wr32(REG_VOFFSET,     32);
    GD.wr32(REG_VSYNC0,       0);
    GD.wr32(REG_VSYNC1,       3);

    GD.wr32(REG_PCLK,         2);
    //GD.wr32(REG_SWIZZLE, 0);
    GD.wr32(REG_PCLK_POL,     1);
    GD.wr32(REG_CSPREAD,      0);
    GD.wr32(REG_DITHER,       1);
    GD.wr16(REG_TOUCH_CONFIG, 0x05d0);
}
//TFT MO FT813 5"   GT911

//TFT MO FT813  3.8"
if (SizeEVE==38)
  {
	cmd_setrotate(ORIENTACION);
	GD.wr32(REG_HSIZE,  480);   //480
     GD.wr32(REG_VSIZE, 272);   //272
	GD.wr32(REG_HCYCLE, 595);   //548   595
	GD.wr32(REG_HOFFSET, 43);   //43    
	GD.wr32(REG_HSYNC0,  35);   //0      35
	GD.wr32(REG_HSYNC1, 101);   //41    101

	
	GD.wr32(REG_VCYCLE, 294);   //292     294
	GD.wr32(REG_VOFFSET, 12);   //12
	GD.wr32(REG_VSYNC0, 152);   //152
	GD.wr32(REG_VSYNC1,  10);   //10

	GD.wr32(REG_PCLK,     5);   //5
	GD.wr32(REG_SWIZZLE,  0);   //0, 3 for GD2
	GD.wr32(REG_PCLK_POL, 1);   //1
	GD.wr32(REG_CSPREAD,  1);   //1
	GD.wr32(REG_DITHER,   1);   //1 
	//GD.wr(REG_ROTATE, 0);
  }


if (SizeEVE==5)
  {

	//cmd_setrotate(ORIENTACION);
    //GD.wr32(REG_HCYCLE, 1056);    
    //GD.wr32(REG_HOFFSET,  46);     
    //GD.wr32(REG_HSIZE,   800);
    //GD.wr32(REG_HSYNC0,    0);
    //GD.wr32(REG_HSYNC1,   10);      
    //GD.wr32(REG_VCYCLE,  525);     
    //GD.wr32(REG_VOFFSET,  23);     
    //GD.wr32(REG_VSIZE,   480);
    //GD.wr32(REG_VSYNC0,    0);
    //GD.wr32(REG_VSYNC1,   10);

    //GD.wr32(REG_PCLK,      2);
    //GD.wr32(REG_PCLK_POL,  0);
    //GD.wr32(REG_CSPREAD,   0);      
    //GD.wr32(REG_DITHER,    1);      
	
	cmd_setrotate(ORIENTACION);
    GD.wr32(REG_HSIZE,    800);//
	GD.wr32(REG_HCYCLE,  1056);// with 928 = artifacs in sprite example   https://newhavendisplay.com/content/specs/NHD-5.0-800480FT-CSXP-CTP.pdf  or  https://support.newhavendisplay.com/hc/en-us/article_attachments/27151786567319
    GD.wr32(REG_HOFFSET,   10);//    88
    GD.wr32(REG_HSYNC0,     0);//
    GD.wr32(REG_HSYNC1,    48);//
    
	GD.wr32(REG_VSIZE,   480);//
	GD.wr32(REG_VCYCLE,  525);//
    GD.wr32(REG_VOFFSET,  10);//            32
    GD.wr32(REG_VSYNC0,    0);//
    GD.wr32(REG_VSYNC1,    3);//
	
    GD.wr32(REG_PCLK,      2);//2
	GD.wr32(REG_SWIZZLE,   0);//0  //3 for GD2
    GD.wr32(REG_PCLK_POL,  0);//0
    GD.wr32(REG_CSPREAD,   0);//0
    GD.wr32(REG_DITHER,    1);//1     
	
	//GD.wr32(REG_HSIZE,   800);//
    //GD.wr32(REG_HCYCLE, 1056);//
    //GD.wr32(REG_HOFFSET,  46);//
    //GD.wr32(REG_HSYNC0,    0);//
    //GD.wr32(REG_HSYNC1,   10);//
    
	//GD.wr32(REG_VSIZE,   480);//
	//GD.wr32(REG_VCYCLE,  525);//
    //GD.wr32(REG_VOFFSET,  23);//
    //GD.wr32(REG_VSYNC0,    0);//
    //GD.wr32(REG_VSYNC1,   10);//
	
    //GD.wr32(REG_PCLK,      2);//2
	//GD.wr32(REG_SWIZZLE,   0);//0  //3 for GD2
    //GD.wr32(REG_PCLK_POL,  0);//0
    //GD.wr32(REG_CSPREAD,   0);//0
    //GD.wr32(REG_DITHER,    1);//1     	
	
  }

  }

  GD.finish();
  w = GDTR.rd16(REG_HSIZE);
  h = GDTR.rd16(REG_VSIZE);
  loadptr = 0;

  // Work-around issue with bitmap sizes not being reset
  for (byte i = 0; i < 32; i++) {
    BitmapHandle(i);
    cI(0x28000000UL);
    cI(0x29000000UL);
  }

  Clear(); swap();
  Clear(); swap();
  Clear(); swap();
  cmd_regwrite(REG_PWM_DUTY, 128);
  flush();

//#if (EVETFTonTeensyX==1)
#ifdef TEENSYDUINO
 if (NHDTouch==1)
 {  	  	
  if ((EEPROM.read(0) == 0)) 
   {
      self_calibrate();
      for (int i = 0; i < 24; i++)
        {
         EEPROM.write(1 + i, GDTR.rd(REG_TOUCH_TRANSFORM_A + i));
        }
      EEPROM.write(0, 0x1);
    } else {
      for (int i = 0; i < 24; i++)
        {
         GDTR.wr(REG_TOUCH_TRANSFORM_A + i, EEPROM.read(1 + i));
        }
           }	
  }
#endif


#if defined(ARDUINO_ARCH_RP2040)
 EEPROM.begin(512);   //eeprom emulada en FLASH
 if (NHDTouch==1)
 {  	  	
  if (EEPROM.read(0) == 0) 
   {
      self_calibrate();
      for (int i = 0; i < 24; i++)
        {
         EEPROM.write(1 + i, GDTR.rd(REG_TOUCH_TRANSFORM_A + i));
        }
      EEPROM.write(0, 1);
	  EEPROM.commit();       //finaliza y guarda cambios en flash
    } else {
      for (int i = 0; i < 24; i++)
        {
         GDTR.wr(REG_TOUCH_TRANSFORM_A + i, EEPROM.read(1 + i));
        }
           }	
  }
#endif


#if defined(ARDUINO_ARCH_STM32)
 if (NHDTouch==1)
 {
 AT24Cxx eep(i2c_address, 63);
 if (eep.read(0) == 0) {
 self_calibrate();
      for (int i = 0; i < 24; i++) 
      {eep.write(1 + i, GDTR.rd(REG_TOUCH_TRANSFORM_A + i));
      }
      eep.write(0, 0x1);  
    } else {
           for (int i = 0; i < 24; i++)
           {
           GDTR.wr(REG_TOUCH_TRANSFORM_A + i, eep.read(1 + i));
           }
    }
 }
#endif


#if defined(ARDUINO_UNOR4_MINIMA)
 if (NHDTouch==1)
 {  	  	
  if ((EEPROM.read(0) == 0)) 
   {
      self_calibrate();
      for (int i = 0; i < 24; i++)
        {
         EEPROM.write(1 + i, GDTR.rd(REG_TOUCH_TRANSFORM_A + i));
        }
      EEPROM.write(0, 0x1);
    } else {
      for (int i = 0; i < 24; i++)
        {
         GDTR.wr(REG_TOUCH_TRANSFORM_A + i, EEPROM.read(1 + i));
        }
           }	
  }
#endif



  GDTR.wr16(REG_TOUCH_RZTHRESH, 1200);

  rseed = 0x77777777;
  cprim = 0xff;
  vxf = 4;

 tune();
   
 cmd_dlstart();
  ClearColorRGB(0x005500);
  Clear();

   if(SizeEVE==54)
   {
	 ClearColorRGB(0x000055);
     Clear();
	 //cmd_logo();     //si funciona XD pero impide inicio de sketch
	 //cmd_testcard(); //si funciona XD pero impide inicio de sketch
	 cmd_text(w / 2, (h / 2)-32, 30, OPT_CENTER, "EVE4 on line");
	 cmd_text(w / 2, h / 2, 30, OPT_CENTER, "FT81XMania.com");
	 delay(2500);
	 swap();
   }
   else
   {
	   
   if(SizeEVE==434)
   {
	 ClearColorRGB(0x000055);
     Clear();
	 //cmd_logo();     //si funciona XD pero impide inicio de sketch
	 //cmd_testcard(); //si funciona XD pero impide inicio de sketch
	 cmd_text(w / 2, (h / 2)-32, 30, OPT_CENTER, "EVE4 on line");
	 cmd_text(w / 2, h / 2, 30, OPT_CENTER, "FT81XMania.com");
	 delay(2500);
	 swap();
   }
   else   
   {   
	 ClearColorRGB(0x005500);
     Clear();	   
	 cmd_text(w / 2, (h / 2)-32, 30, OPT_CENTER, "EVE-1/2/3/4 on line");
	 cmd_text(w / 2, h / 2, 30, OPT_CENTER, "FT81XMania.com");
     //cmd_spinner(w / 2, (h / 2)+ 0.1*h, 1, 0);  //falla en BT817
	 delay(500);
	 swap();
   }
   }
    
  End();
  
  finish();
}


void GDClass::self_calibrate(void) {
   
  if (BT8XX==1)
 {
  //Serial.print("FT80");  Serial.println(BT8XX, HEX); //Serial.println(BT8XX, HEX);
  GDTR.wr(REG_ROTATE, ROTACION);
  //Serial.println(ROTACION);
 }
 
 if (BT8XX==19)
 {
  //Serial.print("FT8");  Serial.println(BT8XX, HEX); //Serial.println(BT8XX, HEX);
  cmd_setrotate(ORIENTACION);
  //Serial.println(ORIENTACION);
 }
 
 if (BT8XX>19)
 {
  //Serial.print("BT8");  Serial.println(BT8XX, HEX); //Serial.println(BT8XX, HEX);
  cmd_setrotate(ORIENTACION);
  //Serial.println(ORIENTACION);
 } 
  
  
	
  #define RAM_TP1 0
    static const unsigned char PROGMEM Tp1[] = 
  {
    #include "Tp1.h"
  };

	
  cmd_dlstart();
  
  GD.cmd_inflate(RAM_TP1);
  //GD.cmd_memwrite(RAM_TP1);
  GD.copy(Tp1, sizeof(Tp1));
  GD.BitmapHandle(0);
  GD.BitmapSource(0);
  GD.BitmapLayout(ARGB1555, 170, 122);
  GD.BitmapSize(NEAREST, BORDER, BORDER, 85, 122); 
 
  ClearColorRGB(0x350035);
  Clear();
  
  GD.Begin(BITMAPS);
  ColorRGB(255,255,0);  
  GD.ColorA(85);
   GD.Vertex2ii((GD.w / 2)-50, (GD.h / 2)-50, 0, 0);
  GD.ColorA(255);
  ColorRGB(255,255,255);  

  cmd_text(GD.w / 2, GD.h / 2, 29, OPT_CENTERX, "please tap on the dot");

  cmd_bgcolor(0x0000ff);
  cmd_fgcolor(0x00ff00);  
  
  
  cmd_calibrate();
  finish();
  cmd_loadidentity();
  cmd_dlstart();
  GDTR.flush();  
  
  
 // cmd_dlstart();
 // Clear();
 // cmd_text(w / 2, h / 2, 30, OPT_CENTER, "please tap on the dot");
 // cmd_calibrate();
 // finish();
 // cmd_loadidentity();
 // cmd_dlstart();
 // GDTR.flush();

}

void GDClass::seed(uint16_t n) {
  rseed = n ? n : 7;
}

uint16_t GDClass::random() {
  rseed ^= rseed << 2;
  rseed ^= rseed >> 5;
  rseed ^= rseed << 1;
  return rseed;
}

uint16_t GDClass::random(uint16_t n) {
  uint16_t p = random();
  if (n == (n & -n))
    return p & (n - 1);
  return (uint32_t(p) * n) >> 16;
}

uint16_t GDClass::random(uint16_t n0, uint16_t n1) {
  return n0 + random(n1 - n0);
}

// >>> [int(65535*math.sin(math.pi * 2 * i / 1024)) for i in range(257)]
static const PROGMEM uint16_t sintab[257] = {
0, 402, 804, 1206, 1608, 2010, 2412, 2813, 3215, 3617, 4018, 4419, 4821, 5221, 5622, 6023, 6423, 6823, 7223, 7622, 8022, 8421, 8819, 9218, 9615, 10013, 10410, 10807, 11203, 11599, 11995, 12390, 12785, 13179, 13573, 13966, 14358, 14750, 15142, 15533, 15923, 16313, 16702, 17091, 17479, 17866, 18252, 18638, 19023, 19408, 19791, 20174, 20557, 20938, 21319, 21699, 22078, 22456, 22833, 23210, 23585, 23960, 24334, 24707, 25079, 25450, 25820, 26189, 26557, 26924, 27290, 27655, 28019, 28382, 28744, 29105, 29465, 29823, 30181, 30537, 30892, 31247, 31599, 31951, 32302, 32651, 32999, 33346, 33691, 34035, 34378, 34720, 35061, 35400, 35737, 36074, 36409, 36742, 37075, 37406, 37735, 38063, 38390, 38715, 39039, 39361, 39682, 40001, 40319, 40635, 40950, 41263, 41574, 41885, 42193, 42500, 42805, 43109, 43411, 43711, 44010, 44307, 44603, 44896, 45189, 45479, 45768, 46055, 46340, 46623, 46905, 47185, 47463, 47739, 48014, 48287, 48558, 48827, 49094, 49360, 49623, 49885, 50145, 50403, 50659, 50913, 51165, 51415, 51664, 51910, 52155, 52397, 52638, 52876, 53113, 53347, 53580, 53810, 54039, 54265, 54490, 54712, 54933, 55151, 55367, 55581, 55793, 56003, 56211, 56416, 56620, 56821, 57021, 57218, 57413, 57606, 57796, 57985, 58171, 58355, 58537, 58717, 58894, 59069, 59242, 59413, 59582, 59748, 59912, 60074, 60234, 60391, 60546, 60699, 60849, 60997, 61143, 61287, 61428, 61567, 61704, 61838, 61970, 62100, 62227, 62352, 62474, 62595, 62713, 62828, 62941, 63052, 63161, 63267, 63370, 63472, 63570, 63667, 63761, 63853, 63942, 64029, 64114, 64196, 64275, 64353, 64427, 64500, 64570, 64637, 64702, 64765, 64825, 64883, 64938, 64991, 65042, 65090, 65135, 65178, 65219, 65257, 65293, 65326, 65357, 65385, 65411, 65435, 65456, 65474, 65490, 65504, 65515, 65523, 65530, 65533, 65535
};

int16_t GDClass::rsin(int16_t r, uint16_t th) {
  th >>= 6; // angle 0-1023
  // return int(r * sin((2 * M_PI) * th / 1024.));
  int th4 = th & 511;
  if (th4 & 256)
    th4 = 512 - th4; // 256->256 257->255, etc
  uint16_t s = pgm_read_word_near(sintab + th4);
  int16_t p = ((uint32_t)s * r) >> 16;
  if (th & 512)
    p = -p;
  return p;
}

int16_t GDClass::rcos(int16_t r, uint16_t th) {
  return rsin(r, th + 0x4000);
}

void GDClass::polar(int &x, int &y, int16_t r, uint16_t th) {
  x = (int)(-GD.rsin(r, th));
  y = (int)( GD.rcos(r, th));
}

// >>> [int(round(1024 * math.atan(i / 256.) / math.pi)) for i in range(256)]
static const PROGMEM uint8_t atan8[] = {
0,1,3,4,5,6,8,9,10,11,13,14,15,17,18,19,20,22,23,24,25,27,28,29,30,32,33,34,36,37,38,39,41,42,43,44,46,47,48,49,51,52,53,54,55,57,58,59,60,62,63,64,65,67,68,69,70,71,73,74,75,76,77,79,80,81,82,83,85,86,87,88,89,91,92,93,94,95,96,98,99,100,101,102,103,104,106,107,108,109,110,111,112,114,115,116,117,118,119,120,121,122,124,125,126,127,128,129,130,131,132,133,134,135,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,177,178,179,180,181,182,183,184,185,186,187,188,188,189,190,191,192,193,194,195,195,196,197,198,199,200,201,201,202,203,204,205,206,206,207,208,209,210,211,211,212,213,214,215,215,216,217,218,219,219,220,221,222,222,223,224,225,225,226,227,228,228,229,230,231,231,232,233,234,234,235,236,236,237,238,239,239,240,241,241,242,243,243,244,245,245,246,247,248,248,249,250,250,251,251,252,253,253,254,255,255
};

uint16_t GDClass::atan2(int16_t y, int16_t x)
{
  uint16_t a;
  uint16_t xx = 0;

  /* These values are tricky. So pretend they are not */
  if (x == -32768)
    x++;
  if (y == -32768)
    y++;

  if ((x <= 0) ^ (y > 0)) {
    int16_t t; t = x; x = y; y = t;
    xx ^= 0x4000;
  }
  if (x <= 0) {
    x = -x;
  } else {
    xx ^= 0x8000;
  }
  y = abs(y);
  if (x > y) {
    int16_t t; t = x; x = y; y = t;
    xx ^= 0x3fff;
  }
  while ((x | y) & 0xff80) {
    x >>= 1;
    y >>= 1;
  }
  if (y == 0) {
    a = 0;
  } else if (x == y) {
    a = 0x2000;
  } else {
    // assert(x <= y);
    int r = ((x << 8) / y);
    // assert(0 <= r);
    // assert(r < 256);
    a = pgm_read_byte(atan8 + r) << 5;
  }
  a ^= xx;
  return a;
}

void GDClass::align(byte n) {
  while ((n++) & 3)
    GDTR.cmdbyte(0);
}

void GDClass::cH(uint16_t v) {
  GDTR.cmdbyte(v & 0xff);
  GDTR.cmdbyte((v >> 8) & 0xff);
}

void GDClass::ch(int16_t v) {
  cH((uint16_t)v);
}

void GDClass::cI(uint32_t v) {
  GDTR.cmd32(v);
}

void GDClass::cFFFFFF(byte v) {
  union {
    uint32_t c;
    uint8_t b[4];
  };
  b[0] = v;
  b[1] = 0xff;
  b[2] = 0xff;
  b[3] = 0xff;
  GDTR.cmd32(c);
}

void GDClass::ci(int32_t v) {
  cI((uint32_t) v);
}

void GDClass::cs(const char *s) {
  int count = 0;
  while (*s) {
    char c = *s++;
    GDTR.cmdbyte(c);
    count++;
  }
  GDTR.cmdbyte(0);
  align(count + 1);
}

#if !defined(TEENSYDUINO)
void GDClass::copy(const uint8_t *src, int count) {
#else
void GDClass::copy(const uint8_t *src, int count) {
#endif
  byte a = count & 3;
  while (count--) {
    GDTR.cmdbyte(pgm_read_byte_near(src));
    src++;
  }
  align(a);
}

void GDClass::copyram(byte *src, int count) {
  byte a = count & 3;
  GDTR.cmd_n(src, count);
  align(a);
}

void GDClass::AlphaFunc(byte func, byte ref) {
  cI((9UL << 24) | ((func & 7L) << 8) | ((ref & 255L) << 0));
}
void GDClass::Begin(Primitive prim) {
  // if (prim != cprim) {
    cI((31UL << 24) | int(prim));
    cprim = prim;
  // }
}
void GDClass::BitmapHandle(byte handle) {
  cI((5UL << 24) | handle);
}
void GDClass::BitmapLayout(byte format, uint16_t linestride, uint16_t height) {
  // cI((7UL << 24) | ((format & 31L) << 19) | ((linestride & 1023L) << 9) | ((height & 511L) << 0));
  union {
    uint32_t c;
    uint8_t b[4];
  };
  b[0] = height;
  b[1] = (1 & (height >> 8)) | (linestride << 1);
  b[2] = (7 & (linestride >> 7)) | (format << 3);
  b[3] = 7;
  cI(c);
  if (ft8xx_model) {
    b[0] = (((linestride >> 10) & 3) << 2) | ((height >> 9) & 3);
    b[3] = 0x28;
    cI(c);
  }
}
void GDClass::BitmapSize(byte filter, byte wrapx, byte wrapy, uint16_t width, uint16_t height) {
  byte fxy = (filter << 2) | (wrapx << 1) | (wrapy);
  // cI((8UL << 24) | ((uint32_t)fxy << 18) | ((width & 511L) << 9) | ((height & 511L) << 0));
  union {
    uint32_t c;
    uint8_t b[4];
  };
  b[0] = height;
  b[1] = (1 & (height >> 8)) | (width << 1);
  b[2] = (3 & (width >> 7)) | (fxy << 2);
  b[3] = 8;
  cI(c);
  if (ft8xx_model) {
    b[0] = ((width >> 9) << 2) | (3 & (height >> 9));
    b[3] = 0x29;
    cI(c);
  }
}
void GDClass::BitmapSource(uint32_t addr) {
  cI((1UL << 24) | ((addr & 0xffffffL) << 0));
}
void GDClass::BitmapTransformA(int32_t a) {
  cI((21UL << 24) | ((a & 131071L) << 0));
}
void GDClass::BitmapTransformB(int32_t b) {
  cI((22UL << 24) | ((b & 131071L) << 0));
}
void GDClass::BitmapTransformC(int32_t c) {
  cI((23UL << 24) | ((c & 16777215L) << 0));
}
void GDClass::BitmapTransformD(int32_t d) {
  cI((24UL << 24) | ((d & 131071L) << 0));
}
void GDClass::BitmapTransformE(int32_t e) {
  cI((25UL << 24) | ((e & 131071L) << 0));
}
void GDClass::BitmapTransformF(int32_t f) {
  cI((26UL << 24) | ((f & 16777215L) << 0));
}
void GDClass::BlendFunc(byte src, byte dst) {
  cI((11UL << 24) | ((src & 7L) << 3) | ((dst & 7L) << 0));
}
void GDClass::Call(uint16_t dest) {
  cI((29UL << 24) | ((dest & 2047L) << 0));
}
void GDClass::Cell(byte cell) {
  cI((6UL << 24) | ((cell & 127L) << 0));
}
void GDClass::ClearColorA(byte alpha) {
  cI((15UL << 24) | ((alpha & 255L) << 0));
}
void GDClass::ClearColorRGB(byte red, byte green, byte blue) {
  cI((2UL << 24) | ((red & 255L) << 16) | ((green & 255L) << 8) | ((blue & 255L) << 0));
}
void GDClass::ClearColorRGB(uint32_t rgb) {
  cI((2UL << 24) | (rgb & 0xffffffL));
}
void GDClass::Clear(byte c, byte s, byte t) {
  byte m = (c << 2) | (s << 1) | t;
  cI((38UL << 24) | m);
}
void GDClass::Clear(void) {
  cI((38UL << 24) | 7);
}
void GDClass::ClearStencil(byte s) {
  cI((17UL << 24) | ((s & 255L) << 0));
}
void GDClass::ClearTag(byte s) {
  cI((18UL << 24) | ((s & 255L) << 0));
}
void GDClass::ColorA(byte alpha) {
  cI((16UL << 24) | ((alpha & 255L) << 0));
}
void GDClass::ColorMask(byte r, byte g, byte b, byte a) {
  cI((32UL << 24) | ((r & 1L) << 3) | ((g & 1L) << 2) | ((b & 1L) << 1) | ((a & 1L) << 0));
}
void GDClass::ColorRGB(byte red, byte green, byte blue) {
  // cI((4UL << 24) | ((red & 255L) << 16) | ((green & 255L) << 8) | ((blue & 255L) << 0));
  union {
    uint32_t c;
    uint8_t b[4];
  };
  b[0] = blue;
  b[1] = green;
  b[2] = red;
  b[3] = 4;
  cI(c);
}
void GDClass::ColorRGB(uint32_t rgb) {
  cI((4UL << 24) | (rgb & 0xffffffL));
}
void GDClass::Display(void) {
  cI((0UL << 24));
}
void GDClass::End(void) {
  cI((33UL << 24));
}
void GDClass::Jump(uint16_t dest) {
  cI((30UL << 24) | ((dest & 2047L) << 0));
}
void GDClass::LineWidth(uint16_t width) {
  cI((14UL << 24) | ((width & 4095L) << 0));
}
void GDClass::Macro(byte m) {
  cI((37UL << 24) | ((m & 1L) << 0));
}
void GDClass::PointSize(uint16_t size) {
  cI((13UL << 24) | ((size & 8191L) << 0));
}
void GDClass::RestoreContext(void) {
  cI((35UL << 24));
}
void GDClass::Return(void) {
  cI((36UL << 24));
}
void GDClass::SaveContext(void) {
  cI((34UL << 24));
}
void GDClass::ScissorSize(uint16_t width, uint16_t height) {
  if (ft8xx_model == 0)
    cI((28UL << 24) | ((width & 1023L) << 10) | ((height & 1023L) << 0));
  else
    cI((28UL << 24) | ((width & 4095L) << 12) | ((height & 4095L) << 0));
}
void GDClass::ScissorXY(uint16_t x, uint16_t y) {
  if (ft8xx_model == 0)
    cI((27UL << 24) | ((x & 511L) << 9) | ((y & 511L) << 0));
  else
    cI((27UL << 24) | ((x & 2047L) << 11) | ((y & 2047L) << 0));
}
void GDClass::StencilFunc(byte func, byte ref, byte mask) {
  cI((10UL << 24) | ((func & 7L) << 16) | ((ref & 255L) << 8) | ((mask & 255L) << 0));
}
void GDClass::StencilMask(byte mask) {
  cI((19UL << 24) | ((mask & 255L) << 0));
}
void GDClass::StencilOp(byte sfail, byte spass) {
  cI((12UL << 24) | ((sfail & 7L) << 3) | ((spass & 7L) << 0));
}
void GDClass::TagMask(byte mask) {
  cI((20UL << 24) | ((mask & 1L) << 0));
}
void GDClass::Tag(byte s) {
  cI((3UL << 24) | ((s & 255L) << 0));
}
void GDClass::Vertex2f(int16_t x, int16_t y) {
  // x = int(16 * x);
  // y = int(16 * y);
  cI((1UL << 30) | ((x & 32767L) << 15) | ((y & 32767L) << 0));
}
void GDClass::Vertex2ii(uint16_t x, uint16_t y, byte handle, byte cell) {
  // cI((2UL << 30) | ((x & 511L) << 21) | ((y & 511L) << 12) | ((handle & 31L) << 7) | ((cell & 127L) << 0));
  union {
    uint32_t c;
    uint8_t b[4];
  };
  b[0] = (cell & 127) | ((handle & 1) << 7);
  b[1] = (handle >> 1) | (y << 4);
  b[2] = (y >> 4) | (x << 5);
  b[3] = (2 << 6) | (x >> 3);
  cI(c);
}
void GDClass::VertexFormat(byte frac) {
  cI((39UL << 24) | (((frac) & 7) << 0));
  vxf = frac;
}
void GDClass::BitmapLayoutH(byte linestride, byte height) {
  cI((40UL << 24) | (((linestride) & 3) << 2) | (((height) & 3) << 0));
}
void GDClass::BitmapSizeH(byte width, byte height) {
  cI((41UL << 24) | (((width) & 3) << 2) | (((height) & 3) << 0));
}
void GDClass::PaletteSource(uint32_t addr) {
  cI((42UL << 24) | (((addr) & 4194303UL) << 0));
}
void GDClass::VertexTranslateX(uint32_t x) {
  cI((43UL << 24) | (((x) & 131071UL) << 0));
}
void GDClass::VertexTranslateY(uint32_t y) {
  cI((44UL << 24) | (((y) & 131071UL) << 0));
}
void GDClass::Nop(void) {
  cI((45UL << 24));
}
void GDClass::BitmapExtFormat(uint16_t format) {
  cI((46UL << 24)|(((format) & 65535UL) << 0));
}
void GDClass::BitmapSwizzle(byte r, byte g, byte b, byte a) {
  cI((47UL << 24)|(((r) & 7UL) << 9)|(((g) & 7UL) << 6)|(((b) & 7UL) << 3)|(((a) & 7UL) << 0));
}

void GDClass::cmd_append(uint32_t ptr, uint32_t num) {
  cFFFFFF(0x1e);
  cI(ptr);
  cI(num);
  cprim = 0xff;
}
void GDClass::cmd_bgcolor(uint32_t c) {
  cFFFFFF(0x09);
  cI(c);
}
void GDClass::cmd_button(int16_t x, int16_t y, uint16_t w, uint16_t h, byte font, uint16_t options, const char *s) {
  cFFFFFF(0x0d);
  ch(x);
  ch(y);
  ch(w);
  ch(h);
  ch(font);
  cH(options);
  cs(s);
  cprim = 0xff;
}
void GDClass::cmd_calibrate(void) {
  cFFFFFF(0x15);
  cFFFFFF(0xff);
}
void GDClass::cmd_clock(int16_t x, int16_t y, int16_t r, uint16_t options, uint16_t h, uint16_t m, uint16_t s, uint16_t ms) {
  cFFFFFF(0x14);
  ch(x);
  ch(y);
  ch(r);
  cH(options);
  cH(h);
  cH(m);
  cH(s);
  cH(ms);
  cprim = 0xff;
}
void GDClass::cmd_coldstart(void) {
  cFFFFFF(0x32);
}
void GDClass::cmd_dial(int16_t x, int16_t y, int16_t r, uint16_t options, uint16_t val) {
  cFFFFFF(0x2d);
  ch(x);
  ch(y);
  ch(r);
  cH(options);
  cH(val);
  cH(0);
  cprim = 0xff;
}
void GDClass::cmd_dlstart(void) {
  cFFFFFF(0x00);
  cprim = 0xff;
  vxf = 4;
}
void GDClass::cmd_fgcolor(uint32_t c) {
  cFFFFFF(0x0a);
  cI(c);
}
void GDClass::cmd_gauge(int16_t x, int16_t y, int16_t r, uint16_t options, uint16_t major, uint16_t minor, uint16_t val, uint16_t range) {
  cFFFFFF(0x13);
  ch(x);
  ch(y);
  ch(r);
  cH(options);
  cH(major);
  cH(minor);
  cH(val);
  cH(range);
  cprim = 0xff;
}
void GDClass::cmd_getmatrix(void) {
  cFFFFFF(0x33);
  ci(0);
  ci(0);
  ci(0);
  ci(0);
  ci(0);
  ci(0);
}
void GDClass::cmd_getprops(uint32_t &ptr, uint32_t &w, uint32_t &h) {
  cFFFFFF(0x25);
  ptr = GDTR.getwp();
  cI(0);
  w = GDTR.getwp();
  cI(0);
  h = GDTR.getwp();
  cI(0);
}
void GDClass::cmd_getptr(void) {
  cFFFFFF(0x23);
  cI(0);
}
void GDClass::cmd_gradcolor(uint32_t c) {
  cFFFFFF(0x34);
  cI(c);
}
void GDClass::cmd_gradient(int16_t x0, int16_t y0, uint32_t rgb0, int16_t x1, int16_t y1, uint32_t rgb1) {
  cFFFFFF(0x0b);
  ch(x0);
  ch(y0);
  cI(rgb0);
  ch(x1);
  ch(y1);
  cI(rgb1);
  cprim = 0xff;
}
void GDClass::cmd_inflate(uint32_t ptr) {
  cFFFFFF(0x22);
  cI(ptr);
}
void GDClass::cmd_interrupt(uint32_t ms) {
  cFFFFFF(0x02);
  cI(ms);
}
void GDClass::cmd_keys(int16_t x, int16_t y, int16_t w, int16_t h, byte font, uint16_t options, const char*s) {
  cFFFFFF(0x0e);
  ch(x);
  ch(y);
  ch(w);
  ch(h);
  ch(font);
  cH(options);
  cs(s);
  cprim = 0xff;
}
void GDClass::cmd_loadidentity(void) {
  cFFFFFF(0x26);
}
void GDClass::cmd_loadimage(uint32_t ptr, int32_t options) {
  cFFFFFF(0x24);
  cI(ptr);
  cI(options);
}
void GDClass::cmd_memcpy(uint32_t dest, uint32_t src, uint32_t num) {
  cFFFFFF(0x1d);
  cI(dest);
  cI(src);
  cI(num);
}
void GDClass::cmd_memset(uint32_t ptr, byte value, uint32_t num) {
  cFFFFFF(0x1b);
  cI(ptr);
  cI((uint32_t)value);
  cI(num);
}
uint32_t GDClass::cmd_memcrc(uint32_t ptr, uint32_t num) {
  cFFFFFF(0x18);
  cI(ptr);
  cI(num);
  uint32_t r = GDTR.getwp();
  cI(0xFFFFFFFF);
  return r;
}
void GDClass::cmd_memwrite(uint32_t ptr, uint32_t num) {
  cFFFFFF(0x1a);
  cI(ptr);
  cI(num);
}
void GDClass::cmd_regwrite(uint32_t ptr, uint32_t val) {
  cFFFFFF(0x1a);
  cI(ptr);
  cI(4UL);
  cI(val);
}
void GDClass::cmd_number(int16_t x, int16_t y, byte font, uint16_t options, uint32_t n) {
  cFFFFFF(0x2e);
  ch(x);
  ch(y);
  ch(font);
  cH(options);
  ci(n);
  cprim = BITMAPS;
}


#if defined(ARDUINO_ARCH_STM32)
void GDClass::printNfloat(int16_t x, int16_t y, float f, int16_t Presc, byte font) {
 //Parte entera
 cmd_number(x - 2, y, font, OPT_RIGHTX | OPT_SIGNED, int(f));
 //Parte entera

 Presc = abs(Presc);
 
// Punto y parte decimal
if (Presc==1){
 cmd_text(  x,     y, font, 0, ".");
 cmd_number(x + 9, y, font, Presc, int(10 * abs(f))); // 1 decimal
 }  
if (Presc==2){
 cmd_text(  x,     y, font, 0, ".");
 cmd_number(x + 9, y, font, Presc, int(100 * abs(f))); // 2 decimales
 }
if (Presc==3){  
 cmd_text(  x,     y, font, 0, ".");
 cmd_number(x + 9, y, font, Presc, int(1000 * abs(f))); //3 decimales
 }
if (Presc==4){  
 cmd_text(  x,     y, font, 0, ".");
 cmd_number(x + 9, y, font, Presc, int(10000 * abs(f))); //4 decimales
 }
if (Presc==5){  
 cmd_text(  x,     y, font, 0, ".");
 cmd_number(x + 9, y, font, Presc, int(100000 * abs(f))); //5 decimales
 }
if (Presc==6){
 cmd_text(  x,     y, font, 0, ".");
 cmd_number(x + 9, y, font, Presc, int(1000000 * abs(f))); //6 decimales
 }
if (Presc==7){
 cmd_text(  x,     y, font, 0, ".");
 cmd_number(x + 9, y, font, Presc, int(10000000 * abs(f))); //7 decimales
 }
// Punto y parte decimal
}
#endif


#if defined(ARDUINO_ARCH_RP2040)
void GDClass::printNfloat(int16_t x, int16_t y, double f, int16_t Presc, byte font, uint16_t options)
{
   char doubleNumber[50];
   char bufNum[25];
   
   dtostrf(f, 3, Presc, bufNum);
   sprintf(doubleNumber,"%s", bufNum);
   cmd_text(x, y, font, options, doubleNumber);
   //cmd_text(x, y, font, 0, floatNumber);
   //cmd_text(x, y, font, OPT_RIGHTX, floatNumber);
   //cmd_text(x, y, font, OPT_CENTER, floatNumber);
}
#endif


#if defined(ARDUINO_UNOR4_MINIMA)
void GDClass::printNfloat(int16_t x, int16_t y, double f, int16_t Presc, byte font, uint16_t options)
{
   char doubleNumber[50];
   char bufNum[25];
   
   dtostrf(f, 3, Presc, bufNum);
   sprintf(doubleNumber,"%s", bufNum);
   cmd_text(x, y, font, options, doubleNumber);
   //cmd_text(x, y, font, 0, floatNumber);
   //cmd_text(x, y, font, OPT_RIGHTX, floatNumber);
   //cmd_text(x, y, font, OPT_CENTER, floatNumber);
}
#endif



#ifdef TEENSYDUINO
void GDClass::printNfloat(int16_t x, int16_t y, double f, int16_t Presc, byte font, uint16_t options)
{
   char doubleNumber[50];
   char bufNum[25];
   
   dtostrf(f, 3, Presc, bufNum);
   sprintf(doubleNumber,"%s", bufNum);
   cmd_text(x, y, font, options, doubleNumber);
   //cmd_text(x, y, font, 0, floatNumber);
   //cmd_text(x, y, font, OPT_RIGHTX, floatNumber);
   //cmd_text(x, y, font, OPT_CENTER, floatNumber);
}
#endif

void GDClass::Rect_Empty(int16_t xi, int16_t yi,int16_t xPX, int16_t yPX, int16_t RF, int16_t GF, int16_t BF)
{
  GD.SaveContext();
  GD.ColorRGB(RF, GF, BF);     //color de relleno
  int xf=xi+xPX;
  int yf=yi+yPX;
  GD.Begin(LINES); GD.LineWidth(0.5 * 16);
  GD.Vertex2f(xi*16, yi*16); GD.Vertex2f(xi*16, yf*16); //lado izquierdo
  GD.Vertex2f(xi*16, yi*16); GD.Vertex2f(xf*16, yi*16); //lado superior
  GD.Vertex2f(xf*16, yi*16); GD.Vertex2f(xf*16, yf*16); //lado derecho
  GD.Vertex2f(xi*16, yf*16); GD.Vertex2f(xf*16, yf*16); //lado inferior
  GD.RestoreContext();
  //GD.End();
}

void GDClass::Rect_Filled(int16_t xi, int16_t yi,int16_t xPX, int16_t yPX, int16_t RF, int16_t GF, int16_t BF)
{
 GD.SaveContext();
 int xf=xi+xPX;
 int yf=yi+yPX;
 GD.Begin(RECTS);
 //GD.LineWidth(2 * 16);        // corner radius 2 pixels
 //GD.Vertex2f(xi*16, yi*16);   //esquina inicial
 //GD.Vertex2f(xf*16, yf*16);   //esquina final

 GD.ColorRGB(RF, GF, BF);     //color de relleno
 GD.LineWidth(1 * 16);        // corner radius 1 pixels
 GD.Vertex2f(xi*16, yi*16);   //esquina inicial
 //GD.Vertex2f(xf*16, yf*16);   //esquina final
 GD.Vertex2f(xf*16, yf*16);   //esquina final
 GD.RestoreContext();
 //GD.End();	
}



void GDClass::cmd_progress(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t options, uint16_t val, uint16_t range) {
  cFFFFFF(0x0f);
  ch(x);
  ch(y);
  ch(w);
  ch(h);
  cH(options);
  cH(val);
  cH(range);
  cH(0);
  cprim = 0xff;
}
void GDClass::cmd_regread(uint32_t ptr) {
  cFFFFFF(0x19);
  cI(ptr);
  cI(0);
}
void GDClass::cmd_rotate(int32_t a) {
  cFFFFFF(0x29);
  ci(a);
}
void GDClass::cmd_scale(int32_t sx, int32_t sy) {
  cFFFFFF(0x28);
  ci(sx);
  ci(sy);
}
void GDClass::cmd_screensaver(void) {
  cFFFFFF(0x2f);
}
void GDClass::cmd_scrollbar(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t options, uint16_t val, uint16_t size, uint16_t range) {
  cFFFFFF(0x11);
  ch(x);
  ch(y);
  ch(w);
  ch(h);
  cH(options);
  cH(val);
  cH(size);
  cH(range);
  cprim = 0xff;
}
void GDClass::cmd_setfont(byte font, uint32_t ptr) {
  cFFFFFF(0x2b);
  cI(font);
  cI(ptr);
}
void GDClass::cmd_setmatrix(void) {
  cFFFFFF(0x2a);
}

//BT817
#if (SizeEVE==434)
void GDClass::cmd_testcard(void) {
  cFFFFFF(0x61);
}
#endif

//BT817
#if (SizeEVE==54)
void GDClass::cmd_testcard(void) {
  cFFFFFF(0x61);
}
#endif

//BT817
#if (SizeEVE==100)
void GDClass::cmd_testcard(void) {
  cFFFFFF(0x61);
}
#endif

#if (SizeEVE==74)
void GDClass::cmd_testcard(void) {
  cFFFFFF(0x61);
}
#endif  
//BT817

void GDClass::cmd_logo(void) {
  cFFFFFF(0x31);
}

void GDClass::cmd_sketch(int16_t x, int16_t y, uint16_t w, uint16_t h, uint32_t ptr, uint16_t format) {
  cFFFFFF(0x30);
  ch(x);
  ch(y);
  cH(w);
  cH(h);
  cI(ptr);
  cI(format);
}
void GDClass::cmd_slider(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t options, uint16_t val, uint16_t range) {
  cFFFFFF(0x10);
  ch(x);
  ch(y);
  ch(w);
  ch(h);
  cH(options);
  cH(val);
  cH(range);
  cH(0);
  cprim = 0xff;
}
void GDClass::cmd_snapshot(uint32_t ptr) {
  cFFFFFF(0x1f);
  cI(ptr);
}
void GDClass::cmd_spinner(int16_t x, int16_t y, byte style, byte scale) {
  cFFFFFF(0x16);
  ch(x);
  ch(y);
  cH(style);
  cH(scale);
}
void GDClass::cmd_stop(void) {
  cFFFFFF(0x17);
}
void GDClass::cmd_swap(void) {
  cFFFFFF(0x01);
}
void GDClass::cmd_text(int16_t x, int16_t y, byte font, uint16_t options, const char *s) {
  cFFFFFF(0x0c);
  ch(x);
  ch(y);
  ch(font);
  cH(options);
  cs(s);
  cprim = BITMAPS;
}
void GDClass::cmd_toggle(int16_t x, int16_t y, int16_t w, byte font, uint16_t options, uint16_t state, const char *s) {
  cFFFFFF(0x12);
  ch(x);
  ch(y);
  ch(w);
  ch(font);
  cH(options);
  cH(state);
  cs(s);
}
void GDClass::cmd_track(int16_t x, int16_t y, uint16_t w, uint16_t h, byte tag) {
  cFFFFFF(0x2c);
  ch(x);
  ch(y);
  ch(w);
  ch(h);
  ch(tag);
  ch(0);
}
void GDClass::cmd_translate(int32_t tx, int32_t ty) {
  cFFFFFF(0x27);
  ci(tx);
  ci(ty);
}
void GDClass::cmd_playvideo(int32_t options) {
  cFFFFFF(0x3a);
  cI(options);
}
void GDClass::cmd_romfont(uint32_t font, uint32_t romslot) {
  cFFFFFF(0x3f);
  cI(font);
  cI(romslot);
}
void GDClass::cmd_mediafifo(uint32_t ptr, uint32_t size) {
  cFFFFFF(0x39);
  cI(ptr);
  cI(size);
}
void GDClass::cmd_setbase(uint32_t b) {
  cFFFFFF(0x38);
  cI(b);
}
void GDClass::cmd_videoframe(uint32_t dst, uint32_t ptr) {
  cFFFFFF(0x41);
  cI(dst);
  cI(ptr);
}
void GDClass::cmd_snapshot2(uint32_t fmt, uint32_t ptr, int16_t x, int16_t y, int16_t w, int16_t h) {
  cFFFFFF(0x37);
  cI(fmt);
  cI(ptr);
  ch(x);
  ch(y);
  ch(w);
  ch(h);
}
void GDClass::cmd_setfont2(uint32_t font, uint32_t ptr, uint32_t firstchar) {
  cFFFFFF(0x3b);
  cI(font);
  cI(ptr);
  cI(firstchar);
}
void GDClass::cmd_setbitmap(uint32_t source, uint16_t fmt, uint16_t w, uint16_t h) {
  cFFFFFF(0x43);
  cI(source);
  ch(fmt);
  ch(w);
  ch(h);
  ch(0);
}

void GDClass::cmd_flasherase() {
  cFFFFFF(0x44);
}

void GDClass::cmd_flashwrite(uint32_t dest, uint32_t num) {
  cFFFFFF(0x45);
  cI(dest);
  cI(num);
}

void GDClass::cmd_flashupdate(uint32_t dst, uint32_t src, uint32_t n) {
  cFFFFFF(0x47);
  cI(dst);
  cI(src);
  cI(n);
}

void GDClass::cmd_flashread(uint32_t dst, uint32_t src, uint32_t n) {
  cFFFFFF(0x46);
  cI(dst);
  cI(src);
  cI(n);
}

void GDClass::cmd_flashdetach() {
  cFFFFFF(0x48);
}

void GDClass::cmd_flashattach() {
  cFFFFFF(0x49);
}

uint32_t GDClass::cmd_flashfast(uint32_t &r) {
  cFFFFFF(0x4a);
  r = GDTR.getwp();
  cI(0xdeadbeef);
  return r;
}



// XXX to do: cmd_rotate_around cmd_inflate2

void GDClass::cmd_setrotate(uint32_t r) {
  cFFFFFF(0x36);
  cI(r);
  // As a special favor, update variables w and h according to this
  // rotation
  w = GDTR.rd16(REG_HSIZE);
  h = GDTR.rd16(REG_VSIZE);
  if (r & 2) {
    int t = h;
    h = w;
    w = t;
  }
}

void GDClass::cmd_videostart() {
  cFFFFFF(0x40);
}

void GDClass::cmd_sync() {
  cFFFFFF(0x42);
}

byte GDClass::rd(uint32_t addr) {
  return GDTR.rd(addr);
}
void GDClass::wr(uint32_t addr, uint8_t v) {
  GDTR.wr(addr, v);
}
uint16_t GDClass::rd16(uint32_t addr) {
  return GDTR.rd16(addr);
}
void GDClass::wr16(uint32_t addr, uint16_t v) {
  GDTR.wr16(addr, v);
}
uint32_t GDClass::rd32(uint32_t addr) {
  return GDTR.rd32(addr);
}
void GDClass::wr32(uint32_t addr, uint32_t v) {
  GDTR.wr32(addr, v);
}
void GDClass::wr_n(uint32_t addr, byte *src, uint32_t n) {
  GDTR.wr_n(addr, src, n);
}
void GDClass::rd_n(byte *dst, uint32_t addr, uint32_t n) {
  GDTR.rd_n(dst, addr, n);
}

void GDClass::cmdbyte(uint8_t b) {
  GDTR.cmdbyte(b);
}
void GDClass::cmd32(uint32_t b) {
  GDTR.cmd32(b);
}
void GDClass::finish(void) {
  GDTR.finish();
}

void GDClass::get_inputs(void) {
  GDTR.finish();
  byte *bi = (byte*)&inputs;
    inputs.x = inputs.y = -32768;
  GDTR.rd_n(bi, REG_TRACKER, 4);
  GDTR.rd_n(bi + 4, REG_TOUCH_RZ, 13);
  GDTR.rd_n(bi + 17, REG_TAG, 1);
  inputs.touching = (inputs.x != -32768);
  inputs.xytouch.set(PIXELS(inputs.x), PIXELS(inputs.y));
}
void GDClass::bulkrd(uint32_t a) {
  GDTR.bulk(a);
}
void GDClass::resume(void) {
  GDTR.resume();
}
void GDClass::__end(void) {
  GDTR.__end();
}
void GDClass::play(uint8_t instrument, uint8_t note) {
  wr16(REG_SOUND, (note << 8) | instrument);
  wr(REG_PLAY, 1);
}
void GDClass::sample(uint32_t start, uint32_t len, uint16_t freq, uint16_t format, int loop) {
  GD.wr32(REG_PLAYBACK_START, start);
  GD.wr32(REG_PLAYBACK_LENGTH, len);
  GD.wr16(REG_PLAYBACK_FREQ, freq);
  GD.wr(REG_PLAYBACK_FORMAT, format);
  GD.wr(REG_PLAYBACK_LOOP, loop);
  GD.wr(REG_PLAYBACK_PLAY, 1);
}
void GDClass::reset() {
  GDTR.__end();
  GDTR.wr(REG_CPURESET, 1);
  GDTR.wr(REG_CPURESET, 0);
  GDTR.resume();
}

// Load named file from storage
// returns 0 on failure (e.g. file not found), 1 on success

//FT81xmania Team
typedef void (* FUNC_POINTER)(long, long);

byte GDClass::load(const char *filename, FUNC_POINTER progress)
{
//SdFat beta V2
 //#define SD_FAT_TYPE 1  //para FAT16/FAT32
   //File32 archivo;
 //#define SD_FAT_TYPE 3  //para FAT16/FAT32 and exFAT
   FsFile archivo;
   archivo = SSD.open(filename);
   //Serial.print(filename);
//SdFat beta V2
  return (loadSdFat(archivo, progress)); 
}
//FT81xmania Team

//FT81xmania Team
//#define SD_FAT_TYPE 1  //para FAT16/FAT32
//byte GDClass::loadSdFat(File32& archivo, FUNC_POINTER progress)
//#define SD_FAT_TYPE 3  //para FAT16/FAT32 and exFAT
byte GDClass::loadSdFat(FsFile& archivo, FUNC_POINTER progress)
{
  int offset=0;
  int offsetFT;
  int bytesDisponibles;
  int wbn;
  
  GD.__end();
  
  if (archivo) {
    
    int tamArchivo=archivo.available();
	
	//Serial.print(", ");  Serial.print(tamArchivo);  Serial.println(" bytes"); 
    
    while( offset < tamArchivo)
    {
        uint16_t m = ( (archivo.available() > TAM_BUFFER_SD) ? TAM_BUFFER_SD : archivo.available());
        archivo.read(buf,m);
        
		
        offsetFT=0;
        bytesDisponibles=m;
        while (offsetFT < m) 
        {
              uint16_t n = ( (bytesDisponibles > TAM_BUFFER_FT) ? TAM_BUFFER_FT : bytesDisponibles);
             
              wbn = (n + 3) & ~3;   // force 32-bit alignment

              GD.resume();
              if (progress)
                (*progress)((offset+offsetFT), tamArchivo);
#ifdef DUMMY_GDCOPYRAM
                memcpy (FTbuf, buf+offsetFT, wbn );
#else
                GD.copyram((buf+offsetFT), wbn);
#endif              
              offsetFT+=n;
			  
              bytesDisponibles-=n;
              GDTR.stop();
        }
        offset+=m;         
    }	
            
    GD.resume();
	#ifdef TEENSYDUINO
	 #if defined(ARDUINO_TEENSY32)
	  //SPI.endTransaction();
	 #else
	
     SPI.endTransaction();
	 #endif
	#endif
	
  #if(STM32_CPU == 4110)
     //SPI_2.endTransaction(SD_PIN);
  #endif    	

  #if(STM32_CPU == 446)
     //SPI_2.endTransaction(SD_PIN);
  #endif

  #if(STM32_CPU == 7670)
     SPI_3.endTransaction(SD_PIN);
  #endif
  
  #if(STM32_CPU == 7460)
     //SPI_3.endTransaction(SD_PIN); //aparentemente no lo necesita en la
  #endif  
	
    return 1;
  }
  GD.resume();
  #ifdef TEENSYDUINO
	 #if defined(ARDUINO_TEENSY32)
	  //SPI.endTransaction();
	 #else
	
     SPI.endTransaction();
	 #endif
  #endif
  
  #if(STM32_CPU == 4110)
     //SPI_2.endTransaction(SD_PIN);
  #endif      
  
  #if(STM32_CPU == 446)
     //SPI_2.endTransaction(SD_PIN);
  #endif  
  
  #if(STM32_CPU == 7670)
   //  SPI_3.endTransaction(SD_PIN);
  #endif  
  
  #if(STM32_CPU == 7460)
     //SPI_3.endTransaction(SD_PIN);
  #endif    
  
  return 0;
}
//FT81xmania Team

// Generated by mk_bsod.py. Blue screen with 'ERROR' text
static const PROGMEM uint8_t __bsod[48] = {
0, 255, 255, 255, 96, 0, 0, 2, 7, 0, 0, 38, 12, 255, 255, 255, 240, 0,
90, 0, 31, 0, 0, 6, 67, 111, 112, 114, 111, 99, 101, 115, 115, 111,
114, 32, 101, 120, 99, 101, 112, 116, 105, 111, 110, 0, 0, 0
};
static const PROGMEM uint8_t __bsod_815[56] = {
0, 255, 255, 255, 96, 0, 0, 2, 7, 0, 0, 38, 12, 255, 255, 255, 240, 0,
136, 0, 28, 0, 0, 22, 67, 111, 112, 114, 111, 99, 101, 115, 115, 111,
114, 32, 101, 120, 99, 101, 112, 116, 105, 111, 110, 58, 10, 10, 37,
115, 0, 0, 0, 0, 0, 0
};
static const PROGMEM uint8_t __bsod_badfile[44] = {
0, 255, 255, 255, 96, 0, 0, 2, 7, 0, 0, 38, 12, 255, 255, 255, 240, 0,
90, 0, 29, 0, 0, 6, 67, 97, 110, 110, 111, 116, 32, 111, 112, 101,
110, 32, 102, 105, 108, 101, 58, 0, 0, 0
};

// Fatal error alert.
// Show a blue screen with message.
// This method never returns.

void GDClass::alert()
{
 // GDTR.coprocsssor_recovery();
 // if (ft8xx_model < 2)
 //   copy(__bsod, sizeof(__bsod));
 // else
 //   copy(__bsod_815, sizeof(__bsod_815));
  begin();
  cmd_dlstart();
  
  #define RAM_RAD1 0
    static const unsigned char PROGMEM Rad1[] = {
    #include "Rad1.h"
  };
 cmd_inflate(RAM_RAD1);
  copy(Rad1, sizeof(Rad1));
  GD.BitmapHandle(0);
  GD.BitmapSource(0);
  GD.BitmapLayout(ARGB1555, 400, 200);
  GD.BitmapSize(NEAREST, BORDER, BORDER, 200, 200);

  if (BT8XX==1)
 {
  //Serial.print("FT80");  Serial.println(BT8XX, HEX); //Serial.println(BT8XX, HEX);
  GDTR.wr(REG_ROTATE, ROTACION);
  //Serial.println(ROTACION);
 }
 
 if (BT8XX==19)
 {
  //Serial.print("FT8");  Serial.println(BT8XX, HEX); //Serial.println(BT8XX, HEX);
  cmd_setrotate(ORIENTACION);
  //Serial.println(ORIENTACION);
 }
 
 if (BT8XX>19)
 {
  //Serial.print("BT8");  Serial.println(BT8XX, HEX); //Serial.println(BT8XX, HEX);
  cmd_setrotate(ORIENTACION);
  //Serial.println(ORIENTACION);
 } 


  ClearColorRGB(0x650000);
  Clear();

  GD.ColorA(85);
   GD.Begin(BITMAPS);
   GD.Vertex2ii((GD.w / 2)-100, (GD.h / 2)-100, 0);
   ColorRGB(255,255,0);
  GD.ColorA(255);

  cmd_text(GD.w / 2, (GD.h / 2)+29, 29, OPT_CENTER, "Invalid operation");
  cmd_text(GD.w / 2, (GD.h / 2)+12, 20, OPT_CENTER, "Check the image name");
  cmd_text(GD.w / 2, (GD.h / 2)-0, 20, OPT_CENTER, "Check the type of the image file");
  cmd_text(GD.w / 2, (GD.h / 2)-12, 20, OPT_CENTER, "Is it the image(s) file(s) on the microSD card?");
  cmd_text(GD.w / 2, (GD.h / 2)-30, 26, OPT_CENTER, "Is it the microSD present in the holder?");
  cmd_text(GD.w / 2, (GD.h / 2)+29+22, 20, OPT_CENTER, "GD.swap() is lost?");
  cmd_text(GD.w / 2, (GD.h / 2)+29+50, 20, OPT_CENTER, "XT8XX suggests: take a break and check again!");

  swap();
  //GD.finish();
  finish();
  for (;;) 
  ;
}

void GDClass::safeload(const char *filename)
{
  if (!load(filename)) {
    __end();
    begin(0);
    copy(__bsod_badfile, sizeof(__bsod_badfile));
    cmd_text(240, 190, 29, OPT_CENTER, filename);
    swap();
    for (;;) ;
  }
}

void GDClass::textsize(int &w, int &h, int font, const char *s)
{
  uint32_t font_addr = rd32(0x309074 + 4 * font);
  w = 0;
  while (*s)
    w += GD.rd(font_addr + *s++);
  h = GD.rd(font_addr + 140);
}