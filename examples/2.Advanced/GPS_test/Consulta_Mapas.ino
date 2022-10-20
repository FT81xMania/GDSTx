void ver_Mapas1(double LatM, double LongM)
{  
       if ((LatM>=MapaY1[0]) && (LatM<=MapaY0[0]))      //Pari.jpg
              {      
             if ((LongM>=MapaX0[0]) && (LongM<=MapaX1[0]))
                {  
                  Mbase=0;
                  SiZeX=800, SiZeY=399;               
                  PitchX=0.000050626;  //  |MapaX[0]|-|MapaX[1]|/SiZeX = 800 px
                  PitchY=0.000050606;  //  |MapaY[0]|-|MapaY[1]|/SiZeY = 399 px
                  //PitchX=abs((abs(MapaX0[0])-abs(MapaX1[0])))/SiZeX;// = 800 px
                  //PitchY=abs((abs(MapaY0[0])-abs(MapaY1[0])))/SiZeY;// = 399 px                  
                }
              }

     if ((LatM>=MapaY1[1]) && (LatM<=MapaY0[1])) 
              {      
             if ((LongM>=MapaX0[1]) && (LongM<=MapaX1[1]))
                {  
                  Mbase=1;
                  SiZeX=800, SiZeY=431;               
                  PitchX=0.000050586;  //  |104.565961-104.606430|/largo jpg = 800 px
                  PitchY=0.000050533;  //  |10.460228-10.482008|/ alto jpg = 431 px
                  //PitchX=abs((abs(MapaX0[0])-abs(MapaX1[0])))/SiZeX;
                  //PitchY=abs((abs(MapaY0[0])-abs(MapaY1[0])))/SiZeY;
                }
              }

     if ((LatM>=MapaY1[2]) && (LatM<=MapaY0[2])) 
              {      
             if ((LongM>=MapaX0[2]) && (LongM<=MapaX1[2]))
                {  
                  Mbase=2;
                  SiZeX=800, SiZeY=382;               
                  PitchX=0.000050640;  //  |55.135531-55.095019|/largo jpg = 800 px
                  PitchY=0.000050664;  //  |25.139207-25.119853|/ alto jpg = 382 px
                  //PitchX=abs((abs(MapaX0[0])-abs(MapaX1[0])))/SiZeX;
                  //PitchY=abs((abs(MapaY0[0])-abs(MapaY1[0])))/SiZeY;
                }
              }                            
}
