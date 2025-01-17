#include <GDSTx.h>

void setup() {
  GD.begin();
}
void loop()
{
  GD.Clear();
  GD.cmd_logo();
}
