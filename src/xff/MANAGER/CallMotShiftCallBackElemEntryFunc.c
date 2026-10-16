typedef struct {
    int id;
    void (*func)(void *, int, int, int);
    int a;
    int b;
} MotShiftEntry;

int CallMotShiftCallBackElemEntryFunc(int *list, int id, void *arg)
{
    int n = list[0];
    MotShiftEntry *e;
    int i;

    if (n != 0) {
        e = (MotShiftEntry *)list[1];
        for (i = 0; i < n; i++, e++) {
            if (e->id == id && e->func != 0) {
                e->func(arg, id, i, e->b);
                return 0;
            }
        }
    }
    return -1;
}
