extern int glBeginWithDlLayerNo(int, int);
extern int iosDlGetLayer();

void glBegin(int arg0)
{
    glBeginWithDlLayerNo(arg0, iosDlGetLayer());
}
