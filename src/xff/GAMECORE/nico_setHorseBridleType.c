extern char *GetLayoutClass(void *);
extern void SetClothSingleFixedChainLeafFixNodeOffset(void *, int);
extern void SetClothWorkDispFlag(void *, int, int);
extern const unsigned char RO_0017D4F0[][4];
extern const signed char RO_0017D500[];

void nico_setHorseBridleType(void *obj, int type)
{
    char *layout;
    const unsigned char *t;
    char *cls;
    char *w;
    int n;
    int i;

    layout = GetLayoutClass(obj);
    i = type * 4;
    t = &RO_0017D4F0[0][0] + i;
    cls = *(char **)(layout + 0x178);
    n = *(short *)(cls + 4);
    w = *(char **)cls;
    for (i = 0; i < n; i++) {
        SetClothSingleFixedChainLeafFixNodeOffset(w, *t++);
        w += 0x90;
        SetClothWorkDispFlag(cls, i, RO_0017D500[i]);
    }
}
