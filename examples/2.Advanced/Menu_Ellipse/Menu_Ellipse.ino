//#include <GD23ZUTX.h>
//#include <GDT4Xv134.h>
#include <GDSTx.h>

#include "money.h"  //0
#include "Icons2.h" //1
#include "Ricon1.h" //2
#include "H1ico.h"  //3
#include "Radio1.h" //4
#include "Radio2.h" //5

                      //    0            1             2          3            4            
char GrupoJPG1[21][15]={"Fn1.jpg","Fondo003.jpeg","tree.jpg","zx13.jpg","selfie.jpg"};
int IDJPG=0;

//                        0            1             2            3            4              5 //IDAsset
char ChAsset[6][11]={"money.gd2", "Icons2.gd2", "Ricon1.gd2", "H1ico.gd2", "Radio1.gd2", "Radio2.gd2"};  //File FileAsset;
int NumAssets;          //10            14          14            8             10           9
int IDAsset=1;

uint32_t ram;
//double ram;
double FRAM, SRAM;

double pi= 3.141592654;

int A[20];
int B[20];
int XX0[20], YY0[20], RadioR[20];
double EEX[20], EEY[20];
double TT[20];
double DeltaD[20];

//Menu elíptico
//parametros de centroide del menu elíptico
  int MCa= 250, MCb= 120, MCX= 250, MCY=190;
  float MCV = -0.01;  //0.025; 0.01;  -0.025;  0.005 velocidad y dirección de rotación
//parametros de centroide del menu elíptico  

int DESPMCX= 100, DESPMCY= -180;

int movx=0, separacionpanel=5;
