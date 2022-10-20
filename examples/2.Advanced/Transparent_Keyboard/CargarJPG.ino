void ImagenJPG(int Fondo)
{
  start = millis();       
  GD.cmd_loadimage(0, 0);
  GD.load(FondoJPG[Fondo]);
}
