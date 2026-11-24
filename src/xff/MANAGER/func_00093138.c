/* Samples a keyframe curve of (t, v) pairs at c->t, wrapping or clamping t past the last key, and stores the interpolated value in c->val. */
typedef struct {
    char pad0[8];
    unsigned int lo : 27;
    unsigned int anim : 4;
    unsigned int loop : 1;
    float t;
    float val;
} Ctl;

typedef struct {
    float t;
    float v;
} Key;

/* The flags word holds a 4-bit animation field at bit 27 and a loop flag in the
 * sign bit. The empty asm keeps a copy of c->t for the == test, as the Original
 * does, and orders n - 1 before it. */
static float func_00093138(Ctl *c, Key *k, int n)
{
    Key *p;
    Key *q;
    int i;
    int prev;
    int nm1;
    float pt;
    float ct;

    if (c && k) {
        while (c->t > k[n - 1].t) {
            if (!c->loop) {
                c->t = 0.0f;
                c->anim = 1;
            } else if (k[n - 1].t == 0.0f) {
                c->t = 0.0f;
            } else {
                c->t -= k[n - 1].t;
            }
        }
        nm1 = n - 1;
        p = k;
        ct = c->t;
        __asm__ ("" : "+f"(ct) : "r"(nm1));
        i = 0;
        if (i < n) {
            pt = p->t;
            prev = nm1;
            goto test;
        loop:
            if (c->t < pt) {
                q = (Key *)(prev * 8 + (int)k);
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
            if (ct != pt) {
                goto loop;
            }
            return c->val = p->v;
        }
    }
end:
    return 1.0f;
}
