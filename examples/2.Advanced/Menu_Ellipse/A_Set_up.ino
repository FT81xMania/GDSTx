void setup()
{
  GD.begin();
   //GD.cmd_setrotate(1); 
  // GD.self_calibrate();
  espera();
  CargaGrupoJPG1(IDJPG);

  MP();
}

void loop(){}

unsigned long start, Test;

void CargaGrupoJPG1(int IDJPG)
{
  start = millis(); 

  if (IDAsset==0){LOAD_ASSETS0(); NumAssets=10;}
  if (IDAsset==1){LOAD_ASSETS1(); NumAssets=14;}
  if (IDAsset==2){LOAD_ASSETS2(); NumAssets=14;}
  if (IDAsset==3){LOAD_ASSETS3(); NumAssets=8;}
  if (IDAsset==4){LOAD_ASSETS4(); NumAssets=10;}
  if (IDAsset==5){LOAD_ASSETS5(); NumAssets=9;}
  
  GD.BitmapHandle(15);
  GD.cmd_loadimage(ASSETS_END, 0);
  GD.load(GrupoJPG1[IDJPG]);

  Test = millis() - start;
}
