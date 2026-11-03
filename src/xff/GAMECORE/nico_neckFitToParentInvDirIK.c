typedef int s128 __attribute__((mode(TI)));

extern char *GetCharacterClass(int);
extern int GetGeometryPointerObject(char *);
extern int GetGeometryPointerObjectParentNodeId(char *);
extern float XUnitVector[];
extern void SetQuaternionByAxisRotateVWithNoRegularize(float *, short, float *);

typedef struct {
    int obj;
    s128 *quats;
    int pad8;
    s128 *base;
    char *skel;
    int index;
} NeckWork;

static inline void quatMul(float *d, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf11, 0x0(%0)
"
                         "lqc2 vf12, 0x0(%1)
"
                         "vmul.xyzw vf13, vf11, vf12
"
                         "vaddy.x vf13, vf13, vf13y
"
                         "vaddz.x vf13, vf13, vf13z
"
                         "vsubx.w vf13, vf13, vf13x
"
                         "vmulw.xyz vf14, vf12, vf11w
"
                         "vmulw.xyz vf15, vf11, vf12w
"
                         "vopmula.xyz ACC, vf12, vf11
"
                         "vopmsub.xyz vf16, vf11, vf12
"
                         "vadd.xyz vf13, vf14, vf15
"
                         "vadd.xyz vf13, vf13, vf16
"
                         "sqc2 vf13, 0x0(%2)
"
                         : : "r"(a), "r"(b), "r"(d) : "memory");
}

static inline void rotQuatX(float *d, float *a, int ang)
{
    float r[4] __attribute__((aligned(16)));

    SetQuaternionByAxisRotateVWithNoRegularize(r, ang, XUnitVector);
    quatMul(d, a, r);
}

void nico_neckFitToParentInvDirIK(NeckWork *w)
{
    float r0[4] __attribute__((aligned(16)));
    char *cls = GetCharacterClass(w->obj);

    if (*(int *)(cls + 0x124) != 0) {
        char *geom = cls + 0xC0;
        int pobj = GetGeometryPointerObject(geom);
        int node = GetGeometryPointerObjectParentNodeId(geom);
        char *pcls = GetCharacterClass(pobj);
        int j;
        int k;
        s128 *pq;

        if (pcls == 0 || node == -1)
            return;
        j = *(int *)((node << 6) + *(int *)(*(char **)(pcls + 0x358) + 8) + 0x38);
        if (j == -1)
            return;
        pq = (s128 *)((j << 4) + *(int *)(pcls + 0x154));
        k = *(int *)((w->index << 6) + *(int *)(w->skel + 8) + 0x38);
        rotQuatX(r0, (float *)pq, -0x8000);
        {
            float r2[4] __attribute__((aligned(16)));
            s128 *bq = (s128 *)((k << 4) + (int)w->base);

            __asm__ __volatile__("lqc2 vf11, 0x0(%0)\n"
                                 "vsubw.x vf5, vf0, vf0w\n"
                                 "vmulx.xyz vf11, vf11, vf5x\n"
                                 "sqc2 vf11, 0x0(%1)\n"
                                 : : "r"(bq), "r"(r2) : "memory");
            __asm__ __volatile__("lqc2 vf11, 0x0(%0)\n"
                                 "lqc2 vf12, 0x0(%1)\n"
                                 "vmul.xyzw vf13, vf11, vf12\n"
                                 "vaddy.x vf13, vf13, vf13y\n"
                                 "vaddz.x vf13, vf13, vf13z\n"
                                 "vsubx.w vf13, vf13, vf13x\n"
                                 "vmulw.xyz vf14, vf12, vf11w\n"
                                 "vmulw.xyz vf15, vf11, vf12w\n"
                                 "vopmula.xyz ACC, vf12, vf11\n"
                                 "vopmsub.xyz vf16, vf11, vf12\n"
                                 "vadd.xyz vf13, vf14, vf15\n"
                                 "vadd.xyz vf13, vf13, vf16\n"
                                 "sqc2 vf13, 0x0(%2)\n"
                                 : : "r"(r2), "r"(r0), "r"((s128 *)((w->index << 4) + (int)w->quats)) : "memory");
        }
    }
}
