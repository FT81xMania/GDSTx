char Board[50];
int ClaveBoard;

void IDEMCU()
{
     ClaveBoard=0;
     sprintf(Board, "MCU: None               (%d)", ClaveBoard);

  #if defined(ARDUINO_ARCH_STM32)
     ClaveBoard=1;
     sprintf(Board, "MCU(%d): STM32 Nucleo-F767ZI", ClaveBoard);
     if (STM32_CPU==4070){sprintf(Board, "MCU: STM32 F407 M4DEMO_SD"); MCUID=4070;}
     if (STM32_CPU==4071){sprintf(Board, "MCU: STM32FX_SDIO"); MCUID=4071;}
     if (STM32_CPU==4073){sprintf(Board, "MCU: M4DEMO/407VG"); MCUID=4073;}
     if (STM32_CPU==411){sprintf(Board, "MCU: STM32 F411CE"); MCUID=411;}
     if (STM32_CPU==429){sprintf(Board, "MCU: STM32 F429I-DISCO"); MCUID=429;}
     if (STM32_CPU==446){sprintf(Board, "MCU: Black F446RE"); MCUID=446;}
     if (STM32_CPU==746){sprintf(Board, "MCU: STM32 Core7XXI (Danieleff Core)"); MCUID=746;}
     if (STM32_CPU==767){sprintf(Board, "MCU: STM32 Nucleo-F767ZI(Danieleff Core)"); MCUID=767;}
     if (STM32_CPU==7670)
        {
       //   if(H743==0){sprintf(Board, "MCU: STM32 Nucleo-F767ZI(Official Core)"); MCUID=7670;}
       //   if(H743==1){sprintf(Board, "MCU: STM32 Nucleo-H743ZI(Official Core)"); MCUID=7670;}
        }
     
  #endif

#ifdef TEENSYDUINO
     ClaveBoard=2;
      #if defined(__IMXRT1052__)
       sprintf(Board, "MCU: Teensy 4 beta");
      #endif
      
     #if defined(__IMXRT1062__)
       #if defined(ARDUINO_TEENSY40)
        sprintf(Board, "MCU: Teensy 4");
       #endif

       #if defined(ARDUINO_TEENSY41)
        sprintf(Board, "MCU: Teensy 4.1");
       #endif
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

  #if !defined(TEENSYDUINO)&& !defined(ESP32)&& !defined(__DUE__)&& !defined(ESP8266)&& !defined(ARDUINO_ARCH_STM32)&& defined(ARDUINO)
     ClaveBoard=6;
     sprintf(Board, "MCU: Arduino MEGA/UNO");
  #endif
}
