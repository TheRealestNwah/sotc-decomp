/* ~11 diffs, same size (91 words). Static (alabel) fade-group tick: for each 0x44-byte item, state 1/4 starts the fade (func_00093880, then state 2/5), state 2/5 steps it (func_00093B38). Only the branch-likely/delay-slot form of the two inlined state checks differs (Original shares the second compare between the case 1 and case 4 copies via bnel). */
typedef struct { int *p; int pad; unsigned int state : 4; char pad2[0x38]; } FadeObj;
typedef struct { int pad0; FadeObj *items; int count; } FadeGroup;

extern void func_00093880(FadeObj *o, int dir);
extern void func_00093B38(FadeObj *o, float dt);

#ifdef NONMATCHING
static inline void start(FadeObj *o)
{
    switch (o->state) {
    case 1:
        func_00093880(o, o->p[3]);
        o->state = 2;
        break;
    case 4:
        func_00093880(o, o->p[3]);
        o->state = 5;
        break;
    }
}

void func_00093CD0(FadeGroup *g, float dt)
{
    int i;
    for (i = 0; i < g->count; i++) {
        FadeObj *o = (FadeObj *)((char *)g->items + i * 0x44);
        switch (o->state) {
        case 0:
            break;
        case 1:
            start(o);
            break;
        case 2:
            func_00093B38(o, dt);
            break;
        case 3:
            break;
        case 4:
            start(o);
            break;
        case 5:
            func_00093B38(o, dt);
            break;
        }
    }
}
#endif
