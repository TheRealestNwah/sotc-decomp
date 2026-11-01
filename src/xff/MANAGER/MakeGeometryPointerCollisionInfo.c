extern char *GetLayoutClass(void *);

typedef struct { void *obj; int id; } CollisionRefId;
typedef union { CollisionRefId r; unsigned char b[8]; } CollisionRef;
typedef struct {
    CollisionRef ref;
    float p8;
    float pC;
    float pos[4] __attribute__((aligned(16)));
    char p20[0x10];
    int type;
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

void MakeGeometryPointerCollisionInfo(CollisionInfo *info, float *point, CollisionRef *ref, float a, float b)
{
    info->p8 = a;
    info->pC = b;
    info->ref.r.obj = ref->r.obj;
    info->ref.r.id = ref->r.id;
    if (ref->r.id < 0) {
        char *c = GetLayoutClass(ref->r.obj);
        info->type = 2;
        applyMatrix(info->pos, (float *)(*(int *)(c + 0x164) + (ref->b[7] & 0x7F) * 64), point);
        scaleXYZ(info->pos, (float *)(c + 0xA0));
    } else {
        info->type = 3;
    }
}
