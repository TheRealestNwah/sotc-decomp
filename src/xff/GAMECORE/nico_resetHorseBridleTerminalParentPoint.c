/* nico_resetHorseBridleTerminalParentPoint: 36 diffs. Register pins (obj $21, cloth $18, w $17, tbl $20, n $19, i $16; second loop p $20, q $18 set after the work pointer, n2 $17, w2 $16, g $19; geo $18) and the inverted select give most of the Original allocation. Remaining: the Original schedules the tbl lui/addiu after the first 0x178 load, rematerialises &vec (sp+0x80) at each call where ours keeps it in $s4, and loads 0.0f into $f20 after the first loop instead of at entry. */
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
void nico_resetHorseBridleTerminalParentPoint(int obj0)
{
    char buf0[0x40];
    char buf1[0x40];
    float vec[4] __attribute__((aligned(16)));
    register int obj __asm__("$21") = obj0;
    register char *cloth __asm__("$18");
    register char *w __asm__("$17");
    register unsigned char *tbl __asm__("$20");
    register int n __asm__("$19");
    register int i __asm__("$16");
    register char *geo __asm__("$18");
    float zero = 0.0f;

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
    {
    register char *p __asm__("$20") = buf0;
    register char *q __asm__("$18");
    register char *c2;
    register int n2 __asm__("$17");
    register char *w2 __asm__("$16");
    register int g __asm__("$19");
    c2 = *(char **)(GetLayoutClass(obj) + 0x178);
    n2 = *(short *)(c2 + 4);
    w2 = *(char **)c2;
    q = buf1;
    for (g = 0; g < n2; g++) {
        SetClothSingleFixedChainLeafFixGeometryPointer((int)w2, !(g & 1) ? q : p);
        w2 += 0x90;
    }
    }
    ParentLayoutObj(obj, buf0);
}
#endif
