/* 4 diffs. Returns the cached independent surface boundary of collision node `node`, entry `idx`, computing it on a miss: unpacks 4 shorts (vitof15, then scale and offset by the node's dequant record) or takes the float vector, transforms it by the layout's node matrix with w = 1, stores w * layout scale in .w and registers the entry with EntryModifiedManager. The unpacked shorts go through a function-level Vec4 temporary, which keeps the Original's store/copy order. Remaining: the shape index ($v0 vs $v1) and the node matrix base and index ($a0/$v0) swap registers. */
typedef int s128 __attribute__((mode(TI)));

typedef struct {
    int x, y, z, w;
} IVec __attribute__((aligned(8)));

typedef union {
    s128 q;
    float f[4];
    IVec i;
} Vec4;

typedef struct {
    Vec4 offset;
    Vec4 scale;
} Dequant;

typedef struct {
    char pad0[9];
    unsigned char packed;
    char padA[2];
    Dequant *dequant;
    char pad10[8];
    void *shapes;
    char pad1C[0x74];
} CollisionNode;

typedef struct {
    char pad0[8];
    CollisionNode *nodes;
} CollisionResource;

typedef struct {
    char pad0[8];
    unsigned char *flags;
    char padC[8];
    Vec4 *values;
    char pad18[0x60 - 0x48 - 0x18];
} SurfCache;

typedef struct {
    char pad0[0x48];
    SurfCache cache;
} CacheNode;

typedef struct {
    char pad0[0x24];
    CacheNode *nodes;
} CollisionModel;

typedef struct {
    char pad0[0x20];
    CollisionResource *resource;
} CollisionFile;

typedef struct {
    char pad0[0x9C];
    float scale;
    char padA0[0x15C - 0xA0];
    Vec4 (*matrices)[4];
    char pad160[0x174 - 0x160];
    CollisionModel *model;
    char pad178[0x184 - 0x178];
    CollisionFile *collision;
} LayoutClass;

extern void EntryModifiedManager(void *, int);

static inline void itof15(Vec4 *src)
{
    __asm__ __volatile__("lqc2 vf30, 0x0(%0)\n"
                         "vitof15.xyzw vf29, vf30\n"
                         : : "r"(src) : "memory");
}

static inline void dequant(Vec4 *dst, Dequant *dq)
{
    __asm__ __volatile__("lqc2 vf30, 0x0(%2)\n"
                         "vmul.xyzw vf31, vf29, vf30\n"
                         "lqc2 vf30, 0x0(%1)\n"
                         "vmove.xyzw vf29, vf31\n"
                         "vmove.xyzw vf31, vf29\n"
                         "vadd.xyz vf31, vf29, vf30\n"
                         "sqc2 vf31, 0x0(%0)\n"
                         : : "r"(dst), "r"(dq), "r"(&dq->scale)
                         : "memory");
}

#ifdef NONMATCHING
Vec4 *getLayoutClassCollisionIndepSurfBoundary(LayoutClass *layout, int node, int idx)
{
    SurfCache *cache;
    Vec4 *out;
    CollisionNode *cn;
    Vec4 *src;
    Vec4 dec;
    Vec4 tmp;
    float w;
    Dequant *dq;
    Vec4 dv;

    cache = &layout->model->nodes[node].cache;
    out = &cache->values[idx];
    if (cache->flags[idx] != 0) {
        return out;
    }
    {
        cn = &layout->collision->resource->nodes[node];
        if (cn->packed) {
            short *sh = (short *)cn->shapes + idx * 4;

            dv.i.x = sh[0];
            dv.i.y = sh[1];
            dv.i.z = sh[2];
            dv.i.w = (unsigned short)sh[3];
            tmp.i = dv.i;
            dq = cn->dequant;
            tmp.i.w >>= 1;
            itof15(&tmp);
            dequant(&dec, dq);
            src = &dec;
        } else {
            src = (Vec4 *)cn->shapes + idx;
        }
        w = src->f[3] * layout->scale;
        tmp.q = src->q;
        tmp.f[3] = 1.0f;
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
                             : : "r"(out), "r"(layout->matrices[node]), "r"(&tmp) : "memory");
        out->f[3] = w;
        EntryModifiedManager(cache, idx);
    }
    return out;
}
#endif
