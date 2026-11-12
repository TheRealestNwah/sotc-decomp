/* Parked draft: per-frame update of the four pad-hint slots (B_0019CCD0): slot state 0 ages
   (timer counts to 5), state 3 fades out, other states fade in; when all four aged out they are
   reset to fading (state 3). ~5 diffs: bnel vs bnez on the gameMode check, and the case-3 constant
   vs loop-counter registers (a1/a2) plus the aged==4 compare register. Permuter queued. */
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
        switch (s->state) {
        case 0:
            s->timer = s->timer + dt;
            if (s->timer >= 5.0f)
                aged++;
            break;
        case 1:
        case 2:
            s->alpha = s->alpha + s->rate * dt * 30.0f;
            if (s->alpha >= 1.0f) {
                s->alpha = 1.0f;
                goto reset;
            }
            break;
        case 3:
            s->alpha = s->alpha + s->rate * dt * 30.0f;
            if (s->alpha <= 0.0f) {
                s->alpha = 0.0f;
            reset:
                s->state = 0;
                s->rate = 0.0f;
                s->timer = 0.0f;
            }
            break;
        }
    }
    if (aged == 4) { for (i = 0; i < 4; i++) { B_0019CCD0[i].state = 3; B_0019CCD0[i].rate = -0.05f; } }
}
#endif
