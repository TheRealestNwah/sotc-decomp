/* Samples a keyframe curve of (t, v) pairs at c->t, wrapping or clamping t past the last key, and stores the interpolated value in c->val. */
typedef struct {
    char pad0[8];
    int flags;
    float t;
    float val;
} Ctl;

typedef struct {
    float t;
    float v;
} Key;

#ifdef NONMATCHING
/* Parked: 11 diffs, same size. Remaining: the flag update uses $v0 instead of $v1, the key loop keeps c->t in one register (the Original copies it to $f0 for the == test), sets prev before loading the first key (the Original sets it in the delay slot), and puts k second in the prev*8 + k add. */
float func_00093138(Ctl *c, Key *k, int n)
{
    Key *p;
    Key *q;
    int i;
    int prev;
    int nm1;
    float pt;

    if (c && k) {
        while (c->t > k[n - 1].t) {
            if (c->flags >= 0) {
                c->t = 0.0f;
                c->flags = (c->flags & 0x87FFFFFF) | 0x08000000;
            } else if (k[n - 1].t == 0.0f) {
                c->t = 0.0f;
            } else {
                c->t -= k[n - 1].t;
            }
        }
        nm1 = n - 1;
        p = k;
        i = 0;
        if (i < n) {
            prev = nm1;
            pt = p->t;
            goto test;
        loop:
            if (c->t < pt) {
                q = &k[prev];
                return c->val = q->v + (p->v - q->v) * (c->t - q->t) / (pt - q->t);
            }
            i++;
            p++;
            prev = i - 1;
            if (i >= n) {
                goto end;
            }
            pt = p->t;
            if (prev < 0) {
                prev = nm1;
            }
        test:
            if (c->t != pt) {
                goto loop;
            }
            return c->val = p->v;
        }
    }
end:
    return 1.0f;
}
#else
extern float func_00093138(Ctl *c, Key *k, int n);
#endif
