extern int glBegin(int);
extern void glEnable(int);
extern void glDisable(int);
extern void glEnd(void);
extern char *iosGetCurrentDC(void);
extern void glSetReg(long reg, long data);
extern void glBlendFuncParticle(int);
extern void gluSetWrapMode(int, int);
extern void func_000C7360(char *a, char *b);

static void func_000C6DF0(char *a, char *b, char *c)
{
    glBegin(8);
    glDisable(9);
    glEnable(3);
    glEnable(0);
    glEnable(7);
    glDisable(8);
    glEnable(4);
    glEnable(1);
    glSetReg(0x4E, *(int *)(iosGetCurrentDC() + 0x164) | 0x31000000 | 0x100000000L);
    glBlendFuncParticle(*(int *)(b + 0x14));
    glEnd();
    gluSetWrapMode(1, 1);
    func_000C7360(a, c);
}
