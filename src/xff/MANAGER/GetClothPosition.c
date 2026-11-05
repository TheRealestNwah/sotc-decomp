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

static inline void lerpVec(void *out, void *a, void *b, float t)
{
    __asm__ __volatile__(".set noreorder\n"
                         "mfc1 $8, %0\n"
                         "qmtc2.ni $8, vf7\n"
                         "lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsubx.w vf8, vf0, vf7x\n"
                         "vmulax.xyz ACC, vf5, vf7x\n"
                         "vmaddw.xyz vf5, vf6, vf8w\n"
                         "sqc2 vf5, 0x0(%3)\n"
                         ".set reorder\n"
                         : : "f"(t), "r"(a), "r"(b), "r"(out) : "memory", "$8");
}

void GetClothPosition(float *out, void *layout, int cloth, int vertex, float time)
{
    ClothFrame f;
    ClothEntry *entry = &(**(ClothEntry ***)(GetLayoutClass(layout) + 0x178))[cloth];
    ClothResource *res = entry->resource;
    ClothTrack *track;
    s128 *positions;
    s128 *cur;

    calcClothFrame(&f, res, vertex, time);
    track = entry->tracks;
    track += vertex;
    positions = track->positions;
    cur = &positions[f.frame];
    if (f.rate == 0.0f) {
        *(s128 *)out = *cur;
    } else {
        lerpVec(out, &positions[f.next], cur, f.rate);
    }
    out[3] = 1.0f;
}
