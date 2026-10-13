extern void iosCopyMatrix(void *, int);
extern unsigned char B_00147AA0[1];
extern int B_001482A0;

void glLoadMatrixf(int arg0)
{
    iosCopyMatrix(&B_00147AA0 + (B_001482A0 << 6), arg0);
}
