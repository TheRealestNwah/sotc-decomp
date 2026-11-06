typedef struct { float f[4]; } __attribute__((aligned(8))) V4;
typedef struct { signed char area; signed char place; char pad2[6]; float x, y, z; char pad14[0x30]; } SavePoint;
typedef struct { char pad[0xC]; int n; SavePoint *list; } SavePointList;
extern SavePointList SH_SavePointDEFAULT;
extern SavePointList *DldSysUndefSymbol;
extern int D_0017AD2C;
extern float D_0017AD24, D_0017AD28;
extern void YattsukeGetSeamlessAreaCenter(float *center, int area);
extern void getPosOnMap(const float *position, float *x, float *z);

static inline void vecAddXYZ(float *dst, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(a), "r"(b) : "memory");
}

static void func_00068168(int unused, SavePoint *e)
{
    SavePointList *l;
    SavePoint *lst;
    int i;
    V4 c;
    V4 v, t;
    float px, pz;

    l = DldSysUndefSymbol == &SH_SavePointDEFAULT ? 0 : &SH_SavePointDEFAULT;
    lst = l->list;

    if (e == 0) {
        for (i = 0; i < l->n; i++) {
            if (lst[i].place == D_0017AD2C) {
                e = &lst[i];
                break;
            }
        }
    }
    if (e != 0) {
        t.f[0] = -e->x;
        t.f[1] = e->y;
        t.f[2] = -e->z;
        t.f[3] = 1.0f;
        v = t;
        YattsukeGetSeamlessAreaCenter(c.f, e->area);
        vecAddXYZ(v.f, v.f, c.f);
        getPosOnMap(v.f, &px, &pz);
        px = px * 512.0f * 0.1f;
        pz = -pz * 512.0f * 0.1f;
        D_0017AD24 = -px;
        D_0017AD28 = -pz;
    }
}
