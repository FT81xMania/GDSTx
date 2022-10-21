void fondoJPGZoom()
{
  GD.Begin(BITMAPS);
    GD.cmd_scale(F16(zoom),F16(zoom));
    GD.cmd_setmatrix();
    GD.Tag(7);    GD.Vertex2f(16*X, 16*Y);  GD.Tag(255);
}  
