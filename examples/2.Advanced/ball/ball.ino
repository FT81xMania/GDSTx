//#include <GD23ZUTX.h>
#include <GDSTx.h>

int MCUID;
int XMAX, YMAX;

int cte=10, PX=400, PY=272, velX=cte, velY=cte;

float dato;

int Size=48;  //48-football.png, 110-Rad1a.png, 210-AE3.pn, 300-Ag4.png
int SizeX=Size, SizeY=Size;
int Centro=Size/2;   //SizexSize px, Centro=Size/2
float AnguloG=0;  //angulo base de la imagen
float avance, rapidez=1.5;
