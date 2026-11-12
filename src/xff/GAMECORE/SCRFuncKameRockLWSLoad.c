typedef int s128 __attribute__((mode(TI)));

extern char rootPtn[], gcGlobalVar[], ZeroPoint[], RO_00180AC0[];
extern void *DldSysUndefSymbol;
extern char *GetSCRCharaAIWorkPtr(int);
extern char *getSCRDataCtrlWork(int);
extern int getPlayerColCont2(int);
extern int ColCont2_IsColStatus(int, int, int);
extern float iosGetRandom(void);
extern int SCRGetCollision(void *, void *, void *, void *);
extern void GetQuaternionByDegEulerYXZ(void *, float, float, float);
extern int loadObj(char *, void *, void *, void *, int, int);
extern void isysAddGroupWithLinkParam(int, void *, int, int);

static inline char *resourceData(unsigned int *reference)
{
    unsigned int encoded = *reference;
    unsigned int offset = encoded & 0x3FFFF;
    char *module;
    if (offset)
        module = *(char **)((char *)reference - offset);
    else
        module = 0;
    if (module && module != DldSysUndefSymbol) {
        int index = (encoded >> 18) & 0xFFF;
        return *(char **)(module + 0x10) + index * *(int *)(*(char **)(module + 8) + 0xC);
    }
    return 0;
}

#ifdef NONMATCHING /* 343 diffs, 347 vs 368 words: request-block layout and dld-resolve branch forms not matched */
void SCRFuncKameRockLWSLoad(int obj, int limit, int base, int unused, int u1, int u2, unsigned int *ref,
                            float f12, float f13, float f14, float f15)
{
    float centre[4] __attribute__((aligned(16)));
    float pos[4] __attribute__((aligned(16)));
    float hit[4] __attribute__((aligned(16)));
    float p70[4] __attribute__((aligned(16)));
    float p80[4] __attribute__((aligned(16)));
    int req[24] __attribute__((aligned(16)));
    float d0[4] __attribute__((aligned(16)));
    float q[4] __attribute__((aligned(16)));
    float m0[4] __attribute__((aligned(16)));
    float sc[4] __attribute__((aligned(16)));
    float tp[4] __attribute__((aligned(16)));
    float rv[4] __attribute__((aligned(16)));
    char *ai = GetSCRCharaAIWorkPtr(obj);
    char *work = getSCRDataCtrlWork(obj);
    char *r = resourceData(ref);
    char *tpl, *ctl;
    int tries = 0;
    int off, k;
    float base_f, t, u;

    *(s128 *)centre = *(s128 *)RO_00180AC0;
    if (*(int *)(work + 0x41C8) < limit && r) {
        tpl = resourceData((unsigned int *)(r + 4));
        if (tpl) {
            if (ColCont2_IsColStatus(getPlayerColCont2(*(int *)(work + 0x4078)), 0x1E00000, 0x200000))
                off = base + 1, *(s128 *)pos = **(s128 **)(*(char **)(work + 0x407C) + 0x134);
            else {
                off = base + 5;
                *(s128 *)pos = *(s128 *)centre;
            }
            *(s128 *)hit = *(s128 *)pos;
            while (*(int *)(work + 0x41C8) < limit) {
                int n = *(int *)(work + 0x41C8);
                base_f = (float)n * 3.5f;
                k = n & 3;
                switch (k) {
                case 0:
                    t = base_f + (float)off;
                    hit[0] = pos[1] - t * iosGetRandom();
                    u = t * iosGetRandom();
                    hit[2] = pos[2] - u;
                    break;
                case 1:
                    t = base_f + (float)off;
                    hit[0] = pos[1] - t * iosGetRandom();
                    u = t * iosGetRandom();
                    hit[2] = pos[2] + u;
                    break;
                case 2:
                    t = base_f + (float)off;
                    hit[0] = pos[1] + t * iosGetRandom();
                    u = t * iosGetRandom();
                    hit[2] = pos[2] - u;
                    break;
                case 3:
                    t = base_f + (float)off;
                    hit[0] = pos[1] + t * iosGetRandom();
                    u = t * iosGetRandom();
                    hit[2] = pos[2] + u;
                    break;
                }
                *(s128 *)p70 = *(s128 *)hit;
                *(s128 *)p80 = *(s128 *)hit;
                p70[1] = 70.0f;
                p80[1] = -30.0f;
                if (SCRGetCollision(centre, p70, p80, gcGlobalVar + 0x248)) {
                    hit[1] = f12 + (pos[1] + f13 * iosGetRandom());
                    sc[0] = sc[1] = sc[2] = f14;
                    sc[3] = 1.0f;
                    tp[0] = *(float *)(tpl + 0x30);
                    tp[1] = *(float *)(tpl + 0x34);
                    tp[2] = *(float *)(tpl + 0x38);
                    tp[3] = 1.0f;
                    rv[0] = -*(float *)(tpl + 0x18);
                    rv[1] = *(float *)(tpl + 0x1C);
                    rv[2] = -*(float *)(tpl + 0x20);
                    rv[3] = 1.0f;
                    GetQuaternionByDegEulerYXZ(m0, *(float *)(tpl + 0x24), -*(float *)(tpl + 0x28), *(float *)(tpl + 0x2C));
                    req[1] = (int)hit;
                    req[2] = (int)m0;
                    req[3] = (int)rv;
                    req[4] = *(int *)(tpl + 8);
                    req[5] = (int)resourceData((unsigned int *)(tpl + 0x3C));
                    *(float *)&req[6] = *(float *)(tpl + 0x40);
                    req[7] = *(int *)(tpl + 0x44);
                    req[8] = 0;
                    req[9] = 0;
                    req[10] = 0;
                    req[11] = 1;
                    req[12] = *(int *)(tpl + 0x14);
                    req[13] = 0;
                    req[14] = 0;
                    sc[0] += f15 * iosGetRandom();
                    sc[1] += f15 * iosGetRandom();
                    sc[2] += f15 * iosGetRandom();
                    req[3] = (int)sc;
                    req[0] = (int)tp;
                    if (loadObj(r, req, rootPtn, gcGlobalVar + 0x280, 1, 4)) {
                        *(int *)(work + 0x41C8) += 1;
                        isysAddGroupWithLinkParam(0, gcGlobalVar + 0x280 + 0x84, 0, 0);
                    }
                } else {
                    *(s128 *)pos = *(s128 *)centre;
                    *(s128 *)hit = *(s128 *)pos;
                    tries++;
                    if (tries >= 11)
                        break;
                }
            }
        }
    }
}
#endif
