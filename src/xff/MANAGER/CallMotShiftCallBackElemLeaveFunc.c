typedef struct { int id; int (*entry)(void *, int, int, int); int (*leave)(void *, int, int, int); int arg; } ShiftCB;
typedef struct { int n; ShiftCB *e; } ShiftList;

int CallMotShiftCallBackElemLeaveFunc(ShiftList *l, int id, void *arg)
{
    int i;
    ShiftCB *e = l->e;
    for (i = 0; i < l->n; i++, e++) {
        if (e->id == id && e->leave != 0) {
            e->leave(arg, id, i, e->arg);
            return 0;
        }
    }
    return -1;
}
