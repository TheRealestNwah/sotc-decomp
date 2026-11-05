typedef unsigned int u_long128 __attribute__((mode(TI)));

typedef struct {
    float pos[4];
    float dir[4];
    char pad[0x10];
} WormEnt;

typedef struct {
    WormEnt ent[32];
    float dist;
    int idx;
    int flag;
    char reset;
    char valid[32];
} WormHist;

extern void func_001287F8(WormHist *w);

static inline float vecDist2(void *a, void *b)
{
    float d;
    int prev;

    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vaddy.x vf7, vf7, vf7y\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "qmfc2.ni $2, vf7\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(a), "r"(b) : "$2");
    return d;
}

static void func_001289B8(WormHist *w, u_long128 *pos, u_long128 *dir)
{
    int i;
    float d;
    int prev;

    if (w->reset) {
        for (i = 0; i < 32; i++) {
            *(u_long128 *)w->ent[i].pos = *pos;
            *(u_long128 *)w->ent[i].dir = *dir;
            w->valid[i] = 1;
        }
        w->reset = 0;
    }
    prev = (w->idx + 31) % 32;
    d = vecDist2(&w->ent[prev], &w->ent[w->idx]);
    if (w->dist * w->dist < d) {
        w->idx++;
        if (w->idx == 32) {
            w->idx = 0;
        }
        w->valid[w->idx] = 0;
    }
    *(u_long128 *)w->ent[w->idx].pos = *pos;
    *(u_long128 *)w->ent[w->idx].dir = *dir;
    func_001287F8(w);
    w->flag = 1;
}
