/* Creates a window object, links it under its parent and group, sets up its two draw contexts and puts it on the window list. */
typedef struct {
    char pad[0x190];
} DC;
typedef struct {
    char pad0[0x1C];
    DC *dc;
} WinRes;
struct Win;
typedef union { unsigned long l; struct Win *p; int i; } Flags;
typedef struct Win {
    char pad0[0x70];
    int group;
    char pad74[0x94 - 0x74];
    struct WinRec *rec;
    char pad98[0x1B8 - 0x98];
    Flags flags;
    unsigned int flags2;
    char pad1C4[4];
    int x1C8;
    char pad1CC[0x264 - 0x1CC];
    float x;
    float y;
    float w;
    float h;
} Win;
typedef struct WinRec {
    int *obj;
    Win *win;
    WinRes *res;
    float time;
    int x10;
    struct WinRec *parent;
    struct WinRec *next;
    struct WinRec *prev;
} WinRec;
typedef struct {
    char pad0[8];
    float x;
    float y;
    char pad10[0x50 - 0x10];
    int top;
} WinDesc;
typedef struct {
    int a;
    int mouse;
    int x8;
    int xC;
    char pad10[0x14];
    WinRec *head;
    WinRec *tail;
} WinState;

extern WinState D_00139B80;
extern int B_0014E888[];
extern char rootPtn[];
extern char T_000D9560[];
extern int getDrawScreenWidth(void);
extern int getDrawScreenHeight(void);
extern int getDrawBufferAddressFBP(void);
extern int getZBufferAddressFBP(void);
extern int *CreateWindowObj(void *, WinDesc *, void *, int);
extern void isysAddGroupWithLinkParam(void *, void *, int, int);
extern Win *GetWindowClass(int *);
extern void *iosMallocAlign(int, int, int);
extern long iosGetTCountExtension(void);
extern float iosGetSecondFromTCount(long);
extern WinRes *iosCreateDC(int, int);
extern void iosSetDCParam(DC *, int, int, int, int);
extern void iosSetDCClearParam(DC *, int, int, int, int, int);
extern void iosSetDCViewPortCenter(DC *, int, int, int, int, int, int);
extern void func_000D7AF0(Win *);
extern void mouseClearStatus(int);

static inline void listAppend(WinRec *r)
{
    WinRec *t;

    r->next = 0;
    t = D_00139B80.tail;
    r->prev = t;
    if (t != 0)
        t->next = r;
    D_00139B80.tail = r;
    if (D_00139B80.head == 0)
        D_00139B80.head = r;
}

static inline void listRemove(WinRec *r)
{
    if (r->prev != 0)
        r->prev->next = r->next;
    if (r->next != 0)
        r->next->prev = r->prev;
    if (r == D_00139B80.head)
        D_00139B80.head = r->next;
    if (r == D_00139B80.tail)
        D_00139B80.tail = r->prev;
    r->prev = 0;
    r->next = 0;
}

WinRec *windowCreate(WinDesc *desc, WinRec *parent, int group)
{
    int sw;
    int sh;
    int *obj;
    Win *win;
    WinRec *rec;
    int i;

    sw = getDrawScreenWidth();
    sh = getDrawScreenHeight();
    desc->x -= (float)(sw >> 1);
    desc->y -= (float)(sh >> 1);
    obj = CreateWindowObj(rootPtn, desc, T_000D9560, 0);
    if (obj == 0)
        return 0;
    isysAddGroupWithLinkParam(obj, &B_0014E888[group], 0, 0);
    win = GetWindowClass(obj);
    rec = iosMallocAlign(*obj, 0x20, 0x10);
    rec->time = iosGetSecondFromTCount(iosGetTCountExtension());
    rec->x10 = 0;
    if (rec == 0)
        return 0;
    win->rec = rec;
    rec->obj = obj;
    rec->win = win;
    rec->parent = parent;
    if (parent != 0) {
        isysAddGroupWithLinkParam(obj, &parent->win->group, 0, 0);
        parent->win->flags.l |= 0x100;
        parent->win->flags.l &= ~4;
        parent->win->flags.l &= ~8;
        parent->win->flags.l &= ~0x10;
    }
    rec->res = iosCreateDC(*rec->obj, 2);
    for (i = 0; i < 2; i++) {
        Win *w2;
        DC *dc;
        int fbp, zbp;
        int w, h;
        int x, y, ww, wh;
        int cx, cy;

        fbp = getDrawBufferAddressFBP();
        zbp = getZBufferAddressFBP();
        iosSetDCParam((DC *)((int)rec->res->dc + i * 0x190), fbp, zbp, sw, sh);
        iosSetDCClearParam((DC *)((int)rec->res->dc + i * 0x190), 0, 0, 0, 0, 0x80);
        dc = (DC *)(i * 0x190 + (int)rec->res->dc);
        w2 = rec->win;
        w = getDrawScreenWidth();
        h = getDrawScreenHeight();
        x = (int)(w2->x + (float)(w >> 1));
        y = (int)(w2->y + (float)(h >> 1));
        ww = (int)w2->w;
        wh = (int)w2->h;
        cx = -x - ww / 2;
        cy = -y - wh / 2;
        if (x < 0) {
            ww += x;
            x = 0;
        } else if (w - 1 < x) {
            x = w - 1;
        }
        if (y < 0) {
            wh += y;
            y = 0;
        } else if (h - 1 < y) {
            y = h - 1;
        }
        if (w - 1 < x + ww)
            ww = w - x - 1;
        if (h - 1 < y + wh)
            wh = h - y - 1;
        iosSetDCViewPortCenter(dc, x, y, ww, (w2->flags2 & 1) ? 0 : wh, cx, cy);
    }
    func_000D7AF0(win);
    if (desc->top) {
        listAppend(rec);
    } else {
        WinRec *t = D_00139B80.tail;
        listAppend(rec);
        if (t != 0) {
            Win *tw = t->win;
            listRemove(t);
            listAppend(t);
            tw->x1C8 = 0;
        }
    }
    win->flags.l |= 1;
    win->flags.l |= 2;
    mouseClearStatus(D_00139B80.mouse);
    D_00139B80.xC = 0;
    D_00139B80.x8 = 0;
    return rec;
}
