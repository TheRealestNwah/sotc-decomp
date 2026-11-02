typedef int Quadword __attribute__((mode(TI)));
typedef union Vector { Quadword q; float f[4]; } Vector;
typedef struct GlobalLight {
    unsigned char unknown[0x114];
    const char *name;
} GlobalLight;
typedef struct LightCollection {
    Vector position;
    float inner;
    float outer;
    int flags;
    unsigned char unknown01C[0x530 - 0x1C];
    int count;
    unsigned char unknown534[0x540 - 0x534];
    GlobalLight *selected;
} LightCollection;
extern LightCollection *D_00136C00;
extern int ExecGlobalLightMan(LightCollection *, LightCollection *);
extern void soundSetRevMode(int, int);
extern int strncmp(const char *, const char *, unsigned int);
extern char RO_0013F840[];

void SetCameraReverbFlag(Vector *position)
{
    LightCollection *work = D_00136C00;
    int selected;
    work->position.q = position->q;
    work->inner = 0.0f;
    work->outer = work->inner;
    work->position.f[3] = 1.0f;
    work->flags = 0;
    work->count = 0;
    selected = ExecGlobalLightMan(work, work) > 0;
    soundSetRevMode(1, 1);
    if (selected && strncmp(work->selected->name, RO_0013F840, 6) != 0)
        soundSetRevMode(0, 1);
    selected = 0;
}
