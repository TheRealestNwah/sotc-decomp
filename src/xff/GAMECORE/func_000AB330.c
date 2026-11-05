typedef struct {
    char pad0[0x258];
    int prevKind;
    int kind;
    char pad260[0x10];
    float timer;
    char pad274[4];
    int x278;
    int x27C;
    int x280;
    char pad284[4];
    int x288;
    int x28C;
    char pad290[0x4C];
    int x2DC;
    int x2E0;
    char pad2E4[0x38];
    int x31C;
    int x320;
} Work;

extern void *isysGetThisSubThread(void);
extern float iosGetRandom(void);

static void func_000AB330(Work *w)
{
    float r;

    isysGetThisSubThread();
    if (w->prevKind == w->kind)
        return;
    w->x280 = 0;
    w->x278 = 0;
    w->x27C = 0;
    w->x288 = 0;
    w->x28C = 0;
    w->x2DC = 0;
    w->x2E0 = 0;
    switch (w->kind) {
    case 0:
        w->timer = iosGetRandom() * 5.0f;
        break;
    case 1:
    case 5:
        break;
    case 2:
        w->timer = iosGetRandom() * 10.0f;
        w->x31C = 0;
        break;
    case 3:
        w->timer = iosGetRandom() * 2.0f;
        break;
    case 4:
        w->timer = iosGetRandom() * 2.0f + 2.0f;
        break;
    case 6:
        r = iosGetRandom();
        if (r < 0.3f)
            w->x320 = 0;
        else if (r < 0.6f)
            w->x320 = 1;
        else
            w->x320 = 2;
        break;
    default:
        w->timer = 0.0f;
        break;
    }
}
