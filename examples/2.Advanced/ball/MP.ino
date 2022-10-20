long previousMillisMatrix = 0, intervalMatrix = 2500;

void MP()
{
  while(1)
  {
    GD.ClearColorRGB(0x000000);
    GD.Clear();
    GD.get_inputs();

     PX=PX-velX;
     //if(PX<=0){velX=-cte;}
     //if(PX>=XMAX-(SizeX)){velX=cte;}

     if(PX<=0){velX=-cte;}
     if(PX>=XMAX-(SizeX)){velX=cte;}

     PY=PY-velY;
     //if(PY<=0){velY=-cte*.9;}
     //if(PY>=YMAX-(SizeY)){velY=cte;}

     if(PY<=0){velY=-cte;}
     if(PY>=YMAX-(SizeY)){velY=cte;}

if(cte<=0){
  cte=random(5,15);
  velX=cte;
  velY=cte;
}else{
unsigned long currentMillisMatrix = millis();
if(currentMillisMatrix - previousMillisMatrix > intervalMatrix)
  {
   previousMillisMatrix = currentMillisMatrix;
   cte=cte*.9;
   
  }
}
     GD.SaveContext();
     GD.Begin(BITMAPS);
     //GD.VertexTranslateX(PX*16);
     //GD.VertexTranslateY(PY*16);

     avance = 1 + dato;
     dato = dato + rapidez;
     if((AnguloG+avance)>=0){rapidez=3;}
     rotate_Center(DEGREES(AnguloG+avance), Centro);
     GD.cmd_setmatrix();
     
      //GD.Vertex2ii(0, 0, 15);
      GD.Tag(1);  GD.Vertex2f(PX*16, PY*16); GD.Tag(255);
      
     GD.cmd_loadidentity();
     GD.End();
  GD.RestoreContext();

GD.cmd_number(190, 14, 28, OPT_SIGNED|OPT_RIGHTX, cte);

if (GD.inputs.tag==1)
    {
      cte=15;
    }

   // GD.SaveContext();
   //  GD.ColorA(255); GD.PointSize(10*16);
   //  GD.Begin(POINTS);
   //  GD.ColorRGB(0xff0000); GD.Vertex2f((PX)*16, (PY)*16);
   // GD.RestoreContext();     

   //GD.SaveContext();
   //GD.ColorRGB(0xFFFFFF);
   //  GD.LineWidth(7); GD.Begin(LINES);
   //  GD.Vertex2f((PX+(SizeX/2))*16, (0)*16); GD.Vertex2f((PX+(SizeX/2))*16, (YMAX)*16);      //VERTICAL
   //  GD.Vertex2f((0)*16, (PY+(SizeY/2))*16); GD.Vertex2f((XMAX)*16, (PY+(SizeY/2))*16);      //HORIZONTAL
   //GD.RestoreContext();

    Parametros();
    GD.swap();
  }
}
