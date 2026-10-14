void SetScariptAnimationObjMotSyncSlotId(unsigned char *p, int a)
{
    char *c = p[8] != 0xD ? 0 : (char *)p + 0x20;

    *(int *)(c + 0x350) = a;
}
