extern int DldSysUndefSymbol;
extern char *GetLayoutClass(void *);
extern char *GetCharacterClass(void *);

int SCRConditionGameObjParentColAttr(void *a, int b, int c, int d, long mask, int attr, int g, int *h)
{
    int ooff = *h & 0x3FFFF;
    int *ot = ooff != 0 ? *(int **)((char *)h - ooff) : 0;
    int *o = (ot != 0 && ot != (int *)DldSysUndefSymbol) ? (int *)ot[4] : 0;
    char *cls;

    if (o != 0) {
        if (o[2] != 0) {
            if (*(int *)(GetLayoutClass((void *)o[2]) + 0x124) != 0) {
                cls = GetCharacterClass((void *)o[2]);
                if (attr != -1)
                    return attr == (*(long *)(cls + 0x690) & mask);
                return (*(long *)(cls + 0x690) & mask) != 0;
            }
        }
    }
    return 0;
}
