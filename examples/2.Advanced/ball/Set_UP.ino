void setup() {
  GD.begin();
  //GD.cmd_setrotate(0);
  IDEMCU();
  XMAX=GD.w; YMAX=GD.h;

  //GD.BitmapHandle(15);
  GD.cmd_loadimage(0, 0);
  GD.load("football.png"); //48
  
  MP();
}
void loop(){}
