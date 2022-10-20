//#include <GD23ZUTX.h>
#include <GDSTx.h>

# define PAINT_ALPHA() GD.BlendFunc(ONE, ONE_MINUS_SRC_ALPHA)
# define CLEAR_ALPHA() GD.BlendFunc(ZERO, ONE_MINUS_SRC_ALPHA)

int picked;
int Floor;
int sz = 35; // button size in pixels
int delta=sz;

//                         0         1         2         3         4         5           6             7            8        9
char FondoJPG[10][15]={"tree.jpg","Ab1.jpg","Ab2.jpg","Ab3.jpg","Ab4.jpg","Ab5.jpg", "Fly.jpg","Lake1.jpg","Fondo010.jpg","Fn1.jpg" };
int BaseJPG = 9;

unsigned long start;

char TxT[40], Board[40];
int ClaveBoard=0;  

void setup() {
   
   GD.begin();
   //GD.cmd_setrotate(1);
   
     ClaveBoard=0;
     sprintf(Board, "MCU: None               (%d)", ClaveBoard);

  #if defined(ARDUINO_ARCH_STM32)
     ClaveBoard=1;
     sprintf(Board, "MCU(%d): STM32 Nucleo-F767ZI", ClaveBoard);
     if (STM32_CPU==4070){sprintf(Board, "MCU: STM32 F407 M4DEMO_SD"); MCUID=4070;}
     if (STM32_CPU==4071){sprintf(Board, "MCU: STM32FX_SDIO"); MCUID=4071;}
     if (STM32_CPU==429){sprintf(Board, "MCU: STM32 F429I-DISCO"); MCUID=429;}
     if (STM32_CPU==767){sprintf(Board, "MCU: STM32 Nucleo-F767ZI(Danieleff Core)"); MCUID=767;}
     if (STM32_CPU==7670)
        {
          if(H743==0){sprintf(Board, "MCU: STM32 Nucleo-F767ZI(Official Core)"); MCUID=7670;}
          if(H743==1){sprintf(Board, "MCU: STM32 Nucleo-H743ZI(Official Core)"); MCUID=7670;}
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
   
  tecladotransp();
}
void loop(){}  //Nothing to do here!

void tecladotransp()
{
  ImagenJPG(0);

  while(1)
  {
    GD.Clear();
    GD.get_inputs();
    GD.ColorMask(1, 1, 1, 0);
    GD.Begin(BITMAPS);
    
    GD.ColorA(150);
      GD.Vertex2ii(0, 0);
    GD.ColorA(255);

    GD.SaveContext();
      GD.cmd_romfont(1,34);  
      GD.ColorRGB(0xffffff);  GD.cmd_number(750, 430, 1, OPT_CENTER, Floor);
    GD.RestoreContext();

       //PieTX();            

    GD.SaveContext();
     sprintf(TxT, "F_CPU= %d MHz", F_CPU/1000000);
     GD.ColorRGB(0, 175, 0); 
     
     GD.cmd_text(0, 0, 26, 0, Board); 
     GD.cmd_text(0, 16, 26, 0, TxT);  

     GD.RestoreContext();

    GD.ColorMask(0, 0, 0, 1);

    int espacio = 4.444*sz;
    
    int x0 = 200, x1 = x0+espacio, x2 = x0+espacio*2;
    int y0 = 97, y1 = y0+espacio, y2 = y0+espacio*2;
    
    button(x0, y0, 1);  button(x1, y0, 2);  button(x2, y0, 3);
    button(x0, y1, 4);  button(x1, y1, 5);  button(x2, y1, 6);
    button(x0, y2, 7);  button(x1, y2, 8);  button(x2, y2, 9);

    GD.ColorMask(1, 1, 1, 1);
      //GD.ColorRGB(0x00ff00);
      GD.ColorRGB(0x0022ff);
    GD.BlendFunc(DST_ALPHA, ONE_MINUS_DST_ALPHA);

    GD.Begin(RECTS);
    GD.Vertex2f(0*16, 0*16); GD.Vertex2f(800*16, 480*16);  

         

    GD.SaveContext();
      CLEAR_ALPHA();
      GD.ColorA(0);
      GD.Tag(1); GD.Vertex2f((x0-delta)*16, (y0-delta)*16); GD.Vertex2f((x0+delta)*16, (y0+delta)*16); GD.Tag(255);
      GD.Tag(2); GD.Vertex2f((x1-delta)*16, (y0-delta)*16); GD.Vertex2f((x1+delta)*16, (y0+delta)*16); GD.Tag(255);
      GD.Tag(3); GD.Vertex2f((x2-delta)*16, (y0-delta)*16); GD.Vertex2f((x2+delta)*16, (y0+delta)*16); GD.Tag(255);

      GD.Tag(4); GD.Vertex2f((x0-delta)*16, (y1-delta)*16); GD.Vertex2f((x0+delta)*16, (y1+delta)*16); GD.Tag(255);
      GD.Tag(5); GD.Vertex2f((x1-delta)*16, (y1-delta)*16); GD.Vertex2f((x1+delta)*16, (y1+delta)*16); GD.Tag(255);
      GD.Tag(6); GD.Vertex2f((x2-delta)*16, (y1-delta)*16); GD.Vertex2f((x2+delta)*16, (y1+delta)*16); GD.Tag(255);

      GD.Tag(7); GD.Vertex2f((x0-delta)*16, (y2-delta)*16); GD.Vertex2f((x0+delta)*16, (y2+delta)*16); GD.Tag(255);
      GD.Tag(8); GD.Vertex2f((x1-delta)*16, (y2-delta)*16); GD.Vertex2f((x1+delta)*16, (y2+delta)*16); GD.Tag(255);
      GD.Tag(9); GD.Vertex2f((x2-delta)*16, (y2-delta)*16); GD.Vertex2f((x2+delta)*16, (y2+delta)*16); GD.Tag(255);
      GD.ColorA(255);
    GD.RestoreContext();

    picked = GD.inputs.tag;   
     if ((picked>=1) && (picked<=9)) 
         { 
           delay(135);
           
           if (picked>BaseJPG){picked=0;}          
           ImagenJPG(picked);
           
          // Serial.println(picked);
           Floor = picked;
         }

   
    GD.swap();
  }
}  

static void button(int x, int y, byte label)
{
  PAINT_ALPHA();
  GD.Begin(RECTS);
  GD.LineWidth(16 * 20);  GD.Vertex2f((x - sz)*16, (y - sz)*16);  GD.Vertex2f((x + sz)*16, (y + sz)*16);
  CLEAR_ALPHA();
  GD.ColorA(255);  //0=color solido, 255=100% transparente
  GD.LineWidth(16 * 15);  GD.Vertex2f((x - sz)*16, (y - sz)*16); GD.Vertex2f((x + sz)*16, (y + sz)*16);
  GD.ColorA(0xff);
  PAINT_ALPHA();
  GD.cmd_number(x, y, 31, OPT_CENTER, label);
}
