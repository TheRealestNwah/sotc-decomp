extern void iosCopyMatrix(void *, int);
extern unsigned char D_001305F0[];

void glSetLightColor(int arg0)
{
    iosCopyMatrix(D_001305F0, arg0);
}
