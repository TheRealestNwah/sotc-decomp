/* Sets the window resize cursor state from which border region of the current window the mouse is over. */
typedef struct {
    float x;
    float y;
    float w;
    float h;
} HitRect;

typedef struct {
    float x;
    float y;
} CursorPos;

typedef struct {
    void *tex;
    char pad4[0xC];
    CursorPos cur;
    char pad18[8];
    int state;
} CursorWork;

typedef struct {
    char pad0[0x80];
    HitRect r[8];
} CursorWin;

typedef struct {
    char pad0[0x1B8];
    unsigned long flags;
    int busy;
    char pad1C4[0x254 - 0x1C4];
    CursorWin win;
} CursorObj;

typedef struct {
    int pad0;
    CursorObj *obj;
} WindowHandle;

extern CursorWork D_00139B80;
extern WindowHandle *windowGetCurrentWindowHandle(void);
extern void texTransRequest(void *, int, int);

static inline int hitRect(HitRect *r, CursorPos *p)
{
    int in = 0;

    if (p->x >= r->x && p->y >= r->y && r->x + r->w > p->x && r->y + r->h > p->y) {
        in = 1;
    }
    return in;
}

static void func_000D84C8(int keep)
{
    WindowHandle *h = windowGetCurrentWindowHandle();
    CursorObj *o = 0;
    CursorWin *w;

    if (h) {
        o = h->obj;
    }
    w = 0;
    if (o) {
        w = &o->win;
    }
    D_00139B80.state = 0;
    if (w && ((int)(o->flags >> 6) & 1) && !o->busy) {
        if (hitRect(&w->r[0], &D_00139B80.cur)) {
            D_00139B80.state = 3;
        } else if (hitRect(&w->r[2], &D_00139B80.cur)) {
            D_00139B80.state = 4;
        } else if (hitRect(&w->r[5], &D_00139B80.cur)) {
            D_00139B80.state = 4;
        } else if (hitRect(&w->r[7], &D_00139B80.cur)) {
            D_00139B80.state = 3;
        } else if (hitRect(&w->r[1], &D_00139B80.cur)) {
            D_00139B80.state = 1;
        } else if (hitRect(&w->r[3], &D_00139B80.cur)) {
            D_00139B80.state = 2;
        } else if (hitRect(&w->r[4], &D_00139B80.cur)) {
            D_00139B80.state = 2;
        } else if (hitRect(&w->r[6], &D_00139B80.cur)) {
            D_00139B80.state = 1;
        }
    }
    if (!keep) {
        D_00139B80.state = 6;
    }
    if (D_00139B80.tex) {
        texTransRequest(D_00139B80.tex, 3, 0);
    }
}
