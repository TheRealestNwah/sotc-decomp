/* Parked at 1 diff: static (alabel) pad-button update for an 0x21 object's work
 * block. Matches exactly when func_00093F40 is defined earlier in the same C file
 * (callee visibility changes delay-slot filling: gcc emits bnel for the mode
 * dispatch while the callee is only declared). Unpark together with func_00093F40
 * once this Source group (func_000936A8..T_00094740) shares one file. */
typedef struct { char pad0[8]; int type; char pad0C[0x38 - 0xC]; int cfg; char pad3C[0x44 - 0x3C]; } Item;
typedef struct { int pad0; Item *items; int pad8; int cur; int buttons; char pad14[0x20 - 0x14]; int f20; int f24; } Work;
typedef struct { char pad0[8]; unsigned char type; } Obj;
typedef struct { int pad0[2]; int held; int pad0C; int trig; } PadData;
extern PadData padManagerData;
extern int D_00136E78;
void func_00093CD0(Work *w, float t);
void func_00093F40(Obj *o);
void func_000943F8(Obj *o);
void func_000936A8(Work *w, int on);
void func_00093278(Work *w, float t);

static inline int padHeld(PadData *pad, int *map, int n) { return pad->held & (1 << ((signed char *)*map)[n]); }
static inline int padTrig(PadData *pad, int *map, int n) { return pad->trig & (1 << ((signed char *)*map)[n]); }
static inline Item *curItem(Work *w) { return &w->items[w->cur]; }
#define WORK(o) ((o)->type == 0x21 ? (Work *)((char *)(o) + 0x90) : 0)

#ifdef NONMATCHING
static void T_00094740(Obj *obj, int flags, int a2, int a3, float t)
{
    Work *w = WORK(obj);
    int on = flags & 1;
    int f8 = flags & 8;
    int m;

    w->buttons = 0;
    WORK(obj)->f20 = a3;
    WORK(obj)->f24 = a2;
    if (w->cur != -1 && (curItem(w)->type & 0xF) == 3 && on) {
        if (padHeld(&padManagerData, &D_00136E78, 0)) {
            w->buttons |= 1;
        }
        if ((padHeld(&padManagerData, &D_00136E78, 10)) && f8) {
            w->buttons |= 0x801;
        }
        if (padHeld(&padManagerData, &D_00136E78, 1)) {
            w->buttons |= 2;
        }
        if (flags & 4) {
            if (padTrig(&padManagerData, &D_00136E78, 2)) {
                w->buttons |= 0x10;
            }
            if (padTrig(&padManagerData, &D_00136E78, 3)) {
                w->buttons |= 0x20;
            }
            if (padTrig(&padManagerData, &D_00136E78, 4)) {
                w->buttons |= 4;
            }
            if (padTrig(&padManagerData, &D_00136E78, 5)) {
                w->buttons |= 8;
            }
        } else {
            if (padTrig(&padManagerData, &D_00136E78, 2)) {
                w->buttons |= 4;
            }
            if (padTrig(&padManagerData, &D_00136E78, 3)) {
                w->buttons |= 8;
            }
            if (padTrig(&padManagerData, &D_00136E78, 4)) {
                w->buttons |= 0x10;
            }
            if (padTrig(&padManagerData, &D_00136E78, 5)) {
                w->buttons |= 0x20;
            }
        }
        if (padHeld(&padManagerData, &D_00136E78, 6)) {
            w->buttons |= 0x80;
        }
        if (padHeld(&padManagerData, &D_00136E78, 7)) {
            w->buttons |= 0x100;
        }
        if (padHeld(&padManagerData, &D_00136E78, 8)) {
            w->buttons |= 0x200;
        }
        if (padHeld(&padManagerData, &D_00136E78, 9)) {
            w->buttons |= 0x400;
        }
    }
    func_00093CD0(w, t);
    if (w->cur != -1) {
        m = curItem(w)->cfg & 0x600;
        if (m == 0) {
            func_00093F40(obj);
        } else if (m == 0x200) {
            func_000943F8(obj);
        }
    }
    func_000936A8(w, on);
    func_00093278(w, t);
}
#endif
