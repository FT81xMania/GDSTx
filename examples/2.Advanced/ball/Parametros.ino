char TXP[50];

void Parametros()
{
  GD.SaveContext();
  
  GD.ColorRGB(0xffffff);
  sprintf(TXP,"F_CPU: %d MHz", (F_CPU/1000000));  GD.cmd_text(3, (GD.h)-30, 26, 0, TXP);
  GD.cmd_text(3, (GD.h)-15, 26, 0, Board);
      
  GD.RestoreContext();
}
