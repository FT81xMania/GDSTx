int XTXT=125+65+5;

void Tipo()
{ if(Dispositivo==24) {GD.cmd_text(XTXT, 50+(Sep*15), 20, 0, "-- MAX1668 (5)");}          //0x18
  if(Dispositivo==25) {GD.cmd_text(XTXT, 50+(Sep*15), 20, 0, "-- MAX1668 (5)");}          //0x19
  if(Dispositivo==28) {GD.cmd_text(XTXT, 50+(Sep*15), 20, 0, "-- MAX6697 (7)");}          //0x1c base
  if(Dispositivo==30) {GD.cmd_text(XTXT, 50+(Sep*15), 20, 0, "-- MMC5883L (GY-273)");}    //0x1e
  if(Dispositivo==35) {GD.cmd_text(XTXT, 50+(Sep*15), 20, 0, "-- Light sensor(GY-30)");}  //0x23
  if(Dispositivo==39) {GD.cmd_text(XTXT, 50+(Sep*15), 20, 0, "-- LCD 16x2");}             //0x27
  if(Dispositivo==41) {GD.cmd_text(XTXT, 50+(Sep*15), 20, 0, "-- MAX1668 (5)");}          //0x29
  if(Dispositivo==42) {GD.cmd_text(XTXT, 50+(Sep*15), 20, 0, "-- MAX1668 (5)");}          //0x2a, base, AD0/AD1 libres
  if(Dispositivo==43) {GD.cmd_text(XTXT, 50+(Sep*15), 20, 0, "-- MAX1668 (5)");}          //0x2b
  if(Dispositivo==77) {GD.cmd_text(XTXT, 50+(Sep*15), 20, 0, "-- MAX1668 (5)");}          //0x4d
  if(Dispositivo==78) {GD.cmd_text(XTXT, 50+(Sep*15), 20, 0, "-- MAX1668 (5)");}          //0x4e
  if(Dispositivo==80) {GD.cmd_text(XTXT, 50+(Sep*15), 20, 0, "-- EEPROM 24XXXXX");}       //0x50   //24FC512
  if(Dispositivo==81) {GD.cmd_text(XTXT, 50+(Sep*15), 20, 0, "-- EEPROM 24XXXXX");}       //0x51
  if(Dispositivo==87) {GD.cmd_text(XTXT, 50+(Sep*15), 20, 0, "-- DS3231 EEPROM");}        //0x57
  if(Dispositivo==104){GD.cmd_text(XTXT, 50+(Sep*15), 20, 0, "-- DS3231 RTC");}           //0x68
  if(Dispositivo==105){GD.cmd_text(XTXT, 50+(Sep*15), 20, 0, "-- MPU6050 (GY-521)");}     //0x69
  if(Dispositivo==119){GD.cmd_text(XTXT, 50+(Sep*15), 20, 0, "-- BMP180 (GY-68)");}       //0x77
}
