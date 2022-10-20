#if defined(__arm__)
extern "C" char* sbrk(int incr);
static int FreeStack() {
  char top = 't';
  return &top - reinterpret_cast<char*>(sbrk(0));
}
#endif

char TX[50];
//int RAM = 131072;
void STM32a()
{
  ram = FreeStack();
  FRAM=ram;
  //if(FRAM<=131072){SRAM=131072;}
  //            else{SRAM=196608;}
  //if(FRAM<=196608){SRAM=196608;}
  //            else{SRAM=327680;}
  //if(FRAM<=196608){SRAM=327680;}
  //            else{SRAM=524288;}  
  //if(FRAM<=262144){SRAM=262144;}
  //            else{SRAM=524288;}
  if(FRAM<=524288){SRAM=524288;}
              else{SRAM=1048576;}
}

void STM32()
{
  STM32a();
  GD.ColorRGB(0x00ff00); sprintf(TX,"F_CPU: %d MHz", (F_CPU/1000000));  GD.cmd_text(GD.w - 105, 0, 26, 0, TX);

  //GD.cmd_text(GD.w - 105, 16, 26, 0, "U_RAM:               %");  GD.printNfloat(GD.w - 35, 16, 100*(SRAM-FRAM)/SRAM, 2, 26);
  //sprintf(TX,"U_RAM: %.2f%%",100*(SRAM-FRAM)/SRAM);  GD.cmd_text(GD.w - 55, 16+7, 26, OPT_CENTER, TX);
  sprintf(TX,"U_RAM: %.1f",FRAM);  GD.cmd_text(GD.w - 100, 16+7, 26, OPT_CENTER, TX);

  GD.ColorA(75);

  //sprintf(floatTXT,"%g-- %6f, %6f, %g msnm",NumSat, Lat, Long, Alt);  GD.cmd_text(320/2, (240/2)-105, 26, OPT_CENTER, floatTXT);
  
  sprintf(TX,"%.6f%%",100*(SRAM-FRAM)/SRAM);  GD.cmd_text(170, 0, 20, 0, TX);
  //GD.printNfloat(200,  0, 100*(SRAM-FRAM)/SRAM, 6, 20);
  //GD.printNfloat(200, 16, 100*(SRAM-FRAM)/SRAM, 6, 26);
  sprintf(TX,"%.6f%%",100*(SRAM-FRAM)/SRAM);  GD.cmd_text(170, 16, 26, 0, TX);
  //GD.printNfloat(200, 16+20, 100*(SRAM-FRAM)/SRAM, 6, 27);
  sprintf(TX,"%.6f%%",100*(SRAM-FRAM)/SRAM);  GD.cmd_text(170, 16+20, 27, 0, TX);
  //GD.printNfloat(200, 16+40, 100*(SRAM-FRAM)/SRAM, 6, 28);
  sprintf(TX,"%.6f%%",100*(SRAM-FRAM)/SRAM);  GD.cmd_text(170, 16+40, 28, 0, TX);
  //GD.printNfloat(200, 16+60, 100*(SRAM-FRAM)/SRAM, 6, 29);
  sprintf(TX,"%.6f%%",100*(SRAM-FRAM)/SRAM);  GD.cmd_text(170, 16+60, 29, 0, TX);
  //GD.printNfloat(200, 16+80, 100*(SRAM-FRAM)/SRAM, 6, 30);
  sprintf(TX,"%.6f%%",100*(SRAM-FRAM)/SRAM);  GD.cmd_text(170, 16+80, 30, 0, TX);
  //GD.printNfloat(200, 16+105, 100*(SRAM-FRAM)/SRAM, 6, 31);
  sprintf(TX,"%.6f%%",100*(SRAM-FRAM)/SRAM);  GD.cmd_text(170, 16+105, 31, 0, TX);

  GD.cmd_romfont(14,32);
  //GD.printNfloat(200, 16+145, 100*(SRAM-FRAM)/SRAM, 6, 14);
  sprintf(TX,"%.6f%%",100*(SRAM-FRAM)/SRAM);  GD.cmd_text(170, 16+145, 14, 0, TX);

  GD.cmd_romfont(14,33);
  //GD.printNfloat(200, 16+195, 100*(SRAM-FRAM)/SRAM, 6, 14);
  sprintf(TX,"%.6f%%",100*(SRAM-FRAM)/SRAM);  GD.cmd_text(170, 16+195, 14, 0, TX);

  GD.cmd_romfont(14,34);
  //GD.printNfloat(200, 16+255, 100*(SRAM-FRAM)/SRAM, 6, 14);
  sprintf(TX,"%.6f%%",100*(SRAM-FRAM)/SRAM);  GD.cmd_text(170, 16+255, 14, 0, TX);
  GD.ColorA(255);
  
  //sprintf(TX,"F_SPI1:  %d MHz", (FreqSPI1));  GD.cmd_text(GD.w - 105, 32, 26, 0, TX);
  //sprintf(TX,"F_SPI2:  %d MHz", (FreqSD2/1000000));  GD.cmd_text(GD.w - 105, 48, 26, 0, TX);
}
