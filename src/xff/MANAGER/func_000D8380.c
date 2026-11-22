/* Clamps the mouse cursor into the object's window rectangle and moves the cursor if it changed. */
typedef struct {
    float x;
    float y;
    float w;
    float h;
} CursorRect;

typedef struct {
    float x;
    float y;
} CursorPos;

typedef struct {
    char pad0[4];
    CursorPos *volatile pos;
    char pad8[8];
    CursorPos cur;
} CursorWork;

typedef struct {
    char pad0[0x10];
    float x;
    char pad14[4];
    float w;
    float hbase;
    char pad20[0x34 - 0x20];
    float y;
    char pad38[4];
    float h;
} CursorWin;

typedef struct {
    char pad0[0x1B8];
    unsigned long flags;
    char pad1C0[0x254 - 0x1C0];
    CursorWin win;
} CursorObj;

extern CursorWork D_00139B80;
extern void mouseSetCursorPosition(float, float);

static inline CursorRect getRect(CursorWin *win)
{
    CursorRect r;

    r.x = win->x;
    r.y = win->y;
    r.w = win->w;
    r.h = win->h + win->hbase;
    return r;
}

static inline int clampCursor(CursorRect r)
{
    int changed = 0;

    if (D_00139B80.cur.x <= r.x) {
        D_00139B80.cur.x = r.x;
        changed = 1;
    } else if (r.x + r.w - 1.0f < D_00139B80.cur.x) {
        D_00139B80.cur.x = r.x + r.w - 1.0f;
        changed = 1;
    }
    if (D_00139B80.cur.y <= r.y) {
        D_00139B80.cur.y = r.y;
        changed = 1;
    } else if (r.y + r.h - 1.0f < D_00139B80.cur.y) {
        D_00139B80.cur.y = r.y + r.h - 1.0f;
        changed = 1;
    }
    return changed;
}

static void func_000D8380(CursorObj *o)
{
    int changed = 0;
    CursorWin *win = &o->win;

    if (!((int)(o->flags >> 9) & 1)) {
        changed = clampCursor(getRect(win));
    }
    if (changed) {
        CursorPos *c = &D_00139B80.cur;

        mouseSetCursorPosition(c->x, c->y);
        *(volatile float *)&D_00139B80.pos->x = c->x;
        D_00139B80.pos->y = c->y;
    }
}
