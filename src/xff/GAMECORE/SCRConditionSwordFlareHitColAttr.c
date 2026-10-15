extern int GetSwordFlareHitPlaneAttribute(void *);

int SCRConditionSwordFlareHitColAttr(void *a, int b, int c, int d, int mask, int val)
{
    if (val != -1)
        return val == (GetSwordFlareHitPlaneAttribute(a) & mask);
    return (GetSwordFlareHitPlaneAttribute(a) & mask) != 0;
}
