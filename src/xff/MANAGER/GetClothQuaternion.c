typedef int s128 __attribute__((mode(TI)));

typedef struct ClothFrame {
    int frame;
    int next;
    float rate;
} ClothFrame;

typedef struct ClothVertex {
    char pad0[4];
    float interval;
    char pad8[0x1C];
} ClothVertex;

typedef struct ClothResource {
    char pad0[8];
    int frames;
    char padC[0x1C];
    ClothVertex *vertices;
} ClothResource;

typedef struct ClothTrack {
    char pad0[0x10];
    s128 *positions;
    char pad14[4];
} ClothTrack;

typedef struct ClothEntry {
    ClothResource *resource;
    char pad4[8];
    ClothTrack *tracks;
    char pad10[0x80];
} ClothEntry;

extern char *GetLayoutClass(void *);

static inline void calcClothFrame(ClothFrame *f, ClothResource *res, int vertex, float time)
{
    int last;
    float interval = res->vertices[vertex].interval;

    time = time < 0.0f ? 0.0f : time;

    f->frame = time / interval;
    f->next = f->frame + 1;
    last = res->frames - 1;
    if (last < f->frame || last < f->next) {
        f->next = last;
        f->frame = last;
        f->rate = 0.0f;
    } else {
        f->rate = (time - f->frame * interval) / interval;
    }
}

extern s128 XUnitVector;
extern void GetQuaternionByAxisDirZY(s128 *, s128 *, s128 *);
extern void SetQuaternionByAxisRotateVWithNoRegularize(s128 *, int, s128 *);

static inline void subNormalize(s128 *out, s128 *a, s128 *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(out) : "memory");
}

static inline void localDirY(s128 *out, s128 *q)
{
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "vmul.xyzw vf5, vf4, vf4\n"
                         "vmr32.xyzw vf6, vf4\n"
                         "vmul.xyzw vf7, vf6, vf4\n"
                         "vmr32.xyzw vf6, vf6\n"
                         "vmul.xyzw vf8, vf6, vf4\n"
                         "vsubx.z vf6, vf0, vf5x\n"
                         "vsuby.z vf6, vf6, vf5y\n"
                         "vaddw.y vf6, vf7, vf7w\n"
                         "vsuby.x vf6, vf8, vf8y\n"
                         "vsub.w vf6, vf0, vf0\n"
                         "vadd.w vf5, vf0, vf0\n"
                         "vmulw.xyz vf6, vf6, vf5w\n"
                         "vaddw.z vf6, vf6, vf0w\n"
                         "sqc2 vf6, 0x0(%0)\n"
                         : : "r"(out), "r"(q) : "memory");
}

static inline void scaleXYZ(s128 *out, s128 *a, float factor)
{
    __asm__ __volatile__("lqc2 vf5, 0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0(%0)\n"
                         : : "r"(out), "r"(a), "r"(factor) : "memory");
}

static inline void mulQuat(s128 *out, s128 *a, s128 *b)
{
    __asm__ __volatile__("lqc2 vf11, 0x0(%1)\n"
                         "lqc2 vf12, 0x0(%2)\n"
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
                         "sqc2 vf13, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

void GetClothQuaternion(s128 *out, void *layout, int cloth, int vertex, float time)
{
    ClothFrame f;
    s128 dir[1];
    s128 up[1];
    s128 rot;
    char *lc = GetLayoutClass(layout);
    ClothEntry *entry = &(**(ClothEntry ***)(lc + 0x178))[cloth];
    ClothResource *res = entry->resource;
    ClothTrack *track;
    s128 *positions;
    s128 *q;

    calcClothFrame(&f, res, vertex, time);
    track = entry->tracks;
    track += vertex;
    positions = track->positions;
    subNormalize(dir, &positions[f.next], &positions[f.frame]);
    localDirY(up, *(s128 **)(lc + 0x13C));
    scaleXYZ(up, up, -1.0f);
    GetQuaternionByAxisDirZY(out, dir, up);
    q = *(s128 **)(lc + 0x13C);
    SetQuaternionByAxisRotateVWithNoRegularize(&rot, 0x4000, &XUnitVector);
    mulQuat(out, q, &rot);
}
