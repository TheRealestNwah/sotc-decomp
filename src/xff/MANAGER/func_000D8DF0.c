typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;
typedef struct { unsigned int b0 : 1; unsigned int b1 : 1; unsigned int b2 : 1; unsigned int b3 : 1; unsigned long rest : 60; } WinFlags;
typedef struct Win {
    char pad0[0x198];
    float ox;
    float oy;
    char pad1A0[0x18];
    WinFlags flags;
    char pad1C0[0x94];
    float rect[0x40];
} Win;
typedef struct {
    int a;
    int *mouse;
    int x8;
    int xC;
} WinState;
extern WinState D_00139B80;
extern Vec4 D_00139B90;

static inline int isInsideRect(float *rect, float *pos)
{
    int inside = 0;
    if (pos[0] >= rect[0] && pos[1] >= rect[1] && pos[0] < rect[0] + rect[2] && pos[1] < rect[1] + rect[3])
        inside = 1;
    return inside;
}

static inline int isInsideRectWin(Win *w, float *rect, float *pos)
{
    int inside;
    float x, y;
    if (w == 0)
        return isInsideRect(rect, pos);
    inside = 0;
    x = rect[0] + w->ox;
    if (x <= pos[0]) {
        y = rect[1] + w->oy;
        if (y <= pos[1] && pos[0] < x + rect[2] && pos[1] < y + rect[3])
            inside = 1;
    }
    return inside;
}

static int func_000D8DF0(Win *w)
{
    int f;
    float *p;
    int on;

    on = w->flags.b3;
    p = w ? w->rect : 0;
    f = on != 0;
    if (p) {
        if (isInsideRectWin(w, p + 4, D_00139B90.f))
            f |= 4;
        if (isInsideRect(p + 8, D_00139B90.f) || isInsideRect(p + 12, D_00139B90.f) || isInsideRect(p + 16, D_00139B90.f))
            f |= 8;
        if (isInsideRect(p + 32, D_00139B90.f) || isInsideRect(p + 40, D_00139B90.f) ||
            isInsideRect(p + 52, D_00139B90.f) || isInsideRect(p + 60, D_00139B90.f) ||
            isInsideRect(p + 36, D_00139B90.f) || isInsideRect(p + 44, D_00139B90.f) ||
            isInsideRect(p + 48, D_00139B90.f) || isInsideRect(p + 56, D_00139B90.f))
            f |= 0x10;
    }
    if (w->flags.b3) {
        if (D_00139B80.mouse[8])
            f |= 0x20;
        if (D_00139B80.mouse[9])
            f |= 0x40;
        if (D_00139B80.mouse[10])
            f |= 0x80;
        if (D_00139B80.mouse[11])
            f |= 0x100;
        if (D_00139B80.mouse[12])
            f |= 0x200;
        if (D_00139B80.mouse[13])
            f |= 0x400;
        if (D_00139B80.mouse[14])
            f |= 0x800;
        if (D_00139B80.mouse[15])
            f |= 0x1000;
        if (D_00139B80.mouse[16])
            f |= 0x2000;
        if (D_00139B80.mouse[5])
            f |= 0x4000;
        if (D_00139B80.mouse[6])
            f |= 0x8000;
        if (D_00139B80.mouse[7])
            f |= 0x10000;
    }
    if (D_00139B80.x8)
        f |= 0x20000;
    if (D_00139B80.xC)
        f |= 0x40000;
    return f;
}

