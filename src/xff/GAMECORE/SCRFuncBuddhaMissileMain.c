extern int *DldSysUndefSymbol;
extern char gcGlobalVar[];
extern char *GetSCRCharaAIWorkPtr(void *);
extern char *getSCRDataCtrlWork(void *);
extern char *GetLayoutClass(void *);
extern void CharaCtrlSetScriptCtrlStatus(void *, int);

static inline char *dldElem(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;
    return (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
}

void SCRFuncBuddhaMissileMain(void *actor, int a1, int a2, int a3, int a4, int a5, int a6, int a7, unsigned int *h)
{
    char *ai = GetSCRCharaAIWorkPtr(actor);
    char *data = getSCRDataCtrlWork(actor);
    char *layout = GetLayoutClass(actor);
    float d;
    float *tbl;
    char *e;

    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xz vf7, vf7, vf7\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "vsqrt Q, vf7x\n"
                         "vwaitq\n"
                         "cfc2 $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(*(float **)(layout + 0x134)), "r"(*(float **)(*(char **)(data + 0x407C) + 0x134))
                         : "$2");
    tbl = *(float **)(ai + 0x41B0);
    if (tbl[0] <= d && d <= tbl[1]) {
        if (tbl[2] + (tbl[3] - tbl[2]) * ((d - tbl[0]) / (tbl[1] - tbl[0])) <= *(float *)(ai + 0x41B4)) {
            e = dldElem(h);
            if (e != 0)
                CharaCtrlSetScriptCtrlStatus(actor, *(int *)(e + 4));
            *(float *)(ai + 0x41B4) = 0;
            *(int *)(ai + 0x41C4) = 2;
        }
    }
    *(float *)(ai + 0x41B4) += *(float *)(gcGlobalVar + 0x180);
}
