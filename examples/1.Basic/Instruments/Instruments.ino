#include <GDSTx.h>

/*
 * #define SILENCE              0x00

#define SQUAREWAVE           0x01
#define SINEWAVE             0x02
#define SAWTOOTH             0x03
#define TRIANGLE             0x04

#define BEEPING              0x05
#define ALARM                0x06
#define WARBLE               0x07
#define CAROUSEL             0x08

#define PIPS(n)              (0x0f + (n))

Instrumentos
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
Instrumentos

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

 */

void setup()
{
  //GD.begin();
  GD.begin(GD_STORAGE);
  GD.play(SILENCE);
 // GD.cmd_setrotate(0);
  Teclado();
}

int XInicial=32, YInicial=125, Sep=7, Espesor=60, Largo=275;

uint16_t Instrumento = 0x40;
int ID=0, espera=75;

void loop(){}

void Teclado()
{
  while(1)
  {
  
  GD.ClearColorRGB(0x000020);
  GD.Clear();
  GD.get_inputs();

  GD.cmd_fgcolor(0x909090);
  GD.Tag(1);  GD.cmd_button(XInicial + 0*Espesor + 0*Sep, YInicial, Espesor, Largo, 26, 0,  " "); GD.Tag(255); 
  if (GD.inputs.tag==1)
     {GD.cmd_fgcolor(0x505050); GD.cmd_button(XInicial + 0*Espesor + 0*Sep, YInicial, Espesor, Largo, 26, 0,  " ");  GD.play(Instrumento, 65);  delay (espera);}

  GD.cmd_fgcolor(0x909090);
  GD.Tag(2);  GD.cmd_button(XInicial + 1*Espesor + 1*Sep, YInicial, Espesor, Largo, 26, 0,  " "); GD.Tag(255); 
  if (GD.inputs.tag==2)
     {GD.cmd_fgcolor(0x505050); GD.cmd_button(XInicial + 1*Espesor + 1*Sep, YInicial, Espesor, Largo, 26, 0,  " ");  GD.play(Instrumento, 68);  delay (espera);}

  GD.cmd_fgcolor(0x909090);
  GD.Tag(3);  GD.cmd_button(XInicial + 2*Espesor + 2*Sep, YInicial, Espesor, Largo, 26, 0,  " "); GD.Tag(255); 
  if (GD.inputs.tag==3)
     {GD.cmd_fgcolor(0x505050); GD.cmd_button(XInicial + 2*Espesor + 2*Sep, YInicial, Espesor, Largo, 26, 0,  " ");  GD.play(Instrumento, 71);  delay (espera);}

  GD.cmd_fgcolor(0x909090);
  GD.Tag(4);  GD.cmd_button(XInicial + 3*Espesor + 3*Sep, YInicial, Espesor, Largo, 26, 0,  " "); GD.Tag(255); 
  if (GD.inputs.tag==4)
     {GD.cmd_fgcolor(0x505050); GD.cmd_button(XInicial + 3*Espesor + 3*Sep, YInicial, Espesor, Largo, 26, 0,  " ");  GD.play(Instrumento, 74);  delay (espera);}

  GD.cmd_fgcolor(0x909090);
  GD.Tag(5);  GD.cmd_button(XInicial + 4*Espesor + 4*Sep, YInicial, Espesor, Largo, 26, 0,  " "); GD.Tag(255); 
  if (GD.inputs.tag==5)
     {GD.cmd_fgcolor(0x505050); GD.cmd_button(XInicial + 4*Espesor + 4*Sep, YInicial, Espesor, Largo, 26, 0,  " ");  GD.play(Instrumento, 77);  delay (espera);}

  GD.cmd_fgcolor(0x909090);
  GD.Tag(6);  GD.cmd_button(XInicial + 5*Espesor + 5*Sep, YInicial, Espesor, Largo, 26, 0,  " "); GD.Tag(255); 
  if (GD.inputs.tag==6)
     {GD.cmd_fgcolor(0x505050); GD.cmd_button(XInicial + 5*Espesor + 5*Sep, YInicial, Espesor, Largo, 26, 0,  " ");  GD.play(Instrumento, 80);  delay (espera);}

  GD.cmd_fgcolor(0x909090);
  GD.Tag(7);  GD.cmd_button(XInicial + 6*Espesor + 6*Sep, YInicial, Espesor, Largo, 26, 0,  " "); GD.Tag(255); 
  if (GD.inputs.tag==7)
     {GD.cmd_fgcolor(0x505050); GD.cmd_button(XInicial + 6*Espesor + 6*Sep, YInicial, Espesor, Largo, 26, 0,  " ");  GD.play(Instrumento, 83);  delay (espera);}

  GD.cmd_fgcolor(0x909090);
  GD.Tag(8);  GD.cmd_button(XInicial + 7*Espesor + 7*Sep, YInicial, Espesor, Largo, 26, 0,  " "); GD.Tag(255); 
  if (GD.inputs.tag==8)
     {GD.cmd_fgcolor(0x505050); GD.cmd_button(XInicial + 7*Espesor + 7*Sep, YInicial, Espesor, Largo, 26, 0,  " ");  GD.play(Instrumento, 86);  delay (espera);}

  GD.cmd_fgcolor(0x909090);
  GD.Tag(9);  GD.cmd_button(XInicial + 8*Espesor + 8*Sep, YInicial, Espesor, Largo, 26, 0,  " "); GD.Tag(255); 
  if (GD.inputs.tag==9)
     {GD.cmd_fgcolor(0x505050); GD.cmd_button(XInicial + 8*Espesor + 8*Sep, YInicial, Espesor, Largo, 26, 0,  " ");  GD.play(Instrumento, 89);  delay (espera);}

  GD.cmd_fgcolor(0x909090);
  GD.Tag(10);  GD.cmd_button(XInicial + 9*Espesor + 9*Sep, YInicial, Espesor, Largo, 26, 0,  " "); GD.Tag(255); 
  if (GD.inputs.tag==10)
     {GD.cmd_fgcolor(0x505050); GD.cmd_button(XInicial + 9*Espesor + 9*Sep, YInicial, Espesor, Largo, 26, 0,  " ");  GD.play(Instrumento, 91);  delay (espera);}

  GD.cmd_fgcolor(0x909090);
  GD.Tag(11);  GD.cmd_button(XInicial + 10*Espesor + 10*Sep, YInicial, Espesor, Largo, 26, 0,  " "); GD.Tag(255); 
  if (GD.inputs.tag==11)
     {GD.cmd_fgcolor(0x505050); GD.cmd_button(XInicial + 10*Espesor + 10*Sep, YInicial, Espesor, Largo, 26, 0,  " ");  GD.play(Instrumento, 94);  delay (espera);}


  GD.cmd_fgcolor(0x000095);
  GD.Tag(12);  GD.cmd_button(XInicial, 10, 100, 60, 26, 0,  " "); GD.Tag(255); 
  if (GD.inputs.tag==12)
     {GD.cmd_fgcolor(0x505050); GD.cmd_button(XInicial, 10, 100, 60, 26, 0,  " "); ID = ID + 1;  if (ID>=11){ID=0;} delay (150);}

  GD.cmd_fgcolor(0x450000);
  GD.Tag(13);  GD.cmd_button(XInicial+100+10, 10, 100, 60, 26, 0,  "MUTE"); GD.Tag(255); 
  if (GD.inputs.tag==13)
     {GD.cmd_fgcolor(0x505050); GD.cmd_button(XInicial+100+10, 10, 100, 60, 26, 0,  "MUTE"); ID = 10; delay (150);}

   if (ID==0){Instrumento=0x40; GD.cmd_text(80, 40, 26, OPT_CENTER, "HARP");}
   if (ID==1){Instrumento=0x41; GD.cmd_text(80, 40, 26, OPT_CENTER, "XYLOPHONE");}
   if (ID==2){Instrumento=0x42; GD.cmd_text(80, 40, 26, OPT_CENTER, "TUBA");}
   if (ID==3){Instrumento=0x43; GD.cmd_text(80, 40, 26, OPT_CENTER, "GLOCKENSPIEL");}
   if (ID==4){Instrumento=0x44; GD.cmd_text(80, 40, 26, OPT_CENTER, "ORGAN");}
   if (ID==5){Instrumento=0x45; GD.cmd_text(80, 40, 26, OPT_CENTER, "TRUMPET");}
   if (ID==6){Instrumento=0x46; GD.cmd_text(80, 40, 26, OPT_CENTER, "PIANO");}
   if (ID==7){Instrumento=0x47; GD.cmd_text(80, 40, 26, OPT_CENTER, "CHIMES");}
   if (ID==8){Instrumento=0x48; GD.cmd_text(80, 40, 26, OPT_CENTER, "MUSICBOX");}
   if (ID==9){Instrumento=0x49; GD.cmd_text(80, 40, 26, OPT_CENTER, "BELL");}
   if (ID==10){Instrumento=0x00; GD.cmd_text(80, 40, 26, OPT_CENTER, "MUTE");}

  GD.swap();
  }
}
