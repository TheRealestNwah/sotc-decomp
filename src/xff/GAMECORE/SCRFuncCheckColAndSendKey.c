typedef int s128 __attribute__((mode(TI)));
typedef struct { long long x, y; } Pair;

extern int *DldSysUndefSymbol;
extern char gcGlobalVar[];
extern int getSCRDataCtrlWork();
extern s128 *getPassageWork(int, int);
extern char *GetLayoutClass(void *);
extern int ClipCollisionDirectCallBack(void *, void *, void *, void *, int, int, int, void *, void *);
extern long nico_GetGeometryPointerAttr(void *);
extern void CharaCtrlSetScriptCtrlStatus(void *, int);
extern int func_00119378(void *);

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return (t != 0 && t != DldSysUndefSymbol) ? (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}

void SCRFuncCheckColAndSendKey(void *obj, int n, int u, long long mask, long long ex, int i1, int i2, int i3, float limit, unsigned int *table)
{
    struct { s128 v10; s128 v20; char buf[0x50]; Pair held; } L;
    s128 *passage;
    char *res;

    passage = getPassageWork(getSCRDataCtrlWork(), 0);
    if (passage == 0)
        return;
    L.v10 = *(s128 *)*(void **)(GetLayoutClass(obj) + 0x134);
    L.v20 = *passage;
    L.held.x = mask;
    L.held.y = ex;
    if (ClipCollisionDirectCallBack(L.buf, &L.v10, &L.v20, gcGlobalVar + 0x238, 0, 0, 0, func_00119378, &L.held) != 0) {
        float len;
        char *pa;
        char *pb;
        pa = (char *)&L.v10;
        pb = L.buf + 0x40;
        __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                             "lqc2 vf6, 0x0(%2)\n"
                             "vsub.xyzw vf7, vf5, vf6\n"
                             "vmul.xyz vf7, vf7, vf7\n"
                             "vmulax.w ACC, vf0, vf7x\n"
                             "vmadday.w ACC, vf0, vf7y\n"
                             "vmaddz.w vf7, vf0, vf7z\n"
                             "vsqrt Q, vf7w\n"
                             "vwaitq\n"
                             "cfc2.ni $2, $22\n"
                             "mtc1 $2, %0\n"
                             : "=f"(len) : "r"(pa), "r"(pb) : "$2", "memory");
        if (limit < len)
            return;
        res = dldResolve(table);
        {
            long long idx = ((unsigned long long)(nico_GetGeometryPointerAttr(L.buf) & mask) >> 47) - (ex >> 47);
            if (res != 0 && idx >= 0 && idx < n)
                { int *ent = (int *)(res + (int)idx * 12); CharaCtrlSetScriptCtrlStatus(obj, ent[1]); }
        }
    }
}
