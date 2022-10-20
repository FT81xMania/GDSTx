#include <Wire.h>
#include <GDSTx.h>

#include "Kuku.h"    //Asset0

//Péndulo
int Centro=250/2;   //pendulo 3.png, 250x250 px, Centro=250/2
float AnguloG=0;  //péndulo vertical
float avance, rapidez=1.5;
//Péndulo

#define DS3231_I2C_ADDRESS 0x68
byte second, minute, hour, dayOfWeek, dayOfMonth, month, year; 
// Convert normal decimal numbers to binary coded decimal
byte decToBcd(byte val)
{
  return( (val/10*16) + (val%10) );
}
// Convert binary coded decimal to normal decimal numbers
byte bcdToDec(byte val)
{
  return( (val/16*10) + (val%16) );
}

void setup()
{
  Wire.begin();
  GD.begin();
  LOAD_ASSETS0();  
}

void BaseX()
{
  GD.Clear();
  GD.Begin(BITMAPS);
    GD.Vertex2ii(0, 0, 0);    //cuco
    GD.Vertex2ii(0, 100, 1);  //reloj
    GD.Vertex2ii(0, 200, 2);  //péndulo
  GD.swap();
}

float dato;

void loop()
{
  readDS3231time(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month,&year); 
  GD.ClearColorRGB(0x202020);
  GD.Clear();

   GD.SaveContext();
     GD.cmd_fgcolor(0x00c040);
     GD.cmd_gradcolor(0x000000);
     GD.cmd_button(402, 32, 76, 56, 26, 0, "custom" );
     GD.cmd_coldstart();
     GD.cmd_button(482, 32, 76, 56, 26, 0, "default");
   GD.SaveContext();
     
   

  GD.SaveContext();
  GD.Begin(BITMAPS);
    avance = 1 + dato;
    dato = dato + rapidez;
    if((AnguloG+avance)>=15){rapidez=-1.5; GD.play(NOTCH);}
    if((AnguloG+avance)<=-15){rapidez=1.5; }
    rotate_Center(DEGREES(AnguloG+avance), Centro);
    GD.cmd_setmatrix();
    GD.Vertex2ii(32, 125, 2);
    GD.cmd_loadidentity();
  GD.End();
  GD.RestoreContext();

  GD.SaveContext();
   GD.Begin(BITMAPS);
   GD.Vertex2ii(50, 50, 1);
  GD.RestoreContext();   

  GD.cmd_clock(151,184,30,OPT_NOTICKS,hour,minute,second,0);

  PieTX();
  GD.swap();
}

void setDS3231time(byte second, byte minute, byte hour, byte dayOfWeek, byte
dayOfMonth, byte month, byte year)
{
  // sets time and date data to DS3231
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0); // set next input to start at the seconds register
  Wire.write(decToBcd(second)); // set seconds
  Wire.write(decToBcd(minute)); // set minutes
  Wire.write(decToBcd(hour)); // set hours
  Wire.write(decToBcd(dayOfWeek)); // set day of week (1=Sunday, 7=Saturday)
  Wire.write(decToBcd(dayOfMonth)); // set date (1 to 31)
  Wire.write(decToBcd(month)); // set month
  Wire.write(decToBcd(year)); // set year (0 to 99)
  Wire.endTransmission();
}

void readDS3231time(byte *second,
byte *minute,
byte *hour,
byte *dayOfWeek,
byte *dayOfMonth,
byte *month,
byte *year)
{
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0); // set DS3231 register pointer to 00h
  Wire.endTransmission();
  Wire.requestFrom(DS3231_I2C_ADDRESS, 7);
  // request seven bytes of data from DS3231 starting from register 00h
  *second = bcdToDec(Wire.read() & 0x7f);
  *minute = bcdToDec(Wire.read());
  *hour = bcdToDec(Wire.read() & 0x3f);
  *dayOfWeek = bcdToDec(Wire.read());
  *dayOfMonth = bcdToDec(Wire.read());
  *month = bcdToDec(Wire.read());
  *year = bcdToDec(Wire.read());
}

static void rotate_Center(float a, int CXY)
{
  GD.cmd_translate(F16(CXY),F16(CXY));
  GD.cmd_rotate(a);
  GD.cmd_translate(F16(-CXY), F16(-CXY));
}
