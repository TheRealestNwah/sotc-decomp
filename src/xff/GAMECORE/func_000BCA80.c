/* Parked draft: per-frame update of the four pad-hint slots (B_0019CCD0): slot state 0 ages
   (timer counts to 5), state 3 fades out, other states fade in; when all four aged out they are
   reset to fading (state 3). Written from the m2c draft; not yet compared closely. */
#ifdef NONMATCHING
typedef struct {
    float timer;
    float alpha;
    float rate;
    int state;
} Slot;

typedef struct {
    char pad0[8];
    unsigned int buttons;
} PadManagerData;

typedef struct {
    char pad0[0x320];
    int padA;
    int padB;
} GcGlobal;

extern Slot B_0019CCD0[4];
extern int __gameMode;
extern GcGlobal gcGlobalVar;
extern PadManagerData padManagerData;
extern void func_000BC988(int, void *);

static void func_000BCA80(float dt)
{
    int aged = 0;
    Slot *s;
    int i;

    if (((padManagerData.buttons & (1 << gcGlobalVar.padA)) || (padManagerData.buttons & (1 << gcGlobalVar.padB))) &&
        !(__gameMode & 1)) {
        func_000BC988(4, &gcGlobalVar);
    }
    s = B_0019CCD0;
    for (i = 3; i >= 0; i--, s++) {
        if (s->state == 0) {
            s->timer = s->timer + dt;
            if (s->timer >= 5.0f)
                aged++;
        } else if (s->state == 3) {
            s->alpha = s->alpha + s->rate * dt * 30.0f;
            if (s->alpha <= 0.0f) {
                s->alpha = 0.0f;
                s->state = 0;
                s->rate = 0.0f;
                s->timer = 0.0f;
            }
        } else {
            s->alpha = s->alpha + s->rate * dt * 30.0f;
            if (s->alpha >= 1.0f) {
                s->alpha = 1.0f;
                s->state = 0;
                s->rate = 0.0f;
                s->timer = 0.0f;
            }
        }
    }
    if (aged == 4) {
        s = B_0019CCD0 + 0;
        for (i = 3; i >= 0; i--, s++) {
            s->state = 3;
            s->rate = -0.05f;
        }
    }
}
#endif
