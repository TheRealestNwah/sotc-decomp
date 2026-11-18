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
    float x100;
    float x104;
} WindEmitter;

extern WindEmitter *B_00149AB0[];
extern void *malloc_from_fast_get_partition(int, const char *, int);
extern void CopyScriptAnimationWindGeometryPointer(void *, void *);
extern void CopyScriptAnimationWindParam(void *, void *);
extern char InitialScriptAnimeWindGeometryPointer[];
extern char InitialScriptAnimeWindParam[];
extern s128 ZeroPoint;
extern s128 ZUnitVector;
extern void func_000CBEC0(WindEmitter *, int);

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

int boot_wind_emitter(void *volume, void *geometry, int a2, int a3)
{
    WindEmitter *e;
    /* The callee func_000CBEC0 reads $f12 as a float argument; the Original keeps xA4 there. */
    register float t asm("$f12");
    int slot;

    if (volume != 0) {
        slot = findFreeEmitter();
        if (slot >= 0) {
            e = malloc_from_fast_get_partition(0x110, "\xB5\xE5\xC9\xF7", 1);
            e->type = 0;
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
            t = e->xA4;
            e->xD0 = t;
            e->up.q = ZUnitVector.q;
            e->xF0 = 1;
            e->xF4 = a2;
            e->xF8 = a3;
            e->x100 = t;
            e->x104 = t;
            func_000CBEC0(e, 1);
            B_00149AB0[slot] = e;
            return slot;
        }
    }
    return -1;
}
