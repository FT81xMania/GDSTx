char TXP[50];
void PieTX()
{
  GD.SaveContext();
  GD.ColorRGB(0x00ff00); sprintf(TXP,"F_CPU: %d MHz", (F_CPU/1000000));  GD.cmd_text(GD.w - 105, 0, 26, 0, TXP);

    GD.ColorRGB(0x444444); GD.cmd_text((GD.w-40), (GD.h)-10, 20, OPT_CENTER, "FT81xmania Team");
  GD.RestoreContext();
}
