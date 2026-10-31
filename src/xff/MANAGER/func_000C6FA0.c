extern void glBegin(int);
extern void glEnd(void);
extern void glEnable(int);
extern void glDisable(int);
extern char *iosGetCurrentDC(void);
extern void glSetReg(int, unsigned long);
extern void glBlendFuncParticle(int);
extern void gluSetWrapMode(int, int);

static void func_000C6FA0(char *p)
{
    glBegin(8);
    glDisable(9);
    glEnable(3);
    glEnable(0);
    glEnable(7);
    glDisable(8);
    glDisable(4);
    glEnable(1);
    glSetReg(0x4E, *(int *)(iosGetCurrentDC() + 0x164) | 0x31000000 | 0x100000000UL);
    glBlendFuncParticle(*(int *)(p + 0x14));
    glDisable(0x13);
    glEnd();
    gluSetWrapMode(1, 1);
}
