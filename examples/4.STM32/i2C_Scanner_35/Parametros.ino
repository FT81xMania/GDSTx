//char TXP[50];

//void STM32()
//{
// GD.ColorRGB(0x00ff00); sprintf(TXP,"F_CPU: %d MHz", (F_CPU/1000000));  GD.cmd_text(GD.w - 105, 5, 26, 0, TXP);  
 //GD.ColorRGB(0x00ff00); sprintf(TXP,"F_SPI1:  %d MHz", (FreqSPI1/1000000));  GD.cmd_text(GD.w - 105, 20, 26, 0, TXP);
 //GD.ColorRGB(0x00ff00); sprintf(TXP,"F_SPI2:  %d MHz", (FreqSPI2));  GD.cmd_text(GD.w - 105, 35, 26, 0, TXP);
//}

char TXP[50];

void Parametros()
{
  GD.SaveContext();
   GD.ColorRGB(0x555500);
   GD.cmd_text(0, (GD.h)-30, 26, 0, Board);
   sprintf(TXP,"F_CPU: %d MHz", (F_CPU/1000000));  GD.cmd_text(0, (GD.h)-15, 26, 0, TXP);
  GD.RestoreContext();
}
