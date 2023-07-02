# History
In  memory of my brother lightcalamar.

"We are an enthusiastic team of screens based on [FTDI chip](http://www.ftdichip.com/EVE.htm). We like programming and share our advances. 
We have reached this goal, our only interest is to give the opportunity to operate this library to multiple platforms of MCU's in the market. 
Wait for you to enjoy the codes, of our, your time.
Two friends, in Mexico and another in Spain, the water or the puddle does not scare us ...
Last month of May, a member of the Team, we left. We move on.
Without any interest, we publish this library altruistically."

1. Library based on the library created by [James Bowman](https://github.com/jamesbowman/gd2-lib)
2. Library based on [lightcalamar GD23STM32_F103x](https://github.com/lightcalamar/GD23STM32_F103x) > programmed and modified by [@TFTLCDCyg]
3. Library based on [STM32_GD2](https://github.com/nopnop2002/STM32_GD2) user **@nopnop2002** this [link](http://stm32duino.com/viewtopic.php?f=9&t=3466#p44477)
4. Configured to work with the most recient version of SdFat library

# Teensy support 
* Teensy 4.1	
* Teensy 4
* Teensy 3.5 and Teensy 3.6

![FT81xMania](NHD43.jpg?raw=true "GDSTx")
NHD 5" FT813 + Teensy 4.1

![FT81xMania](NHD_header-20pin.png?raw=true "GDSTx")
Wiring

# STM32F support
* STM32F103x (F103C8, M3-DEMO)
* STM32F407x (BLACK-F407VG, M4-DEMO)
* BLACK STM32F411 
* STM32F429 (Discovery board)
* Core7XXI (STM32F746)
* Nucleo STM32F767

# Software requirement
* For STM32 boards: Donwload and [use the Core STM32GENERIC by danieleff](https://github.com/danieleff/STM32GENERIC)
* Arduino IDE 1.8.9 for best results
* Teensyduino 1.57
* [SdFat library](https://github.com/greiman/SdFat)

## For Windows
1. Unzip library copy and paste path of IDE arduino-1.8.9\libraries\ or Documents\Arduino\libraries\
2. Install Arduino Zero or Arduino Sam from the board manager for the arm-none-eabi-gcc compiler
3. Download the [GNU ARM Embedded Toolchain](https://developer.arm.com/open-source/gnu-toolchain/gnu-rm/downloads).
   Recommended use GCC ver 5.4.1-2016q2 (or superior),Change compiler.path in [platform.txt](https://github.com/danieleff/STM32GENERIC/blob/master/STM32/platform.txt#L21) 
   to point to that you downloaded.   
   
# Extra libraries    
* AT24C32 library to calibrate the FT81x screens in STM32Fx we need an external EEPROM. 
* Library SdFat for multimedia support

# Tips
* These screens have a problem, being the length of the SPI BUS cables. The purpose is to be very short, between 7 and 10 mm. Also a tip is to use on this same SPI BUS some pull-up resistors. 

# Where do I find information about programming EVE2 of FTDI?
* [Support Oficial FTDI-Chip](http://www.ftdichip.com/Support/SoftwareExamples/FT800_Projects.htm#FT8xx_Selecting%20an%20LCD%20Display) Complete list of examples and documentation of FTDI-Chip
* [Migration FT80x to FT81x](http://www.ftdichip.com/Support/Documents/AppNotes/AN_390%20FT80x%20To%20FT81x%20Migration%20Guide.pdf) Documentation PDF.
* [FT81x High resolution](http://brtchip.com/wp-content/uploads/Support/Documentation/Datasheets/ICs/EVE/DS_FT81x.pdf), This a PDF documentation for FT81x screens programming guide.

# Useful links
* Library GD2 by [James Bowman](https://github.com/jamesbowman/gd2-lib)
* Core for STM32GENERIC by [Danieleff](https://github.com/danieleff/STM32GENERIC), installation for IDE Arduino with STM32 boards
* Repository by [Amthony Di Girolamo](https://github.com/AnthonyDiGirolamo/gd2-lib-sdfat-testing)

# Acknowledgments
- James Bowman for your support and constant teachings and great programming effort
- Infinite thanks to **@nopnop2002** [STM32_GD2 Library on GitHub](https://github.com/nopnop2002/STM32_GD2)
- Hat tip to anyone who's code was used
- Inspiration
- More time frustation...
- Etc...
- Our friends of Matrix Orbital Henry and Daniel

# Test video file
http://www.mediafire.com/file/1fo25jc3605hmm9/oficial.avi/file

#include <GDSTx.h>

void setup(){

  GD.begin();
  
}

void loop(){

  MoviePlayer mp;
  
  mp.begin("oficial.avi");
  
  mp.play();
  
}
