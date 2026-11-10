/* ~122 diffs, same length (187 words). Fallen-leaf / particle draw submit: counts the live entries (stride 0x40, flag at +0x20, ref at +0x34 with float >= 0 at ref+0x10), fetches a ptcl display list for them, resolves the layout object and its texture via two dld handles, builds a unit matrix rotated by pi/2 around X, packs each live entry into 0x30 bytes (quad copies, +0xC/+0x24/+0x28 floats), then submits layer 0xB (or 0x12 + modelResetSurface when under water) with the ptclman Mat/Env/Vtx packets. Only the saved-register assignment differs: the original uses s1 = count, s2 = live count, a0 = entry pointer, a1 = remaining counter; ours swaps the counters and uses v1 for the pointer. */
typedef int s128 __attribute__((mode(TI)));
extern int DldSysUndefSymbol;
extern s128 All1Vector;
extern long RO_0017D3E0[2];
extern int ptclDisplayListGet(int);
extern int *getFogUnderWater(void);
extern void iosUnitMatrix(void *);
extern void iosRotMatrixX(void *, float);
extern void iosDlPushLayer(int);
extern void iosDlPopLayer(void);
extern void modelResetSurface(int);
extern void ptclDisplayListPut(int);
extern void texTransRequest(int, int, int);
extern void transMicroCode(int);
extern void ptclmanBegin(void);
extern void ptclmanBuildMatPacket(int, float, float);
extern void ptclmanBuildEnvPacket(void *, int, void *, int, int, float);
extern void ptclmanBuildVtxPacket(int, int);
extern void ptclmanEnd(void);

static inline char *dldRes(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;
    return (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
}

#ifdef NONMATCHING
void func_00053AE0(char *obj, char *w, char *a2, char *a3, char *tbl)
{
    int cnt = *(int *)(w + 0x120);
    int n = 0;
    int i;
    char *e;
    char *out;
    int dl;
    char *p;
    unsigned int *h2;
    unsigned int v2;
    char *t;
    char *tex;
    struct { s128 one; long env[2]; float m[16]; } L;

    if (cnt > 0) {
        for (i = cnt, e = tbl; i != 0; i--, e += 0x40) {
            if (*(int *)(e + 0x20) != 0 && *(int *)(e + 0x34) != 0 &&
                0.0f <= *(float *)(*(char **)(e + 0x34) + 0x10))
                n++;
        }
    }
    if (n <= 0)
        return;
    dl = ptclDisplayListGet(n);
    if (dl == 0)
        return;
    out = (char *)dl;
    p = dldRes((unsigned int *)(*(char **)(obj + 0x1C) + 0x1C));
    h2 = (unsigned int *)(p + 4);
    v2 = *h2;
    {
        int off = v2 & 0x3FFFF;
        t = off != 0 ? *(char **)((char *)h2 - off) : 0;
    }
    tex = (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) : 0;
    tex = *(char **)(tex + 0xC);
    L.one = All1Vector;
    L.env[0] = RO_0017D3E0[0];
    L.env[1] = RO_0017D3E0[1];
    iosUnitMatrix(L.m);
    iosRotMatrixX(L.m, 1.5707964f);
    if (cnt > 0) {
        for (i = cnt, e = tbl; i != 0; i--, e += 0x40) {
            if (*(int *)(e + 0x20) != 0 && *(int *)(e + 0x34) != 0 &&
                0.0f <= *(float *)(*(char **)(e + 0x34) + 0x10)) {
                *(s128 *)out = *(s128 *)e;
                *(s128 *)(out + 0x20) = *(s128 *)(e + 0x10);
                *(float *)(out + 0xC) = *(float *)(e + 0x28);
                ((float *)&L.one)[3] = *(float *)(e + 0x24);
                *(s128 *)(out + 0x10) = L.one;
                out += 0x30;
            }
        }
    }
    if (*getFogUnderWater() != 0) {
        iosDlPushLayer(0xB);
    } else {
        iosDlPushLayer(0x12);
        modelResetSurface(0x12);
    }
    ptclDisplayListPut(n);
    texTransRequest((int)tex, 0, 0);
    transMicroCode(7);
    ptclmanBegin();
    ptclmanBuildMatPacket(0, 1.0f, 1.0f);
    ptclmanBuildEnvPacket(L.env, 2, L.m, 0, 0, 1.0f);
    ptclmanBuildVtxPacket(dl, n);
    ptclmanEnd();
    iosDlPopLayer();
    *(int *)(w + 0x11C) = n;
}
#endif
