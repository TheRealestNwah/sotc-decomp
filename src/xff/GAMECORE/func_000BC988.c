/* Pad-hint slots (B_0019CCD0): func_000BC988 selects a slot, func_000BCA80 ages and fades them each frame.
   One file: with func_000BC988 defined here, reorg fills the gameMode branch like the Original. */
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
extern int D_0017AFEC;
extern float getDemoBarFade(void);
extern float getFadeValue(void);

static void func_000BC988(int sel)
{
    int i;

    if ((getDemoBarFade() == 1.0f && getFadeValue() == 0.0f) || D_0017AFEC != 0) {
        for (i = 0; i < 4; i++) {
            if (sel == i) {
                if (B_0019CCD0[i].state != 1) {
                    B_0019CCD0[i].state = 1;
                    B_0019CCD0[i].rate = 1.0f;
                }
            } else if ((unsigned)(B_0019CCD0[i].state - 1) >= 2U) {
                B_0019CCD0[i].state = 2;
                B_0019CCD0[i].rate = 0.05f;
            }
            if (B_0019CCD0[i].state != 0)
                B_0019CCD0[i].timer = 0.0f;
        }
    }
}

extern int __gameMode;
extern GcGlobal gcGlobalVar;
extern PadManagerData padManagerData;

static void func_000BCA80(float dt)
{
    int aged = 0;
    Slot *s;
    int i;

    if (((padManagerData.buttons & (1 << gcGlobalVar.padA)) || (padManagerData.buttons & (1 << gcGlobalVar.padB))) &&
        !(__gameMode & 1)) {
        func_000BC988(4);
    }
    s = B_0019CCD0;
    for (i = 0; i < 4; i++, s++) {
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
