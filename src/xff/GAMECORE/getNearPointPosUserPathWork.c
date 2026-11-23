/* Finds the nearest user-path point whose connected lines match flags,
 * optionally limited to one area; copies its position to out. */

typedef unsigned int u_long128 __attribute__((mode(TI)));

typedef struct {
    char *data;
    unsigned int *pts;
    char *lines;
    char pad[0x18];
} PathE;

typedef struct {
    PathE e[4];
    int n;
    int pad;
} PathSet;

extern PathSet B_001A57E8[];
extern const float RO_001812E4;
extern char *getPointData(unsigned int *, unsigned int);
extern unsigned short *getConnectLineArray(unsigned int *, unsigned int);
extern char *getLineData(char *, int);

static inline PathE *getPathDataAddr(char *w, int id)
{
    PathSet *s = &B_001A57E8[*(int *)(w + 0x3C50)];
    int i;

    for (i = 0; i < s->n; i++) {
        if (id == *(int *)(s->e[i].data + 0x1C))
            return &s->e[i];
    }
    return 0;
}


static inline char *ptByArea(char *w, int idx, int area)
{
    PathE *e = getPathDataAddr(w, area);

    if (e != 0)
        return getPointData(e->pts, idx);
    return 0;
}

static inline unsigned short *clByArea(char *w, int idx, int area)
{
    PathE *e = getPathDataAddr(w, area);

    if (e != 0)
        return getConnectLineArray(e->pts, idx);
    return 0;
}

static inline char *lnByArea(char *w, int idx, int area)
{
    PathE *e = getPathDataAddr(w, area);

    if (e != 0)
        return getLineData(e->lines, idx);
    return 0;
}

int getNearPointPosUserPathWork(char *w, u_long128 *out, u_long128 *pos, int flags, int area)
{
    PathSet *s = &B_001A57E8[*(int *)(w + 0x3C50)];
    unsigned int best = -1;
    int bestId = -1;
    float bestD = RO_001812E4;
    int i;

    for (i = 0; i < s->n; i++) {
        unsigned int *pts = s->e[i].pts;
        int id = *(int *)(s->e[i].data + 0x1C);
        unsigned int j;

        if (pts == 0)
            continue;
        for (j = 0; j < *pts; j++) {
            char *pd = ptByArea(w, j, id);

            if (flags & *(int *)(pd + 0x18)) {
                int hit = 0;
                unsigned short *ln = clByArea(w, j, id);
                unsigned int k;

                for (k = 0; k < *(unsigned int *)(pd + 0x10); k++) {
                    char *l = lnByArea(w, ln[k], id);

                    if (!(*(int *)(l + 8) & 4) && (flags & *(int *)(l + 8))) {
                        hit = 1;
                        break;
                    }
                }
                if (hit) {
                    float d;

                    __asm__ volatile("lqc2 vf5, 0x0(%1)\n"
                                     "lqc2 vf6, 0x0(%2)\n"
                                     "vsub.xyzw vf7, vf5, vf6\n"
                                     "vmul.xyz vf7, vf7, vf7\n"
                                     "vaddy.x vf7, vf7, vf7y\n"
                                     "vaddz.x vf7, vf7, vf7z\n"
                                     "qmfc2.ni $2, vf7\n"
                                     "mtc1 $2, %0\n"
                                     : "=f"(d) : "r"(pd), "r"(pos) : "$2");
                    if (d < bestD && (area == -1 || *(short *)(pd + 0x1C) == area)) {
                        best = j;
                        bestD = d;
                        bestId = id;
                    }
                }
            }
        }
    }
    if (best != -1) {
        char *pd = ptByArea(w, best, bestId);

        if (pd) {
            *out = *(u_long128 *)pd;
            return 1;
        }
    }
    return 0;
}
