extern int SeList_decide;
extern int SeList_cancel;
extern int SeList_cursor;
extern void sePlaySystemSound(int id);

typedef struct {
    int pad0;
    unsigned int lo : 9;
    unsigned int sel : 2;
    int x : 10;
    int y : 10;
    unsigned int hi : 1;
    int pad8;
} MenuSub;

typedef void (*MenuCb)(void *o, int a, int flags, int x, int y);

typedef struct {
    char pad0[0x34];
    MenuSub sub;
    MenuCb cb;
} MenuEntry;

typedef struct {
    char pad0[0x10];
    int flags;
} MenuInfo;

typedef struct {
    MenuInfo *info;
    int pad4;
    int pad8;
    int cur;
    int pad10;
    int pad14;
    int attr;
} MenuList;

typedef struct {
    int pad0;
    MenuEntry *entries;
    int pad8;
    int idx;
    int flags;
    int pad14[3];
    int arg;
} MenuCtx;

extern MenuList *func_00093E40(MenuEntry *e);

#ifdef NONMATCHING
/* 151 diffs: branch layout of the cursor-step paths and register allocation */
static void func_000943F8(char *o)
{
    MenuCtx *c = *(unsigned char *)(o + 8) == 0x21 ? (MenuCtx *)(o + 0x90) : 0;
    MenuEntry *e;
    MenuSub *sub;
    MenuList *l;
    MenuInfo *info;
    int flags;
    int old;
    int n;

    if (c->idx == -1)
        return;
    e = &c->entries[c->idx];
    sub = &e->sub;
    l = func_00093E40(e);
    if (l == 0)
        return;
    flags = c->flags;
    info = l->info;
    if (flags & 0x801) {
        sub->sel = 0;
        if (l->attr & 0xC0000000)
            sePlaySystemSound(SeList_decide);
        if (info->flags & 0x100) {
            if (e->cb)
                e->cb(o, c->arg, c->flags, sub->x, l->cur);
        } else {
            if (e->cb)
                e->cb(o, c->arg, c->flags, sub->x, sub->y);
        }
    } else if (flags & 2) {
        sub->sel = 0;
        if (l->attr & 0xC0000000)
            sePlaySystemSound(SeList_cancel);
        if (info->flags & 0x100) {
            if (e->cb)
                e->cb(o, c->arg, c->flags, sub->x, l->cur);
        } else {
            if (e->cb)
                e->cb(o, c->arg, c->flags, sub->x, sub->y);
        }
    } else if (flags & 0x30) {
        if (info->flags & 0x100) {
            if (flags & 0x10) {
                old = l->cur;
                n = old - 1;
                if (n < 0)
                    n = 0;
                l->cur = n;
                if (old == n)
                    return;
            } else if (flags & 0x20) {
                old = l->cur;
                l->cur = old + 1;
                if (l->cur > 0x10)
                    l->cur = 0x10;
                if (old == l->cur)
                    return;
            } else {
                return;
            }
            sePlaySystemSound(SeList_cursor);
            if (e->cb)
                e->cb(o, c->arg, c->flags, sub->x, l->cur);
        } else {
            if (flags & 0x10) {
                old = sub->y;
                if (--sub->y < 0)
                    sub->y = ((l->attr << 22) >> 22) - 1;
            } else if (flags & 0x20) {
                old = sub->y;
                if (++sub->y > ((l->attr << 22) >> 22) - 1)
                    sub->y = 0;
            } else {
                return;
            }
            if (old == sub->y)
                return;
            sePlaySystemSound(SeList_cursor);
            if (e->cb)
                e->cb(o, c->arg, c->flags, sub->x, sub->y);
        }
    } else if (flags & 0x780) {
        if (e->cb)
            e->cb(o, c->arg, c->flags, sub->x, sub->y);
    }
}
#endif
