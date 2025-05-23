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

#ifndef _GDSTx_H_INCLUDED
#define _GDSTx_H_INCLUDED

//FT81xmania team

#define GDT4Xv134_VERSION  "2.2 T4x-STM32-RPiPico"
#define GD23X_VERSION      "2.2 T4x-STM32-RPiPico"
#define GD23ZUTX_VERSION   "2.2 T4x-STM32-RPiPico"
#define GDSTx_VERSION      "2.2 T4x-STM32-RPiPico"

#include "SPI.h"
#if defined(ARDUINO_ARCH_RP2040)                              //*******************************************************RP2040-Pico
 #define DISABLE_FS_H_WARNING  // Disable warning for type File not defined.
#endif

#if defined(ARDUINO_ARCH_STM32)  
 #define DISABLE_FS_H_WARNING  // Disable warning for type File not defined.
#endif

#include "SdFat.h"

#include "Arduino.h"

#include "config.h"

#define JPGsizeX   					 0        //under test
#define JPGsizeY   					 0        //under test
#define  H743    					 0        //under test
#define POR_PIN  					 0        //under test 


#ifdef ARDUINO_UNOR4_MINIMA
  	#if (SizeEVE==5)
		#define SetSPISpeed   36000000    // reducir al valor si la pantalla no enciende o es inestable con gráficos lineales contínuos y/o reproducción de videos
	#endif 
	
  	#if (SizeEVE==510)
		#define SetSPISpeed   36000000    // reducir al valor si la pantalla no enciende o es inestable con gráficos lineales contínuos y/o reproducción de videos
	    
	#endif 	
	
  #define SD_PIN 			       8         //SPI-1
  #define SetSDSpeed       	 	  24	
#endif

#if defined(ARDUINO_ARCH_RP2040)                              //*******************************************************RP2040-Pico

  #define SD_PIN 			      13         //SPI-1
  #define SetSDSpeed       	 	  24
  
  #if (SizeEVE==43)
   #define SetSPISpeed   		  24000000   //SPI-0
  #endif

  //#define SD_PIN 			      13         //SPI-1
  //#define SetSDSpeed       	 	  24
  
  #if (SizeEVE==51)                          //Riverdi-FT813 5.1"   7.1"
   #define SetSPISpeed   		  24000000   //SPI-0
  #endif

  #if (SizeEVE==5)                          //Riverdi-FT813 5.1"   7.1"
   #define SetSPISpeed   		  24000000   //SPI-0
  #endif

 #if (SizeEVE==35)                          //NHD-35
   #define SetSPISpeed   		  36000000   //SPI-0
  #endif

  //#define SD_PIN 			      13         //SPI-1
  //#define SetSDSpeed       	 	  24  
  
#endif                                                        //*******************************************************RP2040-Pico

#ifdef TEENSYDUINO

#if (SizeEVE==0)
 //#define SetSPISpeed   		  29000000   // 29000000 --- gameduino3 shield
 #define SetSPISpeed   		  20000000   //  --- specific FT801/FT800
 //#define POR_PIN                  33   //No conectar
#endif

	#if (SizeEVE==54)
		#define POR_PIN             24	  // 03 Junio 2022 THX hermano!. Funciona para teensy 3.6 XD XD   también funciona en teensy 4.1 XD XD   Reset-PD Pin
	#endif
 
 	#if (SizeEVE==74)
		#define POR_PIN             24	  // 03 Junio 2022 THX hermano!. Funciona para teensy 3.6 XD XD   también funciona en teensy 4.1 XD XD   Reset-PD Pin
	#endif
 
  	#if (SizeEVE==434)
		#define POR_PIN             24	  // 03 Junio 2022 THX hermano!. Funciona para teensy 3.6 XD XD   también funciona en teensy 4.1 XD XD   Reset-PD Pin
	#endif
 
 	#if (SizeEVE==431)
		#define SetSPISpeed   36000000    // reducir al valor si la pantalla no enciende o es inestable con gráficos lineales contínuos y/o reproducción de videos
		//#define POR_PIN             24	  //06 Junio 2023 Reset-PD Pin   revisar si funciona en EVE3x-43
	#endif
 
  	#if (SizeEVE==43)
		#define SetSPISpeed   36000000    // reducir al valor si la pantalla no enciende o es inestable con gráficos lineales contínuos y/o reproducción de videos
	#endif
 
  	#if (SizeEVE==5)
		#define SetSPISpeed   36000000    // reducir al valor si la pantalla no enciende o es inestable con gráficos lineales contínuos y/o reproducción de videos
	#endif 
	
  	#if (SizeEVE==510)
		#define SetSPISpeed   36000000    // reducir al valor si la pantalla no enciende o es inestable con gráficos lineales contínuos y/o reproducción de videos
	#endif 	
 
	#if (SizeEVE==52)
		#define SetSPISpeed   32000000    // reducir al valor óptimo= 32000000, 36000000 es inestable con gráficos lineales contínuos y reproducción de videos
		#define POR_PIN             24	  // 03 Junio 2022 THX hermano!. Funciona para teensy 3.6 XD XD   también funciona en teensy 4.1 XD XD   Reset-PD Pin
	#endif
 
	#if (SizeEVE==53)
		#define POR_PIN             36	  // 03 Junio 2022 THX hermano!. Funciona para teensy 3.6 XD XD   también funciona en teensy 4.1 XD XD   Reset-PD Pin
	#endif 
 
#endif

#if defined(ARDUINO_ARCH_STM32)     //*******************************************************STM32 boards setup: EEPROM source, CS-TFT, MCU, SD_PIN, SDSpeed

  #include <AT24Cxx.h>
  #define EEPROM_SOURCE      		 0    //1-Usar para MO_38     0-para los demás

  #if (EEPROM_SOURCE == 0)
   #define i2c_address     		  0x50    //EEPROM breakout like 24FC512
//   #define i2c_address     	  0x51  
  #endif

  #if (EEPROM_SOURCE == 1)
   #define i2c_address     		  0x57   //EEPROM on DS3231
  #endif


 #if(STM32_CPU == 103) 
    #define SD_PIN          	  PB12  //PB12 SPI2-F103   Danieleff-Core          M3DEMO - funciona sin problemas
    #define SetSDSpeed       	 	36  
  #endif 

  #if(STM32_CPU == 411) 
    #define SD_PIN         		  PB12  //PB12 SPI2-F411CE   Danieleff-Core          funciona sin problemas
    #define SetSDSpeed       	    36  
  #endif   
  
  #if(STM32_CPU == 446) 
    #define SD_PIN         		  PB12  //PB12 SPI2-F411CE   Danieleff-Core          experimental por verificar   
    #define SetSDSpeed       	    36  
  #endif     
  
  #if (STM32_CPU==4110)
    #define SD_PIN         		  PB12  //PB12 SPI2-F411CE   STM32-Core  
    #define SetSDSpeed       	    48  
  #endif    
 
 #if(STM32_CPU == 4073) 
    #define SD_PIN          	  PB12  //PB12 SPI2-F407VG            funciona sin problemas  M4DEMO
    #define SetSDSpeed              48
  #endif  

 #if(STM32_CPU == 4074) 
    #define SD_PIN          	  PB12  //PB12 SPI2-F407VG            funciona en core STM32 Oficial
    #define SetSDSpeed              48
  #endif  

  #if(STM32_CPU == 746) 
     #define SD_PIN        		  PA15  //PA15  SPI3 F429 y Core7XXI          
     #define SetSDSpeed             36  
  #endif
  
  #if(STM32_CPU == 767) 
     #define mySerialPort3 SerialUART3
     #define Serial mySerialPort3	  
  
     #define SD_PIN        		  PB11  //PB11 SPI3-F767, PA11 SPI2-F767      
     #define SetSDSpeed      	    36  
  #endif  


  #if(STM32_CPU == 7670)   
     #define SD_PIN          	  PB11  //PB11 o PA15 SPI3-F767/H743, PA11 SPI2-F767
     #define SetSDSpeed      	    48
  #endif


  #if(STM32_CPU == 7460) 
     #define SD_PIN        		  PA15  //PA15  SPI3 F429 y Core7XXI          
     #define SetSDSpeed             36  
  #endif


#endif                              //*******************************************************STM32 boards setup: EEPROM source, CS-TFT, MCU, SD_PIN, SDSpeed

#if defined(ARDUINO_ARCH_STM32)     //*******************************************************STM32 boards Size-TFT, SPI-TFT-Speed, orientation, PD/Reset-pin (POR)

//*************** User editable line to select EVE TFT size
#if (SizeEVE==0)
 #define SetSPISpeed   		  36000000   //14000000  24000000-FT843        36000000-NHD43

//  #if(STM32_CPU == 4073)
//    #define POR_PIN                PE1	  //Si funciona XD XD F407VG
//  #endif

#endif
#if (SizeEVE==38)
 #define SetSPISpeed   		  30000000
#endif
#if (SizeEVE==35)
 #define SetSPISpeed   		  36000000   //36000000   

 #if(STM32_CPU == 103) 
  #define SetSPISpeed  		  29000000   //para 29-F103VET6
 #endif 
  
#endif
#if (SizeEVE==43)
 #define SetSPISpeed   		  36000000   //36000000
#endif
#if (SizeEVE==5)
  #define SetSPISpeed   	  36000000
  
  #if(STM32_CPU == 103)
    #define SetSPISpeed   	  36000000
  #endif	

#endif
#if (SizeEVE==51)
 #define SetSPISpeed   		  36000000
#endif
#if (SizeEVE==52)
 #define SetSPISpeed   		  32000000    //36000000

  #if(STM32_CPU == 4073)
    #define POR_PIN                PE1	  //Si funciona XD XD F407VG
  #endif

  #if(STM32_CPU == 411)
    #define POR_PIN                PA8	  //Si funciona XD XD F411CE-Black
  #endif  

  #if(STM32_CPU == 446)
    #define POR_PIN                PA8	  //experimental
  #endif  

  #if(STM32_CPU == 767)
    #define POR_PIN                PA8	  //Si funciona en Nucleo-F767ZI
  #endif    

  #if(STM32_CPU == 746)
    #define POR_PIN                PE0	  //Si funciona en Core7XXI
  #endif    

#endif

#if (SizeEVE==53)
 #define SetSPISpeed   		  36000000

  #if(STM32_CPU == 446)
    #define POR_PIN                PD2	  //Experimental
  #endif    

  #if(STM32_CPU == 746)
    #define POR_PIN                PE0	  //Si funciona en Core7XXI
  #endif    

#endif

#if (SizeEVE==54)
 #define SetSPISpeed   		  36000000     //32    36

  #if(STM32_CPU == 4073)
    #define POR_PIN                PE1	  //Si funciona XD XD F407VG
  #endif

  #if(STM32_CPU == 411)
    #define POR_PIN                PA8	  //Si funciona XD XD F411CE-Black
  #endif  
  
  #if(STM32_CPU == 446)
    #define POR_PIN                PA8	  //experimental
  #endif    
  
  #if(STM32_CPU == 767)
    #define POR_PIN                PA8	  //Si funciona en Nucleo-F767ZI
  #endif   

  #if(STM32_CPU == 746)
    #define POR_PIN                PE0	  
  #endif      

#endif

#if (SizeEVE==7)
 #define SetSPISpeed   		  36000000
#endif

#if (SizeEVE==71)
 #define SetSPISpeed   		  34000000
#endif

#if (SizeEVE==100)
 #define SetSPISpeed   		  36000000
#endif
 
#endif                              //*******************************************************STM32 boards Size-TFT, SPI-TFT-Speed, orientation, PD/Reset-pin (POR)
 



//FT81xmania team

#define RGB(r, g, b)    ((uint32_t)((((r) & 0xffL) << 16) | (((g) & 0xffL) << 8) | ((b) & 0xffL)))
#define F8(x)           (int((x) * 256L))
#define F16(x)          ((int32_t)((x) * 65536L))

////////////////////////////////////////////////////////////////////////

class xy {
public:
  int x, y;
  void set(int _x, int _y);
  void rmove(int distance, int angle);
  int angleto(class xy &other);
  void draw(byte offset = 0);
  void rotate(int angle);
  int onscreen(void);
  class xy operator<<=(int d);
  class xy operator+=(class xy &other);
  class xy operator-=(class xy &other);
  long operator*(class xy &other);
  class xy operator*=(int);
  int nearer_than(int distance, xy &other);
};

class Bitmap {
public:
  xy size, center;
  uint32_t source;
  uint16_t format;
  int8_t handle;

  void fromtext(int font, const char* s);
  void fromfile(const char *filename, int format = 7);

  void bind(uint8_t handle);

  void wallpaper();
  void draw(int x, int y, int16_t angle = 0);
  void draw(const xy &pos, int16_t angle = 0);

private:
  void defaults(uint8_t f);
  void setup(void);
};

class Bitmap __fromatlas(uint32_t addr);

////////////////////////////////////////////////////////////////////////

enum Primitive {
BITMAPS              = 1,
POINTS               = 2,
LINES                = 3,
LINE_STRIP           = 4,
EDGE_STRIP_R         = 5,
EDGE_STRIP_L         = 6,
EDGE_STRIP_A         = 7,
EDGE_STRIP_B         = 8,
RECTS                = 9,
};

class GDClass {

//RndMnkIII, FT81xmania Team
private:
    static const uint16_t TAM_BUFFER_SD; //8192 si se aumenta de tamaño se mejora en eficiencia de lectura 
    static const uint16_t TAM_BUFFER_FT;
    static byte buf[];
    static byte FTbuf[];
//RndMnkIII, FT81xmania Team	
	
public:
  int w, h;
  uint32_t loadptr;
  byte vxf;   // Vertex Format

  void begin(int cs = CS);

  uint16_t random();
  uint16_t random(uint16_t n);
  uint16_t random(uint16_t n0, uint16_t n1);
  void seed(uint16_t n);
  int16_t rsin(int16_t r, uint16_t th);
  int16_t rcos(int16_t r, uint16_t th);
  void polar(int &x, int &y, int16_t r, uint16_t th);
  uint16_t atan2(int16_t y, int16_t x);

#if !defined(TEENSYDUINO)
  void copy(const PROGMEM uint8_t *src, int count);
#else
  void copy(const uint8_t *src, int count);
#endif
  void copyram(byte *src, int count);

  void self_calibrate(void);

  void swap(void);
  void flush(void);
  void finish(void);

  void play(uint8_t instrument, uint8_t note = 0);
  void sample(uint32_t start, uint32_t len, uint16_t freq, uint16_t format, int loop = 0);

  void get_inputs(void);
  
  struct {
    uint16_t track_tag;
    uint16_t track_val;
    uint16_t rz;
    uint16_t __dummy_1;
    int16_t y;
    int16_t x;
    int16_t tag_y;
    int16_t tag_x;
    uint8_t tag;
    uint8_t ptag;
    uint8_t touching;
    xy xytouch;
  } inputs;

  void AlphaFunc(byte func, byte ref);
  void Begin(Primitive prim);
  void BitmapHandle(byte handle);
  void BitmapLayout(byte format, uint16_t linestride, uint16_t height);
  void BitmapSize(byte filter, byte wrapx, byte wrapy, uint16_t width, uint16_t height);
  void BitmapSource(uint32_t addr);
  void BitmapTransformA(int32_t a);
  void BitmapTransformB(int32_t b);
  void BitmapTransformC(int32_t c);
  void BitmapTransformD(int32_t d);
  void BitmapTransformE(int32_t e);
  void BitmapTransformF(int32_t f);
  void BlendFunc(byte src, byte dst);
  void Call(uint16_t dest);
  void Cell(byte cell);
  void ClearColorA(byte alpha);
  void ClearColorRGB(byte red, byte green, byte blue);
  void ClearColorRGB(uint32_t rgb);
  void Clear(byte c, byte s, byte t);
  void Clear(void);
  void ClearStencil(byte s);
  void ClearTag(byte s);
  void ColorA(byte alpha);
  void ColorMask(byte r, byte g, byte b, byte a);
  void ColorRGB(byte red, byte green, byte blue);
  void ColorRGB(uint32_t rgb);
  void Display(void);
  void End(void);
  void Jump(uint16_t dest);
  void LineWidth(uint16_t width);
  void Macro(byte m);
  void PointSize(uint16_t size);
  void RestoreContext(void);
  void Return(void);
  void SaveContext(void);
  void ScissorSize(uint16_t width, uint16_t height);
  void ScissorXY(uint16_t x, uint16_t y);
  void StencilFunc(byte func, byte ref, byte mask);
  void StencilMask(byte mask);
  void StencilOp(byte sfail, byte spass);
  void TagMask(byte mask);
  void Tag(byte s);
  void Vertex2f(int16_t x, int16_t y);
  void Vertex2ii(uint16_t x, uint16_t y, byte handle = 0, byte cell = 0);

  void VertexFormat(byte frac);
  void BitmapLayoutH(byte linestride, byte height);
  void BitmapSizeH(byte width, byte height);
  void PaletteSource(uint32_t addr);
  void VertexTranslateX(uint32_t x);
  void VertexTranslateY(uint32_t y);
  void Nop(void);
  void BitmapExtFormat(uint16_t format);
  void BitmapSwizzle(byte r, byte g, byte b, byte a);

  // Higher-level graphics commands

  void cmd_append(uint32_t ptr, uint32_t num);
  void cmd_bgcolor(uint32_t c);
  void cmd_button(int16_t x, int16_t y, uint16_t w, uint16_t h, byte font, uint16_t options, const char *s);
  void cmd_calibrate(void);
  void cmd_clock(int16_t x, int16_t y, int16_t r, uint16_t options, uint16_t h, uint16_t m, uint16_t s, uint16_t ms);
  void cmd_coldstart(void);
  void cmd_dial(int16_t x, int16_t y, int16_t r, uint16_t options, uint16_t val);
  void cmd_dlstart(void);
  void cmd_fgcolor(uint32_t c);
  void cmd_fillwidth(uint32_t s);
  void cmd_gauge(int16_t x, int16_t y, int16_t r, uint16_t options, uint16_t major, uint16_t minor, uint16_t val, uint16_t range);
  void cmd_getmatrix(void);
  void cmd_getprops(uint32_t &ptr, uint32_t &w, uint32_t &h);
  void cmd_getptr(void);
  void cmd_gradcolor(uint32_t c);
  void cmd_gradient(int16_t x0, int16_t y0, uint32_t rgb0, int16_t x1, int16_t y1, uint32_t rgb1);
  void cmd_inflate(uint32_t ptr);
  void cmd_interrupt(uint32_t ms);
  void cmd_keys(int16_t x, int16_t y, int16_t w, int16_t h, byte font, uint16_t options, const char*s);
  void cmd_loadidentity(void);
  void cmd_loadimage(uint32_t ptr, int32_t options);
  void cmd_memcpy(uint32_t dest, uint32_t src, uint32_t num);
  void cmd_memset(uint32_t ptr, byte value, uint32_t num);
  uint32_t cmd_memcrc(uint32_t ptr, uint32_t num);
  void cmd_memwrite(uint32_t ptr, uint32_t num);
  void cmd_regwrite(uint32_t ptr, uint32_t val);
  void cmd_number(int16_t x, int16_t y, byte font, uint16_t options, uint32_t n);

#if defined(ARDUINO_ARCH_STM32)  
   void printNfloat(int16_t x, int16_t y, float f, int16_t Presc, byte font);
#endif 

#if defined(ARDUINO_ARCH_RP2040)
  void printNfloat(int16_t x, int16_t y, double f, int16_t Presc, byte font, uint16_t options);
#endif 

#if defined(ARDUINO_UNOR4_MINIMA)
  void printNfloat(int16_t x, int16_t y, double f, int16_t Presc, byte font, uint16_t options);
#endif 
  
//  #ifdef TEENSYDUINO
//  void printNfloat2(int16_t x, int16_t y, float f, int16_t Presc, byte font);
//  #endif 
  
#ifdef TEENSYDUINO  
  void printNfloat(int16_t x, int16_t y, double f, int16_t Presc, byte font, uint16_t options);
#endif   
  
  void Rect_Empty(int16_t xi, int16_t yi,int16_t xf, int16_t yf, int16_t RF, int16_t GF, int16_t BF);
   //void Rect_Empty(int16_t xi, int16_t yi,int16_t xf, int16_t yf);
  void Rect_Filled(int16_t xi, int16_t yi,int16_t xf, int16_t yf, int16_t RF, int16_t GF, int16_t BF);  
  
  void cmd_progress(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t options, uint16_t val, uint16_t range);
  void cmd_regread(uint32_t ptr);
  void cmd_rotate(int32_t a);
  void cmd_scale(int32_t sx, int32_t sy);
  void cmd_screensaver(void);
  void cmd_scrollbar(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t options, uint16_t val, uint16_t size, uint16_t range);
  void cmd_setfont(byte font, uint32_t ptr);
  void cmd_setmatrix(void);
  
  //BT817
#if (SizeEVE==54)
  void cmd_testcard(void);
#endif  

#if (SizeEVE==434)
  void cmd_testcard(void);
#endif  

#if (SizeEVE==74)
  void cmd_testcard(void);
#endif  
  //BT817
  
  void cmd_logo(void);
  
  void cmd_sketch(int16_t x, int16_t y, uint16_t w, uint16_t h, uint32_t ptr, uint16_t format);
  void cmd_slider(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t options, uint16_t val, uint16_t range);
  void cmd_snapshot(uint32_t ptr);
  void cmd_spinner(int16_t x, int16_t y, byte style, byte scale);
  void cmd_stop(void);
  void cmd_swap(void);
  void cmd_text(int16_t x, int16_t y, byte font, uint16_t options, const char *s);
  
  
  void cmd_toggle(int16_t x, int16_t y, int16_t w, byte font, uint16_t options, uint16_t state, const char *s);
  void cmd_track(int16_t x, int16_t y, uint16_t w, uint16_t h, byte tag);
  void cmd_translate(int32_t tx, int32_t ty);

  void cmd_playvideo(int32_t options);
  void cmd_romfont(uint32_t font, uint32_t romslot);
  void cmd_mediafifo(uint32_t ptr, uint32_t size);
  void cmd_setbase(uint32_t b);
  void cmd_videoframe(uint32_t dst, uint32_t ptr);
  void cmd_snapshot2(uint32_t fmt, uint32_t ptr, int16_t x, int16_t y, int16_t w, int16_t h);
  void cmd_setfont2(uint32_t font, uint32_t ptr, uint32_t firstchar);
  void cmd_setrotate(uint32_t r);
  void cmd_videostart();
  void cmd_setbitmap(uint32_t source, uint16_t fmt, uint16_t w, uint16_t h);
  void cmd_sync();
  void cmd_flasherase();
  void cmd_flashwrite(uint32_t dest, uint32_t num);
  void cmd_flashupdate(uint32_t dst, uint32_t src, uint32_t n);
  void cmd_flashread(uint32_t dst, uint32_t src, uint32_t n);
  void cmd_flashdetach();
  void cmd_flashattach();
  uint32_t cmd_flashfast(uint32_t &r);
  
  

  byte rd(uint32_t addr);
  void wr(uint32_t addr, uint8_t v);
  uint16_t rd16(uint32_t addr);
  void wr16(uint32_t addr, uint16_t v);
  uint32_t rd32(uint32_t addr);
  void wr32(uint32_t addr, uint32_t v);
  void wr_n(uint32_t addr, byte *src, uint32_t n);
  void rd_n(byte *dst, uint32_t addr, uint32_t n);

  void cmd32(uint32_t b);

  void bulkrd(uint32_t a);
  void resume(void);
  void __end(void);
  void reset(void);

  
//RndMnkIII, FT81xmania Team

//#ifdef TEENSYDUINO

 //#define SD_FAT_TYPE 1   //para FAT16/FAT32
  //byte loadSdFat(File32& archivo, void (*progress)(long, long) = NULL);
  //void safeloadSdFat(File32& archivo);
  //#define SD_FAT_TYPE 3  //para FAT16/FAT32 and exFAT
  byte loadSdFat(FsFile& archivo, void (*progress)(long, long) = NULL);
  void safeloadSdFat(FsFile& archivo);
//#endif

//RndMnkIII, FT81xmania Team  
  
  byte load(const char *filename, void (*progress)(long, long) = NULL);
  void safeload(const char *filename);
  void alert();
  void textsize(int &w, int &h, int font, const char *s);

  
  void storage(void);
  void tune(void);

private:
  static void cFFFFFF(byte v);
  static void cI(uint32_t);
  static void ci(int32_t);
  static void cH(uint16_t);
  static void ch(int16_t);
  static void cs(const char *);
  static void fmtcmd(const char *fmt, ...);

  static void align(byte n);
  void cmdbyte(uint8_t b);

  uint32_t measure_freq(void);

  uint32_t rseed;
  byte cprim;       // current primitive
};

extern GDClass GD;
extern byte ft8xx_model;



typedef struct {
  byte handle;
  uint16_t w, h;
  uint16_t size;
} shape_t;

// convert integer pixels to subpixels
#define PIXELS(x)  int((x) * 16)

// Convert degrees to Furmans
#define DEGREES(n) ((65536L * (n)) / 360)

#define NEVER                0
#define LESS                 1
#define LEQUAL               2
#define GREATER              3
#define GEQUAL               4
#define EQUAL                5
#define NOTEQUAL             6
#define ALWAYS               7

#define ARGB1555             0
#define L1                   1
#define L4                   2
#define L8                   3
#define RGB332               4
#define ARGB2                5
#define ARGB4                6
#define RGB565               7

#define PALETTED             8
#define TEXT8X8              9
#define TEXTVGA              10
#define BARGRAPH             11
#define PALETTED565          14
#define PALETTED4444         15
#define PALETTED8            16
#define L2                   17



#define GLFORMAT             31

#define NEAREST              0
#define BILINEAR             1

#define BORDER               0
#define REPEAT               1

#define KEEP                 1
#define REPLACE              2
#define INCR                 3
#define DECR                 4
#define INVERT               5

#define DLSWAP_DONE          0
#define DLSWAP_LINE          1
#define DLSWAP_FRAME         2

#define INT_SWAP             1
#define INT_TOUCH            2
#define INT_TAG              4
#define INT_SOUND            8
#define INT_PLAYBACK         16
#define INT_CMDEMPTY         32
#define INT_CMDFLAG          64
#define INT_CONVCOMPLETE     128

#define TOUCHMODE_OFF        0
#define TOUCHMODE_ONESHOT    1
#define TOUCHMODE_FRAME      2
#define TOUCHMODE_CONTINUOUS 3

#define ZERO                 0
#define ONE                  1
#define SRC_ALPHA            2
#define DST_ALPHA            3
#define ONE_MINUS_SRC_ALPHA  4
#define ONE_MINUS_DST_ALPHA  5

#define OPT_MONO             1
#define OPT_NODL             2
#define OPT_FLAT             256
#define OPT_CENTERX          512
#define OPT_CENTERY          1024
#define OPT_CENTER           (OPT_CENTERX | OPT_CENTERY)
#define OPT_NOBACK           4096
#define OPT_NOTICKS          8192
#define OPT_NOHM             16384
#define OPT_NOPOINTER        16384
#define OPT_NOSECS           32768
#define OPT_NOHANDS          49152
#define OPT_RIGHTX           2048
#define OPT_SIGNED           256
#define OPT_SOUND            32

#define OPT_DITHER           256
#define OPT_3D               0
#define OPT_OPT_RGB565       0

#define OPT_NOTEAR           4
#define OPT_FULLSCREEN       8
#define OPT_MEDIAFIFO        16

#define LINEAR_SAMPLES       0
#define ULAW_SAMPLES         1
#define ADPCM_SAMPLES        2

// 'instrument' argument to GD.play()

#define SILENCE              0x00

#define SQUAREWAVE           0x01
#define SINEWAVE             0x02
#define SAWTOOTH             0x03
#define TRIANGLE             0x04

#define BEEPING              0x05
#define ALARM                0x06
#define WARBLE               0x07
#define CAROUSEL             0x08

#define PIPS(n)              (0x0f + (n))

#define HARP                 0x40
#define XYLOPHONE            0x41
#define TUBA                 0x42
#define GLOCKENSPIEL         0x43
#define ORGAN                0x44
#define TRUMPET              0x45
#define PIANO                0x46
#define CHIMES               0x47
#define MUSICBOX             0x48
#define BELL                 0x49

#define CLICK                0x50
#define SWITCH               0x51
#define COWBELL              0x52
#define NOTCH                0x53
#define HIHAT                0x54
#define KICKDRUM             0x55
#define POP                  0x56
#define CLACK                0x57
#define CHACK                0x58

#define MUTE                 0x60
#define UNMUTE               0x61

#define RAM_PAL              1056768UL


//FT81xmania--MO
#define RAM_REG                  0x302000
#define REG_GPIOX                0x9C
//#define REG_GPIOX_DIR          0x98
//FT81xmania--MO

#define RAM_CMD               (ft8xx_model ? 0x308000UL : 0x108000UL)
#define RAM_DL                (ft8xx_model ? 0x300000UL : 0x100000UL)
#define REG_CLOCK             (ft8xx_model ? 0x302008UL : 0x102408UL)
#define REG_CMD_DL            (ft8xx_model ? 0x302100UL : 0x1024ecUL)
#define REG_CMD_READ          (ft8xx_model ? 0x3020f8UL : 0x1024e4UL)
#define REG_CMD_WRITE         (ft8xx_model ? 0x3020fcUL : 0x1024e8UL)
#define REG_CPURESET          (ft8xx_model ? 0x302020UL : 0x10241cUL)
#define REG_CSPREAD           (ft8xx_model ? 0x302068UL : 0x102464UL)
#define REG_DITHER            (ft8xx_model ? 0x302060UL : 0x10245cUL)
#define REG_DLSWAP            (ft8xx_model ? 0x302054UL : 0x102450UL)
#define REG_FRAMES            (ft8xx_model ? 0x302004UL : 0x102404UL)
#define REG_FREQUENCY         (ft8xx_model ? 0x30200cUL : 0x10240cUL)
#define REG_GPIO              (ft8xx_model ? 0x302094UL : 0x102490UL)
#define REG_GPIO_DIR          (ft8xx_model ? 0x302090UL : 0x10248cUL)
#define REG_HCYCLE            (ft8xx_model ? 0x30202cUL : 0x102428UL)
#define REG_HOFFSET           (ft8xx_model ? 0x302030UL : 0x10242cUL)
#define REG_HSIZE             (ft8xx_model ? 0x302034UL : 0x102430UL)
#define REG_HSYNC0            (ft8xx_model ? 0x302038UL : 0x102434UL)
#define REG_HSYNC1            (ft8xx_model ? 0x30203cUL : 0x102438UL)
#define REG_ID                (ft8xx_model ? 0x302000UL : 0x102400UL)
#define REG_INT_EN            (ft8xx_model ? 0x3020acUL : 0x10249cUL)
#define REG_INT_FLAGS         (ft8xx_model ? 0x3020a8UL : 0x102498UL)
#define REG_INT_MASK          (ft8xx_model ? 0x3020b0UL : 0x1024a0UL)
#define REG_MACRO_0           (ft8xx_model ? 0x3020d8UL : 0x1024c8UL)
#define REG_MACRO_1           (ft8xx_model ? 0x3020dcUL : 0x1024ccUL)
#define REG_OUTBITS           (ft8xx_model ? 0x30205cUL : 0x102458UL)
#define REG_PCLK              (ft8xx_model ? 0x302070UL : 0x10246cUL)
#define REG_PCLK_POL          (ft8xx_model ? 0x30206cUL : 0x102468UL)
#define REG_PLAY              (ft8xx_model ? 0x30208cUL : 0x102488UL)
#define REG_PLAYBACK_FORMAT   (ft8xx_model ? 0x3020c4UL : 0x1024b4UL)
#define REG_PLAYBACK_FREQ     (ft8xx_model ? 0x3020c0UL : 0x1024b0UL)
#define REG_PLAYBACK_LENGTH   (ft8xx_model ? 0x3020b8UL : 0x1024a8UL)
#define REG_PLAYBACK_LOOP     (ft8xx_model ? 0x3020c8UL : 0x1024b8UL)
#define REG_PLAYBACK_PLAY     (ft8xx_model ? 0x3020ccUL : 0x1024bcUL)
#define REG_PLAYBACK_READPTR  (ft8xx_model ? 0x3020bcUL : 0x1024acUL)
#define REG_PLAYBACK_START    (ft8xx_model ? 0x3020b4UL : 0x1024a4UL)
#define REG_PWM_DUTY          (ft8xx_model ? 0x3020d4UL : 0x1024c4UL)
#define REG_PWM_HZ            (ft8xx_model ? 0x3020d0UL : 0x1024c0UL)
#define REG_ROTATE            (ft8xx_model ? 0x302058UL : 0x102454UL)
#define REG_SOUND             (ft8xx_model ? 0x302088UL : 0x102484UL)
#define REG_SWIZZLE           (ft8xx_model ? 0x302064UL : 0x102460UL)

#define REG_TAG               (ft8xx_model ? 0x30207cUL : 0x102478UL)
#define REG_TAG_X             (ft8xx_model ? 0x302074UL : 0x102470UL)
#define REG_TAG_Y             (ft8xx_model ? 0x302078UL : 0x102474UL)

#define REG_TOUCH_ADC_MODE    (ft8xx_model ? 0x302108UL : 0x1024f4UL)
#define REG_TOUCH_CHARGE      (ft8xx_model ? 0x30210cUL : 0x1024f8UL)
#define REG_TOUCH_DIRECT_XY   (ft8xx_model ? 0x30218cUL : 0x102574UL)
#define REG_TOUCH_DIRECT_Z1Z2 (ft8xx_model ? 0x302190UL : 0x102578UL)
#define REG_TOUCH_MODE        (ft8xx_model ? 0x302104UL : 0x1024f0UL)
#define REG_TOUCH_OVERSAMPLE  (ft8xx_model ? 0x302114UL : 0x102500UL)
#define REG_TOUCH_RAW_XY      (ft8xx_model ? 0x30211cUL : 0x102508UL)
#define REG_TOUCH_RZ          (ft8xx_model ? 0x302120UL : 0x10250cUL)
#define REG_TOUCH_RZTHRESH    (ft8xx_model ? 0x302118UL : 0x102504UL)
#define REG_TOUCH_SCREEN_XY   (ft8xx_model ? 0x302124UL : 0x102510UL)
#define REG_TOUCH_SETTLE      (ft8xx_model ? 0x302110UL : 0x1024fcUL)
#define REG_TOUCH_TAG         (ft8xx_model ? 0x30212cUL : 0x102518UL)
#define REG_TOUCH_TAG_XY      (ft8xx_model ? 0x302128UL : 0x102514UL)
#define REG_TOUCH_TRANSFORM_A (ft8xx_model ? 0x302150UL : 0x10251cUL)
#define REG_TOUCH_TRANSFORM_B (ft8xx_model ? 0x302154UL : 0x102520UL)
#define REG_TOUCH_TRANSFORM_C (ft8xx_model ? 0x302158UL : 0x102524UL)
#define REG_TOUCH_TRANSFORM_D (ft8xx_model ? 0x30215cUL : 0x102528UL)
#define REG_TOUCH_TRANSFORM_E (ft8xx_model ? 0x302160UL : 0x10252cUL)
#define REG_TOUCH_TRANSFORM_F (ft8xx_model ? 0x302164UL : 0x102530UL)

//FT81xmania
//#define REG_GPIOX              0x30209CUL
#define REG_GPIOX_DIR          0x302098UL
#define REG_TOUCH_CONFIG       0x302168UL


// FT817/18 only registers
#define REG_UNDERRUN     		0x0030260c
#define REG_AH_CYCLE_MAX 		0x00302610
#define REG_PCLK_FREQ    		0x00302614
#define REG_PCLK_2X      		0x00302618
#define REG_ANIM_ACTIVE  		0x0030902C
#define REG_CTOUCH_MODE         0x003104UL
#define REG_CTOUCH_EXTENDED     0x003108UL
// FT817/18 only registers

//FT81xmania

#define REG_TRACKER           (ft8xx_model ? 0x309000UL : 0x109000UL)
#define REG_TRIM              (ft8xx_model ? 0x302180UL : 0x10256cUL)
#define REG_VCYCLE            (ft8xx_model ? 0x302040UL : 0x10243cUL)
#define REG_VOFFSET           (ft8xx_model ? 0x302044UL : 0x102440UL)
#define REG_VOL_PB            (ft8xx_model ? 0x302080UL : 0x10247cUL)
#define REG_VOL_SOUND         (ft8xx_model ? 0x302084UL : 0x102480UL)
#define REG_VSIZE             (ft8xx_model ? 0x302048UL : 0x102444UL)
#define REG_VSYNC0            (ft8xx_model ? 0x30204cUL : 0x102448UL)
#define REG_VSYNC1            (ft8xx_model ? 0x302050UL : 0x10244cUL)
#define FONT_ROOT             (ft8xx_model ? 0x2ffffcUL : 0x0ffffcUL)

// FT81x only registers
#define REG_CMDB_SPACE                       0x302574UL
#define REG_CMDB_WRITE                       0x302578UL
#define REG_MEDIAFIFO_READ                   0x309014UL
#define REG_MEDIAFIFO_WRITE                  0x309018UL

// FT815 only registers
#define REG_FLASH_SIZE                       0x00309024 
#define REG_FLASH_STATUS                     0x003025f0 
#define REG_ADAPTIVE_FRAMERATE               0x0030257c
//#define REG_FRAMES                           0x00302004


#define RED                  2
#define GREEN                3
#define BLUE                 4
#define ALPHA                5

#define VERTEX2II(x, y, handle, cell) \
        ((2UL << 30) | (((x) & 511UL) << 21) | (((y) & 511UL) << 12) | (((handle) & 31) << 7) | (((cell) & 127) << 0))

#define ROM_PIXEL_FF        0xc0400UL

#define WII_A      (1 << 12)
#define WII_B      (1 << 14)
#define WII_SELECT (1 << 4)
#define WII_HOME   (1 << 3)
#define WII_START  (1 << 2)
#define WII_X      (1 << 11)
#define WII_Y      (1 << 13)
#define WII_UP     (1 << 8)
#define WII_DOWN   (1 << 6)
#define WII_LEFT   (1 << 9)
#define WII_RIGHT  (1 << 7)

class Poly {
    int x0, y0, x1, y1;
    int x[8], y[8];
    byte n;
    void restart() {
      n = 0;
      x0 = (1 << GD.vxf) * GD.w;
      x1 = 0;
      y0 = (1 << GD.vxf) * GD.h;
      y1 = 0;
    }
    void perim() {
      for (byte i = 0; i < n; i++)
        GD.Vertex2f(x[i], y[i]);
      GD.Vertex2f(x[0], y[0]);
    }
  public:
    void begin() {
      restart();

      GD.ColorMask(0,0,0,0);
      GD.StencilOp(KEEP, INVERT);
      GD.StencilFunc(ALWAYS, 255, 255);
    }
    void v(int _x, int _y) {
      x0 = min(x0, _x >> GD.vxf);
      x1 = max(x1, _x >> GD.vxf);
      y0 = min(y0, _y >> GD.vxf);
      y1 = max(y1, _y >> GD.vxf);
      x[n] = _x;
      y[n] = _y;
      n++;
    }
    void paint() {
      x0 = max(0, x0);
      y0 = max(0, y0);
      x1 = min((1 << GD.vxf) * GD.w, x1);
      y1 = min((1 << GD.vxf) * GD.h, y1);
      GD.ScissorXY(x0, y0);
      GD.ScissorSize(x1 - x0 + 1, y1 - y0 + 1);
      GD.Begin(EDGE_STRIP_B);
      perim();
    }
    void finish() {
      GD.ColorMask(1,1,1,1);
      GD.StencilFunc(EQUAL, 255, 255);

      GD.Begin(EDGE_STRIP_R);
      GD.Vertex2f(0, 0);
      GD.Vertex2f(0, (1 << GD.vxf) * GD.h);
    }
    void draw() {
      paint();
      finish();
    }
    void outline() {
      GD.Begin(LINE_STRIP);
      perim();
    }
};

//FT81xmania Team
class Streamer {
public:
  void begin(const char *rawsamples,
             uint16_t freq = 44100,   //8000,  // 44100
             byte format =  ADPCM_SAMPLES, // ULAW_SAMPLES,  // ADPCM_SAMPLES
             uint32_t _base = (0x40000UL - 8192), uint16_t size = 8192) {
    GD.__end();


    if (!r.open(rawsamples)) {
      GD.alert();
    } else {
      GD.resume();

      base = _base;
      mask = size - 1;
      wp = 0;

      //for (byte i = 0; i<10; i++) {
	  for (byte i = 10; i; i--){
        feed();
      }
      GD.sample(base, size, freq, format, 1);
    }
  }
  int feed() {
    uint16_t rp = GD.rd32(REG_PLAYBACK_READPTR) - base;
    uint16_t freespace = mask & ((rp - 1) - wp);

    if (freespace >= 512) {  // If freespace is larg than 512, then read file

      byte buf[512];
      GD.__end();
      int32_t c = r.curPosition();
      int32_t p = r.peek();
      int n = r.read(buf,512);

      GD.resume();
      GD.cmd_memwrite(base + wp, 512);
      GD.copyram(buf, 512);
      wp = (wp + 512) & mask;
    }
    uint32_t m = r.fileSize();
    uint32_t p = r.curPosition();
    return p < m;
  }
  void progress(uint16_t &val, uint16_t &range) {
    uint32_t m = r.fileSize();
    uint32_t p = r.curPosition();
    while (m > 0x10000) { // large than 16 bit
      m >>= 1;
      p >>= 1;
    }
    val = p;
    range = m;
  }
private:
 
 //#define SD_FAT_TYPE 1  //para FAT16/FAT32
  //File32 r;
 //#define SD_FAT_TYPE 3  //para FAT16/FAT32 and exFAT
  FsFile r;

  uint32_t base;
  uint16_t mask;
  uint16_t wp;
};
//FT81xmania Team

////////////////////////////////////////////////////////////////////////
//  TileMap: maps made with the "tiled" map editor
////////////////////////////////////////////////////////////////////////

class TileMap {
  uint32_t chunkstart;
  int chunkw, chunkh;
  int stride;
  int bpc;
  byte layers;

public:
  uint16_t w, h;
  void begin(uint32_t loadpoint) {
    GD.finish();
    w      = GD.rd16(loadpoint +  0);
    h      = GD.rd16(loadpoint +  2);
    chunkw = GD.rd16(loadpoint +  4);
    chunkh = GD.rd16(loadpoint +  6);
    stride = GD.rd16(loadpoint +  8);
    layers = GD.rd16(loadpoint + 10);
    bpc = (4 * 16);
    chunkstart = loadpoint + 12;
  }
  void draw(uint16_t x, uint16_t y, uint16_t layermask = ~0) {
    int16_t chunk_x = (x / chunkw);
    int16_t ox0 = -(x % chunkw);
    int16_t chunk_y = (y / chunkh);
    int16_t oy = -(y % chunkh);

    GD.Begin(BITMAPS);
    GD.SaveContext();
    GD.BlendFunc(ONE, ONE_MINUS_SRC_ALPHA);
    while (oy < GD.h) {
      int16_t ox = ox0;
      GD.VertexTranslateY(oy << 4);
      uint32_t pos = chunkstart + (chunk_x + long(stride) * chunk_y) * layers * bpc;
      while (ox < GD.w) {
        GD.VertexTranslateX(ox << 4);
        for (byte layer = 0; layer < layers; layer++)
          if (layermask & (1 << layer))
            GD.cmd_append(pos + bpc * layer, bpc);
        pos += (layers * bpc);
        ox += chunkw;
      }
      oy += chunkh;
      chunk_y++;
    }
    GD.RestoreContext();
  }
  void draw(xy pos) {
    draw(pos.x >> 4, pos.y >> 4);
  }
  uint32_t addr(uint16_t x, uint16_t y, byte layer) {
    int16_t tx = (x / (chunkw >> 2));
    int16_t ty = (y / (chunkh >> 2));
    return
      chunkstart +
      ((tx >> 2) + long(stride) * (ty >> 2)) * layers * bpc +
      (tx & 3) * 4 +
      (ty & 3) * 16 +
      layer * 64;
  }
  int read(uint16_t x, uint16_t y, byte layer) {
    uint32_t op = GD.rd32(addr(x, y, layer));
    if ((op >> 24) == 0x2d)
      return 0;
    else
      return 1 + (op & 2047);
  }
  void write(uint16_t x, uint16_t y, byte layer, int tile) {
    uint32_t op;
    uint32_t a = addr(x, y, layer);
    if (tile == 0)
      op = 0x2d000000UL;
    else
      op = (GD.rd32(a) & ~2047) | ((tile - 1) & 2047);
    GD.wr32(a, op);
  }
  int read(xy pos, byte layer) {
    return read(pos.x >> 4, pos.y >> 4, layer);
  }
  void write(xy pos, byte layer, int tile) {
    write(pos.x >> 4, pos.y >> 4, layer, tile);
  }
};

//FT81xmania Team
class MoviePlayer
{
  uint32_t mf_size, mf_base, wp;

 //#define SD_FAT_TYPE 1  //para FAT16/FAT32
  //File32 r;
 //#define SD_FAT_TYPE 3  //para FAT16/FAT32 and exFAT
  FsFile r;

  void loadsector() {
    byte buf[512];
    GD.__end();

    //int32_t c = r.curPosition();  //en revision comentarlo
    //int32_t p = r.peek();         //en revision comentarlo
    int n = r.read(buf,512);

    GD.resume();
    GD.wr_n(mf_base + wp, buf, 512);
    wp = (wp + 512) & (mf_size - 1);
  }

public:
  int begin(const char *filename) {
    mf_size = 0x40000UL;
    mf_base = 0x100000UL - mf_size;
    GD.__end();
    if (!r.open(filename)) {
      return 0;
    }
    GD.resume();

    wp = 0;
    while (wp < (mf_size - 512)) {
      loadsector();
    }
    GD.cmd_mediafifo(mf_base, mf_size);
    GD.cmd_regwrite(REG_MEDIAFIFO_WRITE, wp);
    GD.finish();

    return 1;
  }
  int service() {
    if (r.peek() == -1) {
      return 0;
    } else {
      uint32_t fullness = (wp - GD.rd32(REG_MEDIAFIFO_READ)) & (mf_size - 1);
      while (fullness < (mf_size - 512)) {
        loadsector();
        fullness += 512;
        GD.wr32(REG_MEDIAFIFO_WRITE, wp);
      }
      return 1;
    }
  }
  void play() {
if(SizeEVE==0){GD.cmd_playvideo(OPT_MEDIAFIFO | OPT_FULLSCREEN | OPT_SOUND);}else{	  
if(SizeEVE==35){GD.cmd_playvideo(OPT_MEDIAFIFO | OPT_FULLSCREEN | OPT_SOUND);}else{
if(SizeEVE==43){GD.cmd_playvideo(OPT_MEDIAFIFO | OPT_FULLSCREEN | OPT_SOUND);}else{
if(SizeEVE==431){GD.cmd_playvideo(OPT_MEDIAFIFO | OPT_FULLSCREEN | OPT_SOUND);}else{
if(SizeEVE==38){GD.cmd_playvideo(OPT_MEDIAFIFO | OPT_FULLSCREEN | OPT_SOUND);}else{
if(SizeEVE==51){GD.cmd_playvideo(OPT_MEDIAFIFO | OPT_FULLSCREEN | OPT_SOUND);}else{ 
//if(SizeEVE==5){GD.cmd_playvideo(OPT_MEDIAFIFO | OPT_FULLSCREEN | OPT_SOUND);}else{
if(SizeEVE==52){GD.cmd_playvideo(OPT_MEDIAFIFO | OPT_FULLSCREEN | OPT_SOUND);}else{ 
if(SizeEVE==434){GD.cmd_playvideo(OPT_MEDIAFIFO | OPT_SOUND);}else{ 
if(SizeEVE==54){GD.cmd_playvideo(OPT_MEDIAFIFO | OPT_SOUND);}else{ 
if(SizeEVE==74){GD.cmd_playvideo(OPT_MEDIAFIFO | OPT_SOUND);}else{ 
if(SizeEVE==71){GD.cmd_playvideo(OPT_MEDIAFIFO | OPT_FULLSCREEN | OPT_SOUND);}else{
GD.cmd_playvideo(OPT_MEDIAFIFO | OPT_SOUND);
     }
    }
   }
  }
 }
//}
}
}
}
}
}
}
    
GD.flush();
    while (service())
      ;
    GD.cmd_memcpy(0, 0, 4);
    GD.finish();
  }
};
//FT81xmania Team

#if defined(ARDUINO_ARCH_STM32) || defined(TEENSYDUINO)
#undef PROGMEM
#define PROGMEM
#endif

#endif