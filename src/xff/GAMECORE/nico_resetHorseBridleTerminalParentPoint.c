/* nico_resetHorseBridleTerminalParentPoint: ~72 diffs (reg alloc of loop vars / vec build) */
typedef int s128 __attribute__((mode(TI)));
extern unsigned char RO_0017D4F0[];
extern char RO_0017D500[];
extern float RO_0017D510[];
extern char IdentityQuaternion[];
extern char *GetLayoutClass(int);
extern void SetClothSingleFixedChainLeafFixNodeOffset(int, int);
extern void SetClothWorkDispFlag(void *, int, int);
extern void SetGeometryPointerNodePosState(void *, void *, int, void *, void *);
extern void SetClothSingleFixedChainLeafFixGeometryPointer(int, void *);
extern void ParentLayoutObj(int, void *);

#ifdef NONMATCHING
void nico_resetHorseBridleTerminalParentPoint(int obj)
{
    char buf0[0x40];
    char buf1[0x40];
    float vec[4] __attribute__((aligned(16)));
    float zero = 0.0f;
    char *cloth;
    char *w;
    unsigned char *tbl;
    int n;
    int i;
    int g;
    char *p;
    char *geo;

    cloth = *(char **)(GetLayoutClass(obj) + 0x178);
    n = *(short *)(cloth + 4);
    tbl = RO_0017D4F0 + 0xC;
    w = *(char **)cloth;
    for (i = 0; i < n; i++) {
        SetClothSingleFixedChainLeafFixNodeOffset((int)w, *tbl++);
        w += 0x90;
        SetClothWorkDispFlag(cloth, i, RO_0017D500[i]);
    }
    geo = *(char **)(GetLayoutClass(obj) + 0x194);
    *(s128 *)vec = *(s128 *)RO_0017D510;
    vec[0] = RO_0017D510[0] - zero;
    SetGeometryPointerNodePosState(buf0, geo, 0, IdentityQuaternion, vec);
    vec[0] = RO_0017D510[0] + zero;
    SetGeometryPointerNodePosState(buf1, geo, 0, IdentityQuaternion, vec);
    cloth = *(char **)(GetLayoutClass(obj) + 0x178);
    n = *(short *)(cloth + 4);
    w = *(char **)cloth;
    for (g = 0; g < n; g++) {
        SetClothSingleFixedChainLeafFixGeometryPointer((int)w, (g & 1) ? buf0 : buf1);
        w += 0x90;
    }
    ParentLayoutObj(obj, buf0);
}
#endif
