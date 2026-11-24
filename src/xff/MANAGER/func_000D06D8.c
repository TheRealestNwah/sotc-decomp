/* Parked: 7 diffs, same size (423 words) (was 9). An empty asm that reads
 * the two context stores and list and rewrites the flags keeps the ld at
 * 0x1B8 after them, as in the Original.
 * Remaining: prologue scheduling. The Original stores w (sw a1) before the
 * callee saves and loads list (lw s0) before storing w->scroll (sw a2).
 */
#ifdef NONMATCHING
typedef struct { int rows; int cur; int top; } Scroll;
typedef struct { char pad0[0x10]; int count; char pad14[0x10]; int f24; union { int i; char c[4]; } f28u; } List;
typedef struct {
    char pad0[0x94];
    union { int i; char c[4]; } idu;
    char pad98[0x198 - 0x98];
    float x;
    float y;
    char pad1A0[0x10];
    float w;
    int pad1B4;
    union { unsigned long long l; char c[8]; } flagsu;
    char pad1C0[0x1E0 - 0x1C0];
    float wheel;
    char pad1E4[0x3E0 - 0x1E4];
    List *list;
    int pad3E4;
    Scroll *scroll;
} Win;
typedef union { int i; char c[4]; } WU;
typedef struct { float x, y, w, h; WU scu; WU winu; } Ctx;
#define scv scu.i
#define winv winu.i

typedef struct { int held; int pad4[3]; int trig; } Pad;

extern Pad padManagerData;
extern void windowGetCursorPosOnWindow(int, Ctx *);
extern void windowSetCursorPosOnWindow(int, Ctx *);

static inline void clampScroll(Ctx *c)
{
    while (((Scroll *)c->scv)->cur < ((Scroll *)c->scv)->top)
        ((Scroll *)c->scv)->top--;
    while (((Scroll *)c->scv)->top + ((Scroll *)c->scv)->rows - 1 < ((Scroll *)c->scv)->cur)
        ((Scroll *)c->scv)->top++;
}

static inline void setCursor(Ctx *c, Ctx *d)
{
    clampScroll(d);
    c->y = (((Scroll *)c->scv)->cur - ((Scroll *)c->scv)->top) * 16 + 8;
    windowSetCursorPosOnWindow(((Win *)c->winv)->idu.i, c);
}

static void func_000D06D8(int unused, Win *w)
{
    Ctx c;
    List *list;
    int wheel;

    c.winv = (int)w;
    c.scv = (int)((Win *)c.winv)->scroll;
    list = ((Win *)c.winv)->list;
    __asm__("" : "+m"(w->flagsu.l) : "m"(c.winu), "m"(c.scu), "r"(list));
    list->f24 = (int)(((Win *)c.winv)->flagsu.l >> 2) & 1;
    if (!((int)(((Win *)c.winv)->flagsu.l >> 2) & 1))
        return;
    if ((int)(((Win *)c.winv)->flagsu.l >> 9) & 1) {
        ((Win *)c.winv)->flagsu.l &= ~0x200;
        c.x = ((Win *)c.winv)->x + ((Win *)c.winv)->w * 0.5f;
        c.y = ((Win *)c.winv)->y + list->f28u.i * 16;
        windowSetCursorPosOnWindow(((Win *)c.winv)->idu.i, &c);
        return;
    }
    if ((int)(((Win *)c.winv)->flagsu.l >> 3) & 1) {
        wheel = ((Win *)c.winv)->wheel;
        windowGetCursorPosOnWindow(((Win *)c.winv)->idu.i, &c);
        ((Scroll *)c.scv)->cur = (int)c.y / 16 + ((Scroll *)c.scv)->top;
        if (((Scroll *)c.scv)->cur < ((Scroll *)c.scv)->top)
            ((Scroll *)c.scv)->cur = ((Scroll *)c.scv)->top;
        if (((Scroll *)c.scv)->top + ((Scroll *)c.scv)->rows - 1 < ((Scroll *)c.scv)->cur)
            ((Scroll *)c.scv)->cur = ((Scroll *)c.scv)->top + ((Scroll *)c.scv)->rows - 1;
        if (wheel != 0) {
            ((Scroll *)c.scv)->top -= wheel;
            if (((Scroll *)c.scv)->top < 0)
                ((Scroll *)c.scv)->top = 0;
            if (list->count - ((Scroll *)c.scv)->rows < ((Scroll *)c.scv)->top)
                ((Scroll *)c.scv)->top = list->count - ((Scroll *)c.scv)->rows;
        }
    }
    if (!(padManagerData.held & 8) && (padManagerData.trig & 0x1000)) {
        if (c.y > 16.0f) {
            c.y -= 16.0f;
            windowSetCursorPosOnWindow(((Win *)c.winv)->idu.i, &c);
        } else {
            if (--((Scroll *)c.scv)->cur < 0)
                ((Scroll *)c.scv)->cur = list->count - 1;
            setCursor(&c, &c);
        }
    } else if (!(padManagerData.held & 8) && (padManagerData.trig & 0x4000)) {
        if (c.y < ((Scroll *)c.scv)->rows * 16 - 16) {
            c.y += 16.0f;
            windowSetCursorPosOnWindow(((Win *)c.winv)->idu.i, &c);
        } else {
            if (++((Scroll *)c.scv)->cur >= list->count)
                ((Scroll *)c.scv)->cur = 0;
            setCursor(&c, &c);
        }
    } else if ((padManagerData.trig & 0x8000) ||
               ((padManagerData.held & 8) && (padManagerData.trig & 0x1000))) {
        if (((Scroll *)c.scv)->cur == 0) {
            ((Scroll *)c.scv)->cur = list->count - 1;
            ((Scroll *)c.scv)->top = list->count - ((Scroll *)c.scv)->rows;
        } else {
            ((Scroll *)c.scv)->cur -= ((Scroll *)c.scv)->rows;
            ((Scroll *)c.scv)->top -= ((Scroll *)c.scv)->rows;
            if (((Scroll *)c.scv)->cur < 0)
                ((Scroll *)c.scv)->cur = 0;
            if (((Scroll *)c.scv)->top < 0)
                ((Scroll *)c.scv)->top = 0;
        }
        setCursor(&c, &c);
    } else if ((padManagerData.trig & 0x2000) ||
               ((padManagerData.held & 8) && (padManagerData.trig & 0x4000))) {
        if (((Scroll *)c.scv)->cur == list->count - 1) {
            ((Scroll *)c.scv)->cur = 0;
            ((Scroll *)c.scv)->top = 0;
        } else {
            ((Scroll *)c.scv)->cur += ((Scroll *)c.scv)->rows;
            ((Scroll *)c.scv)->top += ((Scroll *)c.scv)->rows;
            if (((Scroll *)c.scv)->cur >= list->count)
                ((Scroll *)c.scv)->cur = list->count - 1;
            if (((Scroll *)c.scv)->top >= list->count - ((Scroll *)c.scv)->rows)
                ((Scroll *)c.scv)->top = list->count - ((Scroll *)c.scv)->rows;
        }
        setCursor(&c, &c);
    }
    ((Win *)c.winv)->y = -((Scroll *)c.scv)->top * 16;
}
#else
static void func_000D06D8();
#endif
