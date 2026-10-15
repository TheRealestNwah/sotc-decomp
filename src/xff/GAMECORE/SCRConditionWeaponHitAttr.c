extern char *getSCRDataCtrlWork(void *);
extern int getPlayerWeaponHitAttr(int);

int SCRConditionWeaponHitAttr(void *a, int b, int c, int d, int mask, int val)
{
    if (val != -1)
        return val == (getPlayerWeaponHitAttr(*(int *)(getSCRDataCtrlWork(a) + 0x4078)) & mask);
    return (getPlayerWeaponHitAttr(*(int *)(getSCRDataCtrlWork(a) + 0x4078)) & mask) != 0;
}
