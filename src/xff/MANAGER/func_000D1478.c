/* Parked: 20 diffs, same size (956 words).
 * Remaining: register allocation in two places.
 * - Int dialog (0xB48-0xB5C): with the name pinned to a0, the Original stores
 *   d->val before d->name, then reloads SC into v1; here v1/v0 are swapped
 *   and d->val is stored after the SC reload.
 * - Float path changed() calls (0xD6C-0xDBC): v0/v1 swapped, and in the
 *   fp && f2C branch the Original loads SC into v1, keeping a2 live, where
 *   here SC is reloaded into a2.
 */
#ifdef NONMATCHING
typedef struct { int rows; int cur; int top; } Scroll;
typedef union { int i; char c[4]; } SU3;
typedef struct { SU3 rows, cur, top; } ScrollU;
typedef struct Win Win;
typedef struct Item {
    char *name;
    int (*get)(void);
    void (*changed)(Win *, struct Item *, Scroll *);
    void (*select)(Win *, struct Item *, Scroll *);
    int val;
    int type;
    float min;
    float max;
    float step;
    int readonly;
    int pad28;
    int f2C;
    int pad30[2];
} Item;
typedef struct List {
    int pad0[2];
    void (*update)(Win *, struct List *);
    int padC;
    float x;
    float y;
    int pad18[3];
    Item *items;
    int count;
} List;
struct Win {
    char pad0[0x94];
    union { int i; char c[4]; } idu;
    char pad98[0x198 - 0x98];
    float x;
    float y;
    char pad1A0[0x8];
    float px;
    float py;
    float w;
    int pad1B4;
    unsigned long long flags;
    int pad1C0;
    int flags2;
    char pad1C8[0x1E0 - 0x1C8];
    float wheel;
    char pad1E4[0x3E0 - 0x1E4];
    List *list;
    int pad3E4;
    Scroll *scroll;
};
typedef union { int i; char c[4]; } WU;
typedef struct { float x, y, w, h; WU scu; WU winu; } Ctx;
#define scv scu.i
#define winv winu.i
#define SC ((Scroll *)c.scv)
#define WN ((Win *)c.winv)

typedef struct { int held; int pad4[3]; int trig; } Pad;
typedef struct { float x, y; } Mouse;
typedef struct {
    char *name;
    float x;
    float y;
    int val;
    float *min;
    float *max;
    int type;
    Win *win;
    Item *items;
    int idx;
    int f28;
    int f2C;
} NumDlg;

extern Pad padManagerData;
extern char rootPtn[];
extern void windowGetCursorPosOnWindow(int, Ctx *);
extern void windowSetCursorPosOnWindow(int, Ctx *);
extern Mouse *windowGetMouseStatus(int, Win *);
extern void windowCloseRequest(Win *);
extern int getDrawScreenWidth(void);
extern int getDrawScreenHeight(void);
extern void *iosMallocAlign(void *, int, int);
extern void createNumDialog(NumDlg *, int);

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

void func_000D1478(int a0, Win *w)
{
    Ctx c;
    List *list;
    Item *items;
    Mouse *ms;
    int fp;
    int s6;
    int i;
    Item *it;

    c.winv = (int)w;
    c.scv = (int)WN->scroll;
    list = WN->list;
    items = list->items;
    ms = windowGetMouseStatus(a0, WN);
    fp = WN->flags2 & 0x20000;
    s6 = WN->flags2 & 0x20;
    if (!((int)(WN->flags >> 2) & 1))
        return;
    if ((int)(WN->flags >> 9) & 1) {
        WN->flags &= ~0x200;
        c.x = WN->x + WN->w * 0.5f;
        c.y = WN->y + (((ScrollU *)SC)->cur.i - ((ScrollU *)SC)->top.i) * 16;
        windowSetCursorPosOnWindow(WN->idu.i, &c);
        return;
    }
    for (i = 0; i < list->count; i++) {
        if (items[i].get != 0) {
            switch (items[i].type) {
            case 0:
            case 1:
                items[i].val = items[i].get();
                break;
            case 2:
                items[i].val = (int)items[i].get();
                break;
            case 3:
                items[i].val = items[i].get();
                break;
            }
        }
    }
    if (list->update != 0)
        list->update(WN, list);
    if (WN->flags2 & 0x40040)
        windowCloseRequest(WN);
    list->x = WN->px + (float)(getDrawScreenWidth() >> 1);
    list->y = WN->py + (float)(getDrawScreenHeight() >> 1);
    if ((int)(WN->flags >> 4) & 1) {
        int wheel;
        if ((int)(WN->flags >> 3) & 1)
            wheel = WN->wheel;
        else
            wheel = 0;
        windowGetCursorPosOnWindow(WN->idu.i, &c);
        SC->cur = (int)c.y / 16 + SC->top;
        if (SC->cur < SC->top)
            SC->cur = SC->top;
        if (SC->top + SC->rows - 1 < SC->cur)
            SC->cur = SC->top + SC->rows - 1;
        if (wheel != 0) {
            SC->top -= wheel;
            if (SC->top < 0)
                SC->top = 0;
            if (list->count - SC->rows < SC->top)
                SC->top = list->count - SC->rows;
        }
        __asm__ __volatile__("" ::: "memory");
        if (!(padManagerData.held & 8)) {
            if (padManagerData.trig & 0x1000) {
                if (c.y > 16.0f) {
                    c.y -= 16.0f;
                    windowSetCursorPosOnWindow(WN->idu.i, &c);
                } else {
                    if (--SC->cur < 0)
                        SC->cur = list->count - 1;
                    setCursor(&c, &c);
                }
            } else if (padManagerData.trig & 0x4000) {
                if (c.y < SC->rows * 16 - 16) {
                    c.y += 16.0f;
                    windowSetCursorPosOnWindow(WN->idu.i, &c);
                } else {
                    if (++SC->cur >= list->count)
                        SC->cur = 0;
                    setCursor(&c, &c);
                }
            }
        } else {
            if (padManagerData.trig & 0x1000) {
                if (SC->cur == 0) {
                    SC->cur = list->count - 1;
                    SC->top = list->count - SC->rows;
                } else {
                    SC->cur -= SC->rows;
                    SC->top -= SC->rows;
                    if (SC->cur < 0)
                        SC->cur = 0;
                    if (SC->top < 0)
                        SC->top = 0;
                }
                setCursor(&c, &c);
            } else if (padManagerData.trig & 0x4000) {
                if (SC->cur == list->count - 1) {
                    SC->cur = 0;
                    SC->top = 0;
                } else {
                    SC->cur += SC->rows;
                    SC->top += SC->rows;
                    if (SC->cur >= list->count)
                        SC->cur = list->count - 1;
                    if (SC->top >= list->count - SC->rows)
                        SC->top = list->count - SC->rows;
                }
                setCursor(&c, &c);
            }
        }
    } else {
        if (padManagerData.trig & 0x1000) {
            if (--SC->cur < 0)
                SC->cur = list->count - 1;
            clampScroll(&c);
        } else if (padManagerData.trig & 0x4000) {
            if (++SC->cur >= list->count)
                SC->cur = 0;
            clampScroll(&c);
        }
    }
    if (items[SC->cur].val == 0)
        return;
    if (items[SC->cur].select != 0)
        items[SC->cur].select(WN, &items[SC->cur], SC);
    if (items[SC->cur].readonly != 0)
        return;
    if ((unsigned)items[SC->cur].type < 2) {
        int *p = (int *)items[SC->cur].val;
        int step = 1;
        if (*p < items[SC->cur].min)
            *p = items[SC->cur].min;
        if (items[SC->cur].max < *p)
            *p = items[SC->cur].max;
        if (padManagerData.held & 8)
            step = 10;
        if (padManagerData.held & 2)
            step *= 100;
        if (padManagerData.trig & 0x8000) {
            *p -= step;
            if (*p < items[SC->cur].min)
                *p = items[SC->cur].max;
            if (items[SC->cur].changed != 0)
                items[SC->cur].changed(WN, items, SC);
        } else if ((padManagerData.trig & 0x2000) || (s6 && items[SC->cur].f2C)) {
            *p += step;
            if (items[SC->cur].max < *p)
                *p = items[SC->cur].min;
            if (items[SC->cur].changed != 0)
                items[SC->cur].changed(WN, items, SC);
        } else if (fp && items[SC->cur].f2C) {
            if (items[SC->cur].changed != 0)
                items[SC->cur].changed(WN, items, SC);
        } else if (fp || s6) {
            NumDlg *d = iosMallocAlign(rootPtn, 0x30, 0x10);
            float *min;
            {register char *nm asm("$4") = items[SC->cur].name; d->name = nm;}
            min = &items[SC->cur].min;
            d->val = (int)p;
            d->min = min;
            d->max = &items[SC->cur].max;
            d->x = ms->x + (float)(getDrawScreenWidth() >> 1);
            d->y = ms->y + (float)(getDrawScreenHeight() >> 1);
            d->type = 0;
            d->win = WN;
            d->items = items;
            d->idx = SC->cur;
            d->f28 = 0;
            d->f2C = 0;
            createNumDialog(d, WN->idu.i);
        }
    }
    if (items[SC->cur].type == 2) {
        float *p = (float *)items[SC->cur].val;
        float step = items[SC->cur].step;
        if (*p < items[SC->cur].min)
            *p = items[SC->cur].min;
        if (items[SC->cur].max < *p)
            *p = items[SC->cur].max;
        if (padManagerData.held & 8)
            step *= 10.0f;
        if (padManagerData.held & 2)
            step *= 100.0f;
        if (padManagerData.trig & 0x8000) {
            *p -= step;
            if (*p < items[SC->cur].min)
                *p = items[SC->cur].max;
            if (items[SC->cur].changed != 0)
                items[SC->cur].changed(WN, items, SC);
        } else if ((padManagerData.trig & 0x2000) || (s6 && items[SC->cur].f2C)) {
            *p += step;
            if (items[SC->cur].max < *p)
                *p = items[SC->cur].min;
            if (items[SC->cur].changed != 0)
                items[SC->cur].changed(WN, items, SC);
        } else if (fp && items[SC->cur].f2C) {
            if (items[SC->cur].changed != 0)
                items[SC->cur].changed(WN, items, SC);
        } else if (fp || s6) {
            NumDlg *d = iosMallocAlign(rootPtn, 0x30, 0x10);
            d->name = items[SC->cur].name;
            d->x = ms->x + (float)(getDrawScreenWidth() >> 1);
            d->y = ms->y + (float)(getDrawScreenHeight() >> 1);
            d->val = (int)p;
            d->min = &items[SC->cur].min;
            d->max = &items[SC->cur].max;
            d->type = 2;
            d->win = WN;
            d->items = items;
            d->idx = SC->cur;
            d->f28 = 0;
            d->f2C = 0;
            createNumDialog(d, WN->idu.i);
        }
    }
}
#else
static void func_000D1478();
#endif
