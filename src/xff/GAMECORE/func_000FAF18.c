typedef int Quadword __attribute__((mode(TI)));
typedef struct { char pad[0x1C]; int x1C; } Obj;
typedef struct { Obj *obj; void *x4; char pad[0x1C]; } Entry;
typedef struct { Entry e[4]; int n; char pad[4]; } Table;
typedef struct {
    float pos[4];
    char pad10[0x10];
    float dir[4];
    char pad30[0xEC - 0x30];
    int xEC;
    char padF0[0x3C50 - 0xF0];
    int x3C50;
} Game;
extern Table B_001A57E8[];
extern float *getPointData(void *, int);

static inline void normalizeXYZ(float *output, const float *input)
{
    __asm__ __volatile__(".set noreorder\n"
        "lqc2 vf5, 0x0(%1)\n"
        "vmul.xyz vf7, vf5, vf5\n"
        "vmulax.w ACC, vf0, vf7x\n"
        "vmadday.w ACC, vf0, vf7y\n"
        "vmaddz.w vf7, vf0, vf7z\n"
        "vrsqrt Q, vf0w, vf7w\n"
        "vwaitq\n"
        "vmulq.xyz vf5, vf5, Q\n"
        "sqc2 vf5, 0x0(%0)\n"
        ".set reorder\n"
        : : "r"(output), "r"(input) : "memory");
}

static inline void subXYZW(float *output, const float *a, const float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(output), "r"(a), "r"(b) : "memory");
}

static inline float dotXYZ(const float *a, const float *b)
{
    float r;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vaddw.x vf7, vf0, vf0w\n"
                         "vmul.xyz vf6, vf5, vf6\n"
                         "vaddax.x ACC, vf0, vf6x\n"
                         "vmadday.x ACC, vf7, vf6y\n"
                         "vmaddz.x vf6, vf7, vf6z\n"
                         "qmfc2.ni $2, vf6\n"
                         "mtc1 $2, %0\n"
                         : "=f"(r) : "r"(a), "r"(b) : "$2");
    return r;
}

static inline Entry *findEntry(Game *g, int id)
{
    Table *t = &B_001A57E8[g->x3C50];
    int i;
    for (i = 0; i < t->n; i++) {
        if (id == t->e[i].obj->x1C) return &t->e[i];
    }
    return 0;
}

static int func_000FAF18(Game *g, int unused, int idx, int id, float maxDot, float *outDot, int *outIdx, int *outId)
{
    float v[4] __attribute__((aligned(16)));
    float a[4] __attribute__((aligned(16)));
    float b[4] __attribute__((aligned(16)));
    Entry *e = findEntry(g, id);
    float *pt = e ? getPointData(e->x4, idx) : 0;
    float dot;

    if (maxDot <= -1.0f) return 1;
    subXYZW(v, pt, g->pos);
    normalizeXYZ(v, v);
    if (g->xEC) {
        *(Quadword *)b = *(Quadword *)g->dir;
        *(Quadword *)a = *(Quadword *)v;
        b[1] = 0.0f;
        a[1] = 0.0f;
        normalizeXYZ(a, a);
        normalizeXYZ(b, b);
        dot = dotXYZ(a, b);
    } else {
        dot = dotXYZ(v, g->dir);
    }
    if (dot < maxDot) {
        if (outDot != 0 && *outDot < dot) {
            *outDot = dot;
            if (outIdx) *outIdx = idx;
            if (outId) *outId = id;
        }
        return 0;
    }
    return 1;
}
