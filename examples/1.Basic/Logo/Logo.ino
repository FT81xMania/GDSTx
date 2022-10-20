//#include <GD23ZUTX.h>
//#include <GDT4Xv134.h>
#include <GDSTx.h>

void setup() {
  GD.begin();
}
void loop()
{
  GD.Clear();
  GD.cmd_logo();
}
