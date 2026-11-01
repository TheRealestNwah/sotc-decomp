typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; int i[4]; } V;
extern char *GetLayoutClass(void *);

typedef struct { int obj; int id; } CollisionRef;
typedef struct {
    int obj;
    int p4;
    float p8;
    float pC;
    float pos[4] __attribute__((aligned(16)));
    char p20[0x10];
    int type;
    char p34[0xC];
    V point;
} CollisionInfo;

static inline void applyMatrix(float *dst, float *m, float *v)
{
    __asm__ __volatile__("lqc2 vf8, 0x0(%2)\n"
                         "lqc2 vf14, 0x0(%1)\n"
                         "lqc2 vf15, 0x10(%1)\n"
                         "lqc2 vf16, 0x20(%1)\n"
                         "lqc2 vf17, 0x30(%1)\n"
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf17, vf8w\n"
                         "sqc2 vf10, 0x0(%0)\n"
                         : : "r"(dst), "r"(m), "r"(v) : "memory");
}

static inline void scaleXYZ(float *dst, float *s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "lqc2 vf6, 0x0(%1)\n"
                         "vmul.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(s) : "memory");
}

void MakeCollisionPointCollisionInfo(CollisionInfo *info, V *point, CollisionRef *ref, float a, float b)
{
    info->point.q = point->q;
    info->p8 = a;
    info->pC = b;
    info->obj = ref->obj;
    info->p4 = ref->id;
    if (ref->id < 0) {
        char *c = GetLayoutClass((void *)ref->obj);
        info->type = 2;
        applyMatrix(info->pos, (float *)(*(int *)(c + 0x164) + (((unsigned char *)ref)[7] & 0x7F) * 64), (float *)point);
        scaleXYZ(info->pos, (float *)(c + 0xA0));
    } else {
        info->type = 3;
    }
}
