/* Root position delta over a motion's span: the current root position minus
 * the sampled one, corrected by the first and last keyframes of the track.
 * The keyframe vector is a union with shorts: the Original's keyframe
 * decode stores each component before the next short load, which gcc only
 * keeps when the store's alias set covers short. */

typedef union {
    float v[4];
    short s[8];
} Vec4 __attribute__((aligned(16)));

typedef struct {
    float x, sx, y, sy, z, sz;
    short *q;
} PosData;

typedef struct {
    int w;
    PosData *data;
} PosTrack;

extern void func_0003A168(Vec4 *, PosTrack *, float);

static inline void subXYZ(Vec4 *out, Vec4 *a, Vec4 *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void sub4(Vec4 *out, Vec4 *a, Vec4 *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void add4(Vec4 *out, Vec4 *a, Vec4 *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

/* fmt 0: one raw position; 2: shorts scaled by 1/32767 plus an offset;
 * otherwise raw positions, 12 bytes per keyframe. */
static inline void getPos(Vec4 *o, int fmt, PosData *p, int i)
{
    if (p != 0) {
        o->v[3] = 1.0f;
        switch (fmt) {
        default: {
            float *f = (float *)p + i * 3;
            o->v[0] = f[0];
            o->v[1] = f[1];
            o->v[2] = f[2];
            break;
        }
        case 2: {
            short *q = p->q + i * 3;
            o->v[0] = q[0] * p->sx * (1.0f / 32767.0f) + p->x;
            o->v[1] = q[1] * p->sy * (1.0f / 32767.0f) + p->y;
            o->v[2] = q[2] * p->sz * (1.0f / 32767.0f) + p->z;
            break;
        }
        case 0: {
            o->v[0] = ((float *)p)[0];
            o->v[1] = ((float *)p)[1];
            o->v[2] = ((float *)p)[2];
            break;
        }
        }
    }
}

static void func_0003A4A8(Vec4 *out, Vec4 *cur, PosTrack *trk, int n, float t, float r)
{
    Vec4 base;
    Vec4 first;
    Vec4 last;
    Vec4 d;
    Vec4 e;

    func_0003A168(&base, trk, r);
    if (r <= t) {
        subXYZ(out, cur, &base);
        return;
    }
    getPos(&first, (trk->w >> 16) & 0xFF, trk->data, 0);
    getPos(&last, (trk->w >> 16) & 0xFF, trk->data, n - 1);
    sub4(&d, &last, &base);
    sub4(&e, cur, &first);
    add4(out, &d, &e);
}
