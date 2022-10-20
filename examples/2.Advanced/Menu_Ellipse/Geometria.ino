void Parametros(int i, int a, int b, int px, int py, int r, double inicial, double delta)
{
  A[i]=a;
  B[i]=b;
  XX0[i]=px;   YY0[i]=py;   
  RadioR[i]=r;   //para puntos con trayectoria elíptica
  EEX[i]=0;  EEY[i]=0;
  TT[i]=inicial;
  DeltaD[i]=delta;  
}

double dato;
int Centro=48/2;   //48x48 px, Centro=48/2
double AnguloG=0;  //angulo base de la imagen
double avance, rapidez=1.5;


void EllipseD(int j, int IMG)
{
  EEX[j]= XX0[j]+A[j]*cosf(TT[j]);
  EEY[j]= YY0[j]+B[j]*sinf(TT[j]);

   GD.Vertex2ii(EEX[j], EEY[j], IMG);

  TT[j]= TT[j]+DeltaD[j];
}

void ElipseCpuntos()
{
  GD.Begin(POINTS);
  GD.ColorRGB(255,255,0);
   GD.PointSize(16*50);
   GD.Vertex2f(400*16, 240*16);

  GD.ColorRGB(255,0,0);   Ellipse(1);
  GD.ColorRGB(0,0,255);   Ellipse(2);
  GD.ColorRGB(0,255,0);   Ellipse(3);
}

void Ellipse(int j)
{
  EEX[j]= XX0[j]+A[j]*cosf(TT[j]);
  EEY[j]= YY0[j]+B[j]*sinf(TT[j]);
   GD.PointSize(RadioR[j]*16);
   GD.Vertex2f(EEX[j]*16, EEY[j]*16);
   TT[j]= TT[j]+DeltaD[j];
}


static void rotate_Center(double a, int CXY)
{
  GD.cmd_translate(F16(CXY),F16(CXY));
  GD.cmd_rotate(a);
  GD.cmd_translate(F16(-CXY), F16(-CXY));
}
