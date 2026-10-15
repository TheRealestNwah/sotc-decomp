extern int *B_001517F4;
extern void iosIopRead(int, int, int);
void sheetFsLoadAdpcmInt(int a, int i, int off, int buf, int size)
{
    int *t = B_001517F4 + i * 2;
    iosIopRead(*t + off, buf, size);
}
