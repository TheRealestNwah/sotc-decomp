typedef struct ObjMgr {
    int heap;
    char pad4[4];
    int flags;
    unsigned short groups;
    char padE[2];
    struct ObjMgr *next;
    void (*dispose)(struct ObjMgr *);
} ObjMgr;

typedef struct {
    char pad0[9];
    unsigned char alive;
} ObjHead;

typedef struct {
    ObjHead *obj;
    char pad4[0xE];
    unsigned short objNext;
    char pad14[2];
    unsigned short freeNext;
} SysGroup;

extern int GetThreadId();
extern void SignalSema(int);
extern void WaitSema(int);
extern void func_00019AA8(SysGroup *);
extern void iosFree(int);
extern int B_000BF6CC;
extern SysGroup *B_000BF6C4;
extern ObjMgr *B_000BF6C8;
extern int D_00040D5C;
extern int D_00040D60;
extern SysGroup B_0006D640[];

/* Parked: 94 diffs: register allocation in the free-list loop (target keeps g in a0, nx in s0, keep in s1) */
#ifdef NONMATCHING
void isysDeleteObjManager(void)
{
    SysGroup *g;
    SysGroup *nx;
    SysGroup *keep;
    ObjMgr *m;
    ObjMgr *mn;
    ObjMgr *live;
    ObjMgr *dead;
    int tid = GetThreadId();

    if (tid == D_00040D5C) {
        D_00040D60 += 1;
    } else {
        WaitSema(B_000BF6CC);
        D_00040D5C = tid;
        D_00040D60 = 1;
    }
    keep = 0;
    for (g = B_000BF6C4; g != 0; g = nx) {
        nx = g->freeNext ? &B_0006D640[g->freeNext] : 0;
        if (g->obj->alive == 0) {
            func_00019AA8(g);
        } else {
            g->freeNext = keep ? keep - B_0006D640 : 0;
            keep = g;
        }
    }
    B_000BF6C4 = keep;
    for (g = keep; g != 0; g = g->freeNext ? &B_0006D640[g->freeNext] : 0) {
    }
    live = 0;
    dead = 0;
    for (m = B_000BF6C8; m != 0; m = mn) {
        mn = m->next;
        if (!(m->flags & 0xFFFEFF00)) {
            for (g = m->groups ? &B_0006D640[m->groups] : 0; g != 0;
                 g = g->objNext ? &B_0006D640[g->objNext] : 0) {
                func_00019AA8(g);
            }
            m->next = dead;
            dead = m;
            m->groups = 0;
        } else {
            m->next = live;
            live = m;
        }
    }
    B_000BF6C8 = live;
    for (m = dead; m != 0; m = mn) {
        mn = m->next;
        if (m->dispose != 0) {
            m->dispose(m);
        }
        iosFree(m->heap);
    }
    for (m = live; m != 0; m = m->next) {
    }
    if (--D_00040D60 == 0) {
        D_00040D5C = -1;
        SignalSema(B_000BF6CC);
    }
}
#else
extern void isysDeleteObjManager(void);
#endif
