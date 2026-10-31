extern int glBegin(int);
extern void glDisable(int);
extern void glEnd(void);
extern char *iosGetCurrentDC(void);
extern void glSetReg(long reg, long data);

static void func_000C6EB8(void)
{
    glBegin(8);
    glSetReg(0x4E, *(int *)(iosGetCurrentDC() + 0x164) | 0x31000000);
    glDisable(0);
    glDisable(3);
    glDisable(4);
    glEnd();
}
