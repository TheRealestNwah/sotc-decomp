#ifdef NONMATCHING /* 2 diffs: the xA4 -> xD0 float copy uses $f12 in the Original, $f0 here. Tried a float local, a reused float parameter, an inline setter and other statement placements. */
typedef union { int q __attribute__((mode(TI))); float v[4]; } s128;

typedef struct {
    int type;
    void *volume;
    int x8;
    int pad0C;
    char geometry[0x50];
    char param[0x40];
    int active;
    float xA4;
    int padA8[2];
    s128 pos;
    s128 dir;
    float xD0;
    int padD4[3];
    s128 up;
    int xF0;
    int xF4;
    int xF8;
    int padFC;
    int x100;
} WindEmitter;

extern WindEmitter *B_00149AB0[];
extern void *malloc_from_fast_get_partition(int, const char *, int);
extern void CopyScriptAnimationWindGeometryPointer(void *, void *);
extern void CopyScriptAnimationWindParam(void *, void *);
extern char InitialScriptAnimeWindGeometryPointer[];
extern char InitialScriptAnimeWindParam[];
extern s128 ZeroPoint;
extern s128 ZUnitVector;
extern void func_000CC018(WindEmitter *, int);

static inline int findFreeEmitter(void)
{
    int i;

    for (i = 0; i < 80; i++) {
        if (B_00149AB0[i] == 0) {
            return i;
        }
    }
    return -1;
}

int boot_wind_emitter_by_judge_volume(void *volume, int a1, int a2, int a3)
{
    WindEmitter *e;
    int slot;

    if (volume != 0) {
        slot = findFreeEmitter();
        if (slot >= 0) {
            e = malloc_from_fast_get_partition(0x110, "\xA5\xDC\xA5\xEA\xA5\xE5\xA1\xBC\xA5\xE0\xC9\xF7", 1);
            e->type = 2;
            e->volume = volume;
            e->x8 = 0;
            CopyScriptAnimationWindGeometryPointer(e->geometry, InitialScriptAnimeWindGeometryPointer);
            CopyScriptAnimationWindParam(e->param, InitialScriptAnimeWindParam);
            e->active = 1;
            e->xA4 = 0.0f;
            e->pos.q = ZeroPoint.q;
            e->dir.q = ZUnitVector.q;
            e->xD0 = e->xA4;
            e->up.q = ZUnitVector.q;
            e->xF0 = 1;
            e->xF4 = a2;
            e->xF8 = a3;
            e->x100 = a1;
            func_000CC018(e, 1);
            B_00149AB0[slot] = e;
            return slot;
        }
    }
    return -1;
}
#endif
