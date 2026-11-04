typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;
typedef struct { unsigned long pad : 5; unsigned int active : 1; unsigned long rest : 58; } WinFlags;
typedef struct Window { int a; char *obj; char pad[0x14]; struct Window *next; } Window;
extern Window *D_00139BA8;
extern Vec4 D_00139B90;

static inline int isInsideRect(float *rect, float *pos)
{
    int inside = 0;
    if (rect[0] <= pos[0] && rect[1] <= pos[1] && pos[0] < rect[0] + rect[2] && pos[1] < rect[1] + rect[3])
        inside = 1;
    return inside;
}

static Window *func_000D59E8(void)
{
    Window *w;
    for (w = D_00139BA8; w != 0; w = w->next) {
        if (((WinFlags *)(w->obj + 0x1B8))->active) {
            if (isInsideRect((float *)(w->obj + 0x254), D_00139B90.f))
                return w;
        }
    }
    return 0;
}
