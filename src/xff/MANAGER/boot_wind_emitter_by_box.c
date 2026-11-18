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
    char mat[0x40];
    s128 x140;
    s128 x150;
    float x160;
} WindEmitter;

extern WindEmitter *B_00149AB0[];
extern void *malloc_from_fast_get_partition(int, const char *, int);
extern void CopyScriptAnimationWindGeometryPointer(void *, void *);
extern void CopyScriptAnimationWindParam(void *, void *);
extern char InitialScriptAnimeWindGeometryPointer[];
extern char InitialScriptAnimeWindParam[];
extern s128 ZeroPoint;
extern s128 ZUnitVector;
extern void func_000CAA98(WindEmitter *, int, float);
extern void iosCopyMatrix(void *, void *);
extern char UnitMatrix[];
extern s128 ZeroVector;

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

int boot_wind_emitter_by_box(void *volume, void *geometry, int a2, int a3)
{
    WindEmitter *e;
    int slot;

    if (volume != 0) {
        slot = findFreeEmitter();
        if (slot >= 0) {
            e = malloc_from_fast_get_partition(0x170, "\xC8\xA2\xC9\xF7", 1);
            e->type = 1;
            e->volume = volume;
            if (geometry != 0) {
                e->x8 = 1;
                CopyScriptAnimationWindGeometryPointer(e->geometry, geometry);
            } else {
                e->x8 = 0;
                CopyScriptAnimationWindGeometryPointer(e->geometry, InitialScriptAnimeWindGeometryPointer);
            }
            CopyScriptAnimationWindParam(e->param, InitialScriptAnimeWindParam);
            e->active = 1;
            e->xA4 = 0.0f;
            e->pos.q = ZeroPoint.q;
            e->dir.q = ZUnitVector.q;
            e->xD0 = 0.0f;
            e->up.q = ZUnitVector.q;
            e->xF0 = 1;
            e->xF4 = a2;
            e->xF8 = a3;
            iosCopyMatrix(e->mat, UnitMatrix);
            e->x140.q = ZeroVector.q;
            e->x150.q = ZeroVector.q;
            e->x160 = 0.0f;
            func_000CAA98(e, 1, e->x160);
            B_00149AB0[slot] = e;
            return slot;
        }
    }
    return -1;
}
