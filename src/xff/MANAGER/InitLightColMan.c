extern char B_00148CF0[];
extern char *D_00136C00;
extern void *memset(void *, int, unsigned int);
extern void isysInitGroup(char *);

void InitLightColMan(void)
{
    D_00136C00 = B_00148CF0;
    memset(B_00148CF0, 0, 0xBD0);
    isysInitGroup(B_00148CF0 + 0x514);
    isysInitGroup(B_00148CF0 + 0x518);
    isysInitGroup(B_00148CF0 + 0x51C);
    isysInitGroup(B_00148CF0 + 0x524);
    isysInitGroup(B_00148CF0 + 0x528);
}
