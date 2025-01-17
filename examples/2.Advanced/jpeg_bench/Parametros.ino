char TXP[50];

void Parametros()
{
  GD.SaveContext();
  
  GD.ColorRGB(0x00ff00);

  GD.cmd_text(2, (GD.h)-24, 20, 0, Board);
  sprintf(TXP,"F_CPU: %d MHz", (F_CPU/1000000));  GD.cmd_text(2, (GD.h)-48, 20, 0, TXP);

  #if defined(ARDUINO_ARCH_STM32)  
  if(GD.model==815){
  sprintf(TXP,"EVE chip: BT%d ", GD.model);  GD.cmd_text(2, (GD.h)-36, 20, 0, TXP);}else{
  sprintf(TXP,"EVE chip: FT%d ", GD.model);  GD.cmd_text(2, (GD.h)-36, 20, 0, TXP);  
  }
  #endif
  
  if(SizeEVE==35){GD.cmd_text(2, GD.h-12, 20, 0, "EVE chip: FT813@NHD-3.5-320240FT-CSXN-CTP");}
  if(SizeEVE==43){GD.cmd_text(2, GD.h-12, 20, 0, "EVE chip: FT813@NHD-4.3-480272FT-CSXN-CTP");}
  if(SizeEVE==5){GD.cmd_text(2, GD.h-12, 20, 0, "EVE chip: FT813@NHD-5.0-800480FT-CTXL-CTP");}
  if(SizeEVE==7){GD.cmd_text(2, GD.h-12, 20, 0, "EVE chip: FT813@NHD-7.0-800480FT-CSXN-CTP");}
  if(SizeEVE==51){GD.cmd_text(2, GD.h-12, 20, 0, "EVE chip: FT813@Riverdi RVT50UQFNWC000");}
  if(SizeEVE==71){GD.cmd_text(2, GD.h-12, 20, 0, "EVE chip: FT813@Riverdi RVT70UQFNWC000");}
  if(SizeEVE==52){GD.cmd_text(2, GD.h-12, 20, 0, "EVE chip: BT815@Matrix Orbital EVE3-50G");}
  
  
  GD.RestoreContext();
}
