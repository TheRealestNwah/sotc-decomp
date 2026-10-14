extern void isysInitGroup(int);
extern int D_00136C10;

void InitObjectManagerResourceInfo(int arg0)
{
    D_00136C10 = arg0;
    isysInitGroup(arg0 + 4);
    isysInitGroup(D_00136C10);
    isysInitGroup(D_00136C10 + 8);
    isysInitGroup(D_00136C10 + 0xC);
    isysInitGroup(D_00136C10 + 0x10);
    isysInitGroup(D_00136C10 + 0x14);
    isysInitGroup(D_00136C10 + 0x18);
}
