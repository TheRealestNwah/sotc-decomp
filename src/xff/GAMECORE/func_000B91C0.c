typedef struct {
    char pad0[0x170];
    int state;
    char pad174[0xC8];
    float speed;
} SmallWork;

typedef struct {
    char pad0[0x190];
    float dt;
} GlobalVar;
extern GlobalVar gcGlobalVar;

#define ABS(x) ((x) < 0.0f ? -(x) : (x))
#define NABS(x) ((x) < 0.0f ? (x) : -(x))

static void func_000B91C0(SmallWork *w, float acc, float target)
{
    switch (w->state) {
    case 0x10:
        w->speed += -w->speed * 4.0f * gcGlobalVar.dt;
        break;
    case 0x11:
        if (w->speed < ABS(target)) {
            w->speed += acc * gcGlobalVar.dt;
            if (ABS(target) < w->speed)
                w->speed = ABS(target);
        } else {
            w->speed -= acc * gcGlobalVar.dt;
            if (w->speed < ABS(target))
                w->speed = ABS(target);
        }
        break;
    case 0x12:
        if (NABS(target) < w->speed) {
            w->speed -= acc * gcGlobalVar.dt;
            if (w->speed < NABS(target))
                w->speed = NABS(target);
        } else {
            w->speed += acc * gcGlobalVar.dt;
            if (NABS(target) < w->speed)
                w->speed = NABS(target);
        }
        break;
    }
}
