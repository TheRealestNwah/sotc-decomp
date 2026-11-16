typedef struct {
    int busy;
    float cur;
    float target;
    float step;
    char *name;
} TexAlphaAnim;

extern void *texSearchMopByName(char *);
extern void texScaleClutAlpha(void *, float);
extern void scrRun(void);

typedef struct Ptn Ptn;
extern Ptn rootPtn;
extern unsigned char RO_0017D138[];
extern void *_gcCreateChildScriptObj(void *, void *, Ptn *, int, int, int, void *, void *);

#ifdef NONMATCHING
/* Thread that bootTexAlphaAnim starts: steps cur toward target by step, rescaling the
   texture's CLUT alpha each frame. 18 differing words: the original keeps a separate
   texScaleClutAlpha call and busy store for step == 0 after the shared tail, where gcc
   folds the zero case into it. */
static void func_000420B8(TexAlphaAnim *p)
{
    void *mop = texSearchMopByName(p->name);

    if (p->step > 0.0f) {
        if (p->cur < p->target) {
            p->cur += p->step;
            while (!(p->cur > p->target)) {
                texScaleClutAlpha(mop, p->cur);
                scrRun();
                if (!(p->cur < p->target))
                    goto done;
                p->cur += p->step;
            }
            p->cur = p->target;
        }
    } else if (p->step < 0.0f) {
        if (p->cur > p->target) {
            p->cur += p->step;
            while (!(p->cur < p->target)) {
                texScaleClutAlpha(mop, p->cur);
                scrRun();
                if (!(p->cur > p->target))
                    goto done;
                p->cur += p->step;
            }
            p->cur = p->target;
        }
    } else {
        p->cur = p->target;
    }
done:
    texScaleClutAlpha(mop, p->cur);
    p->busy = 0;
}
#else
extern void func_000420B8();
#endif

void bootTexAlphaAnim(void *parent, int *st, float a, float b)
{
    *(float *)&st[3] = b;
    *(float *)&st[2] = a;
    if (st[0] == 0) {
        st[0] = 1;
        _gcCreateChildScriptObj(func_000420B8, st, &rootPtn, 0x4000, 0, 4, RO_0017D138, parent);
        st = 0;
    }
}
