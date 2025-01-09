#include <EEPROM.h>
#include <GDSTx.h>

char TxT[50];
int VTlimpio[50];
int VTlleno[50];

int Test =0;

void setup() {
  Serial.begin(9600);
  //while (!Serial){}

  for ( unsigned int i = 0 ; i < 25 ; i++ )
  {
   EEPROM.write(i, 0);
   VTlimpio[i]=EEPROM.read(i);
   Serial.print(i); Serial.print(": "); Serial.println(VTlimpio[i]); 
  }

  WriteVector();
  
  GD.begin();
  
MP();
} void loop(){}

void MP()
{

  for ( unsigned int i = 0 ; i < 25 ; i++ )
  {
   VTlleno[i]=EEPROM.read(i);
   Serial.print(i); Serial.print(": "); Serial.println(VTlleno[i]); 
  }

while(1)
 {
  GD.ClearColorRGB(0x00aa00); 
  GD.Clear();
  GD.get_inputs(); 
  GD.SaveContext();

  for ( unsigned int i = 0 ; i < 25 ; i++ )
  {
    sprintf(TxT, "Adress %d: %d", i,VTlleno[i]);
    GD.cmd_text(60+200, 10+18*i, 28, OPT_CENTER, TxT);
  }  
  GD.RestoreContext();

  GD.SaveContext();

    GD.cmd_fgcolor(0x9025fa);   GD.ColorRGB(0xffffff);  
    sprintf(TxT, "%d", Test);
    GD.Tag(1);    GD.cmd_button(GD.w - 100, 150, 45, 55, 26, 0,  TxT);    GD.Tag(255);

   if (GD.inputs.tag==1)
       {
         Test = Test + 1;
       }    

    GD.cmd_fgcolor(0x9025fa);   GD.ColorRGB(0xffffff);  
    sprintf(TxT, "%d", Test);
    GD.Tag(2);    GD.cmd_button(5, 5, 45, 55, 26, 0,  TxT);    GD.Tag(255);

   if (GD.inputs.tag==2)
       {
         Test = Test - 1;
       }        

    GD.cmd_fgcolor(0x9025fa);   GD.ColorRGB(0xffffff);  
    sprintf(TxT, "%d", Test);
    GD.Tag(3);    GD.cmd_button((GD.w/2)-75, GD.h-60, 45, 55, 26, 0,  TxT);    GD.Tag(255);

   if (GD.inputs.tag==3)
       {
         Test = Test + 2;
       }        
  
  GD.RestoreContext();  

  GD.swap();
 }
}
