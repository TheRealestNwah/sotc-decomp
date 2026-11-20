/* Root scale ratio update: clamps o->r (0x160) toward the chara's current ratio by a per-frame step, limits it to [p->f58, p->f38], eases it with getValueInterp and, when shrinking, limits it by the two analyzeMotionProperty2 speeds, then hands it to SCRSetRootScaleRatio / SCRSetCharaRootTurnScaleRatio. The analyzeMotionProperty2 prototype lists its float arguments before the pointers so gcc sets them up in the Original order. Mot's elem shares a union with a float so its load stays after the v[1] store, as in the Original. */
typedef struct { char pad0[0x360]; char b360; char pad361[2]; char b363; char pad364[0x20C]; float f570; char pad574[0x1DC]; int i750; } Chara;
typedef struct { union { char *elem; float f0; } u; int pad4; float f8; float fC; } Mot;
typedef struct { char pad0[0x38]; float f38; char pad3C[0x1C]; float f58; float f5C; float f60; char pad64[8]; int i6C; char pad70[4]; float f74; float f78; char pad7C[0x1C]; int i98; } Prm;
typedef struct { char pad0[8]; int h; char padC[8]; Chara *c; char pad18[4]; Mot *m; char pad20[0xAC]; Prm *p; char padD0[0x74]; float f144; float f148; char pad14C[0x14]; float r; } Obj;
typedef struct { char pad0[0x190]; float f190; } GV;
extern GV gcGlobalVar;
extern void analyzeMotionProperty(int, char *, float *, float *, float *, float, float);
extern void analyzeMotionProperty2(int, char *, float, float, float, float *, float *, float *);
extern float getValueInterp(float, float, float, float);
extern void SCRSetRootScaleRatio(int, float);
extern void SCRSetCharaRootTurnScaleRatio(int, float);
extern float fabsf(float);

static void func_0010F338(Obj *o)
{
    float v[3];
    Prm *p = o->p;
    float cur = o->c->f570;
    float r, step, t, d;
    Chara *c;

    analyzeMotionProperty(o->h, o->m->u.elem, 0, 0, v, 1.0f, 0.0f);
    if (!((*(unsigned int *)(o->m->u.elem + 0x68) >> 4) & 1)) {
        o->r = 1.0f;
    } else {
        c = o->c;
        if (c->b360 == 0 && c->b363 != 0 && v[0] != 0.0f) {
            if (p->f78 != o->r && fabsf(p->f78 - o->r) <= 0.02f)
                o->r = p->f78;
        }
    }
    p->f78 = o->r;
    if (o->r != cur) {
        step = p->f5C * gcGlobalVar.f190;
        if (cur < o->r) {
            if (o->c->i750 == p->i6C && fabsf(o->f148) > 0.052359877f && o->f144 > 0.01f) {
                t = fabsf(o->r - cur) / o->f144 * gcGlobalVar.f190;
                if (t < step)
                    step = t;
            }
            if (step < o->r - cur)
                o->r = cur + step;
        } else if (o->r < cur && -step > o->r - cur) {
            o->r = cur - step;
        }
    }
    if (p->f38 < o->r)
        o->r = p->f38;
    else if (o->r < p->f58)
        o->r = p->f58;
    o->r = getValueInterp(p->f74, o->r - cur, p->f60, gcGlobalVar.f190) + cur;
    if (p->f38 < o->r)
        o->r = p->f38;
    else if (o->r < p->f58)
        o->r = p->f58;
    d = o->r - cur;
    if (d < 0.0f && (p->i98 != 0 || o->c->b363 != 0)) {
        if (o->m->fC != 0.0f) {
            if (v[0] != 0.0f) {
            analyzeMotionProperty2(o->h, o->m->u.elem, 1.0f, 0.0f, o->m->fC, 0, 0, &v[1]);
            v[1] *= cur;
            analyzeMotionProperty2(o->h, o->m->u.elem, 1.0f, 0.0f, o->m->f8, 0, 0, &v[2]);
            {
                float rr = o->r, a = v[1], b = v[2];
                float t = b * rr;
                if ((a > 0.0f && t < a) || (a < 0.0f && a < t)) {
                    if (b != 0.0f)
                        o->r = fabsf(a / b);
                    else
                        o->r = cur;
                }
            }
            if (p->f38 < o->r)
                o->r = p->f38;
            }
        } else {
            o->r = cur;
        }
        d = o->r - cur;
    }
    p->f74 = d;
    __asm__ volatile("" ::: "memory");
    p->i98 = o->c->b363;
    __asm__ volatile("" ::: "memory");
    SCRSetRootScaleRatio(o->h, o->r);
    SCRSetCharaRootTurnScaleRatio(o->h, o->r);
}
