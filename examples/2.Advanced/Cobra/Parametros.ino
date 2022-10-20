char TXP[50];

void Parametros()
{
  GD.SaveContext();
  
  GD.ColorRGB(0x00ff00);
  sprintf(TXP,"F_CPU: %d MHz", (F_CPU/1000000));  GD.cmd_text(5, 0, 26, 0, TXP);
  GD.cmd_text(0, (GD.h)-15, 26, 0, Board);
      
  GD.RestoreContext();
}
