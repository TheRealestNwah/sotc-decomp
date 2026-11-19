/* func_00093F40 (menu cursor/decide handling) and its caller T_00094740 (pad-button
 * update for an 0x21 object's work block). They share one file because
 * T_00094740 only matches when func_00093F40 is visible: callee visibility
 * changes delay-slot filling in its mode dispatch. The work block is accessed
 * through a union, which gives it the alias set the Original's scheduling needs. */
typedef struct { int lo : 9; unsigned mode : 2; int f1 : 10; int f2 : 10; unsigned top : 1; } CfgBits;
typedef struct Obj2 { int pad0[4]; int flags; int f14; int f18; char pad1C[0x5C - 0x1C]; void (*fn)(void *); } Obj2;
typedef struct { Obj2 *o; int pad4[5]; int x18; } Ent;
typedef struct { int pad; CfgBits b; } Cfg;
typedef void (*Cb)(void *obj, int arg, int buttons, int idx);
typedef struct {
    int has;
    Ent *ents;
    unsigned kind : 4;
    unsigned cnt : 10;
    unsigned rest : 18;
    char padC[0x34 - 0xC];
    Cfg sub;
    Cb cb;
    char pad40[4];
} Item;
typedef struct { int pad0; Item *items; int pad8; int cur; int buttons; int x14; int x18; int pad1C; int f20; Cb cb24; } WorkS;
typedef union { WorkS s; } Work;
typedef struct { char pad0[8]; unsigned char type; } Obj;
typedef struct { int pad0[2]; int held; int pad0C; int trig; } PadData;
extern PadData padManagerData;
extern int D_00136E78;
extern int SeList_decide;
extern int SeList_cancel;
extern int SeList_cursor;
void sePlaySystemSound(int se);
void func_00093CD0(Work *w, float t);
void func_000943F8(Obj *o);
void func_000936A8(Work *w, int on);
void func_00093278(Work *w, float t);

static inline Work *getWork(Obj *o)
{
    if (o->type == 0x21) {
        return (Work *)((char *)o + 0x90);
    }
    return 0;
}

static inline int padHeld(PadData *pad, int *map, int n) { return pad->held & (1 << ((signed char *)*map)[n]); }
static inline int padTrig(PadData *pad, int *map, int n) { return pad->trig & (1 << ((signed char *)*map)[n]); }
static inline Item *curItem(Work *w) { return &w->s.items[w->s.cur]; }

static inline int hasSel(Item *it)
{
    int i;

    for (i = 0; i < it->cnt; i++) {
        Obj2 *o = it->ents[i].o;
        if ((o->flags & 0xC02) == 2 && o->f18 == -1 && o->f14 == it->sub.b.f1) {
            return 1;
        }
    }
    return 0;
}

static inline Ent *findSel(Item *it)
{
    int i;

    for (i = 0; i < it->cnt; i++) {
        if ((it->ents[i].o->flags & 2) && it->ents[i].o->f14 == it->sub.b.f1) {
            return &it->ents[i];
        }
    }
    return 0;
}

static void func_00093F40(Obj *obj)
{
    Work *w;
    Item *it;
    Cfg *c;
    Ent *sel;
    int i;

    w = getWork(obj);
    if (w->s.cur == -1) {
        return;
    }
    it = &w->s.items[w->s.cur];
    c = &it->sub;
    for (i = 0; i < it->cnt; i++) {
        if ((it->ents[i].o->flags & 2) && it->ents[i].o->f14 == it->sub.b.f1) {
            sel = &it->ents[i];
            goto found;
        }
    }
    sel = 0;
found:
    if (sel != 0) {
        if (w->s.buttons & 0x801) {
            Obj2 *o = sel->o;
            if (sel->x18 & 0xC0000000) {
                sePlaySystemSound(SeList_decide);
            }
            if (o->fn != 0) {
                o->fn(obj);
            }
            w->s.x18 = c->b.f1;
            w->s.x14 = w->s.cur;
            if (it->cb != 0) {
                it->cb(obj, w->s.f20, w->s.buttons, c->b.f1);
            }
            if (sel->x18 & 0x3FF) {
                c->b.mode = 1;
            }
        } else if (w->s.buttons & 2) {
            if (sel->x18 & 0xC0000000) {
                sePlaySystemSound(SeList_cancel);
            }
            if (it->cb != 0) {
                it->cb(obj, w->s.f20, w->s.buttons, c->b.f1);
            }
        } else if (w->s.buttons & 4) {
            int old2 = c->b.f1;
            do {
                if (--c->b.f1 < 0) {
                    c->b.f1 = c->b.lo - 1;
                }
                if (c->b.f1 == old2) {
                    break;
                }
            } while (!hasSel(it));
            if (old2 != c->b.f1) {
                sePlaySystemSound(SeList_cursor);
            }
            if (w->s.cb24 != 0) {
                w->s.cb24(obj, w->s.f20, w->s.buttons, c->b.f1);
            }
            if (it->cb != 0) {
                it->cb(obj, w->s.f20, w->s.buttons, c->b.f1);
            }
        } else if (w->s.buttons & 8) {
            int old2 = c->b.f1;
            do {
                if (++c->b.f1 > c->b.lo - 1) {
                    c->b.f1 = 0;
                }
                if (c->b.f1 == old2) {
                    break;
                }
            } while (!hasSel(it));
            if (old2 != c->b.f1) {
                sePlaySystemSound(SeList_cursor);
            }
            if (w->s.cb24 != 0) {
                w->s.cb24(obj, w->s.f20, w->s.buttons, c->b.f1);
            }
            if (it->cb != 0) {
                it->cb(obj, w->s.f20, w->s.buttons, c->b.f1);
            }
        } else if (w->s.buttons & 0x780) {
            if (it->cb != 0) {
                it->cb(obj, w->s.f20, w->s.buttons, c->b.f1);
            }
        }
    }
    if (w->s.buttons != 0 && w->s.cb24 != 0) {
        w->s.cb24(obj, w->s.f20, w->s.buttons, c->b.f1);
    }
}

static void T_00094740(Obj *obj, int flags, Cb a2, int a3, float t)
{
    Work *w = getWork(obj);
    int on = flags & 1;
    int f8 = flags & 8;
    int m;

    w->s.buttons = 0;
    getWork(obj)->s.f20 = a3;
    getWork(obj)->s.cb24 = a2;
    if (w->s.cur != -1 && curItem(w)->kind == 3 && on) {
        if (padHeld(&padManagerData, &D_00136E78, 0)) {
            w->s.buttons |= 1;
        }
        if ((padHeld(&padManagerData, &D_00136E78, 10)) && f8) {
            w->s.buttons |= 0x801;
        }
        if (padHeld(&padManagerData, &D_00136E78, 1)) {
            w->s.buttons |= 2;
        }
        if (flags & 4) {
            if (padTrig(&padManagerData, &D_00136E78, 2)) {
                w->s.buttons |= 0x10;
            }
            if (padTrig(&padManagerData, &D_00136E78, 3)) {
                w->s.buttons |= 0x20;
            }
            if (padTrig(&padManagerData, &D_00136E78, 4)) {
                w->s.buttons |= 4;
            }
            if (padTrig(&padManagerData, &D_00136E78, 5)) {
                w->s.buttons |= 8;
            }
        } else {
            if (padTrig(&padManagerData, &D_00136E78, 2)) {
                w->s.buttons |= 4;
            }
            if (padTrig(&padManagerData, &D_00136E78, 3)) {
                w->s.buttons |= 8;
            }
            if (padTrig(&padManagerData, &D_00136E78, 4)) {
                w->s.buttons |= 0x10;
            }
            if (padTrig(&padManagerData, &D_00136E78, 5)) {
                w->s.buttons |= 0x20;
            }
        }
        if (padHeld(&padManagerData, &D_00136E78, 6)) {
            w->s.buttons |= 0x80;
        }
        if (padHeld(&padManagerData, &D_00136E78, 7)) {
            w->s.buttons |= 0x100;
        }
        if (padHeld(&padManagerData, &D_00136E78, 8)) {
            w->s.buttons |= 0x200;
        }
        if (padHeld(&padManagerData, &D_00136E78, 9)) {
            w->s.buttons |= 0x400;
        }
    }
    func_00093CD0(w, t);
    if (w->s.cur != -1) {
        m = *(int *)&curItem(w)->sub.b & 0x600;
        if (m == 0) {
            func_00093F40(obj);
        } else if (m == 0x200) {
            func_000943F8(obj);
        }
    }
    func_000936A8(w, on);
    func_00093278(w, t);
}
