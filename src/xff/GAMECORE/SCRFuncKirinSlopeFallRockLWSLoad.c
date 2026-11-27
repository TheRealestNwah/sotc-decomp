typedef int s128 __attribute__((mode(TI)));
typedef struct { float v[4]; } __attribute__((aligned(8))) V4;
typedef struct {
    s128 q0;
    char pad10[0x124];
    union { float *p; float f; } pos;
} Layout;

extern char rootPtn[], gcGlobalVar[], ZeroPoint[];
extern void *DldSysUndefSymbol;
extern char *GetSCRCharaAIWorkPtr(int);
extern Layout *GetLayoutClass(int);
extern void GetStageCenter(void *, void *);
extern void GetQuaternionByDegEulerYXZ(void *, float, float, float);
extern int loadObj(char *, void *, void *, void *, int, int);
extern int isysAddGroupWithLinkParam(int, void *, int, int);
extern void func_00061D40(int *rank, int n, int m, float *val);

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

#define LPOS(l) ((l)->pos.p)

static inline void copyQ(float *dst, float *src)
{
    *(s128 *)dst = *(s128 *)src;
}

static inline float distXZ(const float *a, const float *b)
{
    float d;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xz vf7, vf7, vf7\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "vsqrt Q, vf7x\n"
                         "vwaitq\n"
                         "cfc2.ni $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(a), "r"(b) : "$2");
    return d;
}

#ifdef NONMATCHING /* 17 diffs: scheduling of the req[] stores before the loop (reordering the C stores only makes it worse). The stage-center adds read p[k] into a local after c[k], which gives the Original's load order around the k != 1 branch. */
/* Drops up to six falling rocks on the Kirin slope: ranks the five high spawn points by XZ distance from the layout
   position (relative to the stage center), then spawns the three nearest high points and their two low points each. */
void SCRFuncKirinSlopeFallRockLWSLoad(int obj, int a1, int a2, int a3, int t0, int t1, unsigned int *ref)
{
    float p[4] __attribute__((aligned(16)));
    float c[4] __attribute__((aligned(16)));
    float dist[5];
    int rank[9];
    char *fp = GetSCRCharaAIWorkPtr(obj);
    Layout *lay = GetLayoutClass(obj);
    char *s1 = resourceData(ref);
    char *d;
    int i, k, r, o;

    if (*(int *)(fp + 0x41BC) == 0)
        return;
    if (*(int *)(fp + 0x41B0) >= 7) {
        *(int *)(fp + 0x41BC) = 0;
        return;
    }
    if (s1) {
        d = resourceData((unsigned int *)(s1 + 4));
        if (d) {
            float lowPos[11][3] = {{76.0f, 61.0f, 278.0f},      {67.0f, 60.5f, 283.5f},
                                   {57.0f, 60.199997f, 285.8f}, {45.0f, 60.0f, 284.5f},
                                   {36.399998f, 60.5f, 279.69998f}, {27.0f, 60.0f, 275.0f},
                                   {22.5f, 60.5f, 265.0f},      {14.799999f, 60.3f, 258.5f},
                                   {5.0f, 60.0f, 253.0f},       {3.0f, 58.0f, 241.5f},
                                   {2.3f, 56.0f, 231.0f}};
            float lowRot[11] = {-160.0f, -163.0f, -174.0f, 140.0f, 160.0f, 135.0f,
                                95.0f,   160.0f,  130.0f,  85.5f,  105.0f};
            float highPos[5][3] = {{75.0f, 51.0f, 261.0f},
                                   {64.0f, 49.5f, 266.0f},
                                   {48.699997f, 50.0f, 266.8f},
                                   {33.199997f, 50.0f, 263.5f},
                                   {26.0f, 50.0f, 251.0f}};
            float highRot[5] = {23.0f, 31.5f, 0.0f, -60.0f, -37.0f};
            int req[16];
            float scale[4] __attribute__((aligned(16)));
            float quat[4] __attribute__((aligned(16)));
            V4 pos2;
            V4 pos;
            i = 0;
            copyQ(p, LPOS(lay));
            GetStageCenter(c, LPOS(lay));
            for (; i < 3; i++) {
                p[i] -= c[i];
                if (i != 1)
                    p[i] = -p[i];
            }
            c[3] = 1.0f;
            for (i = 0; i < 5; i++) {
                c[0] = highPos[i][0];
                c[1] = highPos[i][1];
                c[2] = highPos[i][2];
                dist[i] = distXZ(p, c);
            }
            func_00061D40(rank, 3, 5, dist);
            for (i = 0; i < 3; i++) {
                rank[3 + i * 2] = rank[i] * 2;
                rank[4 + i * 2] = rank[i] * 2 + 1;
            }
            pos.v[0] = *(float *)(s1 + 0x30);
            pos.v[1] = *(float *)(s1 + 0x34);
            pos.v[2] = *(float *)(s1 + 0x38);
            pos.v[3] = 1.0f;
            pos2 = pos;
            scale[0] = -*(float *)(s1 + 0x18);
            scale[1] = *(float *)(s1 + 0x1C);
            scale[2] = -*(float *)(s1 + 0x20);
            scale[3] = 1.0f;
            GetQuaternionByDegEulerYXZ(quat, *(float *)(s1 + 0x24), -*(float *)(s1 + 0x28), *(float *)(s1 + 0x2C));
            req[1] = (int)scale;
            req[2] = (int)quat;
            req[3] = (int)&pos2;
            req[0] = 0;
            req[8] = 0;
            req[4] = *(int *)(s1 + 8);
            req[5] = (int)resourceData((unsigned int *)(s1 + 0x3C));
            *(float *)&req[6] = *(float *)(s1 + 0x40);
            req[7] = *(int *)(s1 + 0x44);
            req[11] = 1;
            req[9] = 0;
            req[10] = 0;
            req[0] = (int)ZeroPoint;
            req[12] = *(int *)(s1 + 0x14);
            p[3] = 1.0f;
            req[13] = 0;
            req[14] = 0;
            for (i = 0; i < 9;) {
                float *rot;
                r = rank[i];
                k = 0;
                if (i < 3) {
                    p[0] = highPos[r][0];
                    p[1] = highPos[r][1];
                    p[2] = highPos[r][2];
                    GetStageCenter(c, LPOS(lay));
                    for (; k < 3; k++) {
                        float *pk = &p[k];
                        float v = c[k];
                        float w = *pk;
                        if (k != 1)
                            v = -v;
                        *pk = w + v;
                        if (k != 1)
                            *pk = -*pk;
                    }
                    c[1] = highRot[r];
                } else {
                    p[0] = lowPos[r][0];
                    p[1] = lowPos[r][1];
                    p[2] = lowPos[r][2];
                    GetStageCenter(c, LPOS(lay));
                    for (; k < 3; k++) {
                        float *pk = &p[k];
                        float v = c[k];
                        float w = *pk;
                        if (k != 1)
                            v = -v;
                        *pk = w + v;
                        if (k != 1)
                            *pk = -*pk;
                    }
                    c[1] = lowRot[r];
                }
                c[3] = 1.0f;
                c[0] = 0.0f;
                c[2] = 0.0f;
                req[1] = (int)p;
                req[2] = (int)c;
                o = loadObj(d, req, rootPtn, gcGlobalVar + 0x280, 1, 4);
                if (o) {
                    isysAddGroupWithLinkParam(o, gcGlobalVar + 0x280 + 0x84, 0, 0);
                    (*(int *)(fp + 0x41B0))++;
                }
                i++;
                if (*(int *)(fp + 0x41B0) >= 6) {
                    *(int *)(fp + 0x41BC) = 0;
                    i = 9;
                }
            }
        }
    }
}
#endif
