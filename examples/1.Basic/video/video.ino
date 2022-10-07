#include <GDSTx.h>

void setup()
{
  GD.begin();
}
void loop()
{
  MoviePlayer mp;

  mp.begin("GIMBAL_2.avi");
  //mp.begin("GOFAST_3.avi");
      
  mp.play();
}
