extern void iosUnitMatrix(void *);
extern unsigned char B_00147AA0[];
extern int B_001482A0;

void glLoadIdentity(void)
{
    B_001482A0 = 0;
    iosUnitMatrix(B_00147AA0);
}
