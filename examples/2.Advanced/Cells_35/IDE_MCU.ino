char Board[40];
int ClaveBoard;

void IDEMCU()
{
     ClaveBoard=0;
     sprintf(Board, "MCU: None               (%d)", ClaveBoard);

  #if defined(ARDUINO_ARCH_STM32)
     ClaveBoard=1;
     //sprintf(Board, "MCU(%d): STM32 Nucleo-F767ZI", ClaveBoard);
     //if (STM32_CPU==407){sprintf(Board, "MCU: STM32 F407 M4DEMO"); MCUID=407;}
     if (STM32_CPU==4070){sprintf(Board, "MCU: STM32 F407 M4DEMO_SD"); MCUID=4070;}
     if (STM32_CPU==4071){sprintf(Board, "MCU: STM32 F407 M4DEMO_SDIO"); MCUID=4071;}
     if (STM32_CPU==4073){sprintf(Board, "MCU: M4DEMO/407VG"); MCUID=4073;}
     if (STM32_CPU==429){sprintf(Board, "MCU: STM32 F49I-DISCO"); MCUID=429;}
     if (STM32_CPU==446){sprintf(Board, "MCU: Black F446RE"); MCUID=446;}
     if (STM32_CPU==746){sprintf(Board, "MCU: STM32 Core7XXI"); MCUID=746;}
     if (STM32_CPU==767){sprintf(Board, "MCU: STM32 Nucleo-F767ZI(Danieleff Core)"); MCUID=767;}
     if (STM32_CPU==7670)
        {
          if(H743==0){sprintf(Board, "MCU: STM32 Nucleo-F767ZI(Official Core)"); MCUID=7670;}
          if(H743==1){sprintf(Board, "MCU: STM32 Nucleo-H743ZI(Official Core)"); MCUID=7670;}
        }
      if (STM32_CPU==1030){sprintf(Board, "MCU: STM32 F103XX(Official Core)");}
      if (STM32_CPU==103){sprintf(Board, "MCU: STM32 F103XX(Danieleff Core)");}
     
  #endif

  #ifdef TEENSYDUINO
     ClaveBoard=2;
    #if defined(__IMXRT1052__) || defined(__IMXRT1062__)
      sprintf(Board, "MCU: Teensy 4");
    #else
      sprintf(Board, "MCU: Teensy 3.X");
    #endif
  #endif

  #ifdef __DUE__
     ClaveBoard=3;
     sprintf(Board, "MCU: Arduino Due");
  #endif

  #ifdef ESP8266
     ClaveBoard=4;
     sprintf(Board, "MCU: ESP8266");
  #endif

  #if defined(ESP32)
     ClaveBoard=5;
     sprintf(Board, "MCU: ESP32");
  #endif

  #if defined(ARDUINO_ARCH_RP2040)
     ClaveBoard=6;
     sprintf(Board, "MCU: R-Pi Pico");
  #endif
  
  #if !defined(TEENSYDUINO)&& !defined(ESP32)&& !defined(__DUE__)&& !defined(ESP8266)&& !defined(ARDUINO_ARCH_STM32)&& !defined(ARDUINO_ARCH_RP2040)&& defined(ARDUINO)
     ClaveBoard=7;
     sprintf(Board, "MCU: Arduino MEGA/UNO");
  #endif
}

char TXP[50];

void Parametros()
{
  GD.SaveContext();
   sprintf(TXP,"F_CPU: %d MHz", (F_CPU/1000000));  
   GD.ColorRGB(0x00ff00); GD.cmd_text((GD.w/2)-40, 3, 20, 0, TXP);
   GD.ColorRGB(0xffff00); GD.cmd_text(3, 3, 20, 0, Board);

   GD.ColorRGB(0x888800); GD.cmd_text(40, (GD.h)-10, 20, OPT_CENTER, "FT81xmania Team");

  GD.RestoreContext();
}
