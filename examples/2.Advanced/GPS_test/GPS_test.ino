#include <GDSTx.h>

int SiZeX=800, SiZeY=399;
                    //    0             1              2
char MapJPG[10][22]={"Pari.jpg", "Vtm_17b.jpg", "Dubai17_c.jpg"};
int Mbase=                1;

int TestGPS=1;

char doubleTXT[40];
double Lat=0, Long=0;   //Paricutín, Pari.jpg
//double Lat=19.493523, Long=-102.248125;   //Paricutín, Pari.jpg
//double Lat=10.490665, Long=104.605832;     //Vietnam Opción 1
//Lat= 25.129932, Long= 55.117630;     //Dubai17_c.jpg   Dubai-1
//Lat= 25.125260, Long= 55.129636;     //Dubai17_c.jpg   Dubai-2



double MovPX=0, MovPY=0;
double DeltaPX, PitchX, CambioPX;
double DeltaPY, PitchY, CambioPY;

double MapaX0[10], MapaX1[10];
double MapaY0[10], MapaY1[10];

double MapaZX0[10], MapaZX1[10];
double MapaZY0[10], MapaZY1[10];

void setup(){
  GD.begin();
  MP();
}
void loop(){}

void MP()
{
  GD.cmd_loadimage(0, 0);  GD.load(MapJPG[Mbase]);
  limitesM(); 
  while(1)
  {
   if(TestGPS==0)
   {
    Lat=19.493523; Long=-102.248125;   //Paricutín, Pari.jpg
   }

   if(TestGPS==1)
   {
    Lat=10.490665; Long=104.605832;    //Vietnam Opción 1
   }

   if(TestGPS==2)
   {
    Lat=25.129932; Long=55.117630;    //Dubai17_c.jpg
   }   

   if(TestGPS==3)
   {
    Lat=25.125260; Long=55.129636;    //Dubai17_c.jpg
   }      

    
    ver_Mapas1(Lat, Long);
    GD.cmd_loadimage(0, 0);  GD.load(MapJPG[Mbase]);
    
    if(Long<=0)
    {
       DeltaPX= abs(MapaX0[Mbase])-abs(Long);  CambioPX=DeltaPX/PitchX;        //Calcula la coordenada X en el Mapa base
    }
    if(Long>=0)
    {
       DeltaPX= abs(Long-MapaX0[Mbase]);  CambioPX=DeltaPX/PitchX;             //Calcula la coordenada X en el Mapa base
    }
       DeltaPY= abs(Lat)-abs(MapaY0[Mbase]);   CambioPY=DeltaPY/PitchY;        //Calcula la coordenada Y en el mapa base
    
   GD.ClearColorRGB(0x000015);
   GD.Clear();
   GD.get_inputs();

     GD.SaveContext();
               GD.Begin(BITMAPS);
               MovPX=SiZeX/2-CambioPX;    
               MovPY=SiZeY/2+CambioPY;                        //calcula los pixeles de desplazamiento del mapa
               GD.Tag(1); GD.Vertex2f((((GD.w-SiZeX)/2) + MovPX)*16, (((GD.h-SiZeY)/2) + MovPY)*16);  GD.Tag(255); 
     GD.RestoreContext();
     GD.SaveContext();
                GD.ColorRGB(0xf01500);  
                sprintf(doubleTXT,"Lat: %.6f, Lon: %.6f",Lat,Long); 
                GD.cmd_text(GD.w/2, 50, 28, OPT_CENTER, doubleTXT);
                GD.cmd_text(GD.w/2, GD.h-50, 28, OPT_CENTER, doubleTXT);
                GD.cmd_text(GD.w/2, GD.h-25, 28, OPT_CENTER, MapJPG[Mbase]);
     GD.RestoreContext();
     GD.SaveContext();
               GD.ColorA(145);
               GD.Begin(POINTS);
               GD.PointSize(16*5);
               GD.ColorRGB(255,0,0);
               GD.Vertex2f((GD.w/2)*16, (GD.h/2)*16);
               GD.ColorA(255);
               GD.PointSize(16*1);
               GD.ColorRGB(255,255,0);
               GD.Vertex2f((GD.w/2)*16, (GD.h/2)*16);
                  
     GD.RestoreContext();

   if (GD.inputs.tag==1)
   {
    TestGPS=TestGPS+1;
    if(TestGPS>=4){TestGPS=0;}
   }

   GD.swap();
  }
}
