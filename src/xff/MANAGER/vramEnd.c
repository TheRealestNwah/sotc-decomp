extern void iosFree(int);
extern int D_00136550;

void vramEnd(void)
{
    iosFree(D_00136550);
}
