typedef struct {
    int mode;
    int state;
    int pad8;
    int active;
    int flag;
    int pad14;
    float start;
} Waiter;

typedef struct {
    char pad0[0x178];
    float time;
} GlobalVar;

extern GlobalVar gcGlobalVar;
extern float D_0017ABA8;
extern float D_0017ABAC;
extern int func_0004D260(Waiter *);
extern void func_0004D0C8(Waiter *, int);
extern void scrRun(void);

static void func_0004E960(Waiter *w)
{
    float limit;

    do {
        if (w->mode == 0)
            limit = D_0017ABA8;
        else
            limit = D_0017ABAC;
        w->state = 0;
    } while (0);
    w->start = gcGlobalVar.time;
    while (w->active) {
        switch (w->state) {
        case 0:
            if (func_0004D260(w)) {
                w->start = gcGlobalVar.time;
                w->state = 1;
            }
            break;
        case 1:
            func_0004D260(w);
            if (limit < gcGlobalVar.time - w->start) {
                w->flag = 0;
                w->state = 2;
            }
            break;
        case 2:
            if (func_0004D260(w)) {
                func_0004D0C8(w, 0);
                w->state = 3;
            }
            break;
        }
        scrRun();
    }
}
