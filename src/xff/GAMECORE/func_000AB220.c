typedef struct {
    char pad0[0x250];
    int state;
    char pad254[8];
    int kind;
    int mode;
    char pad264[4];
    int ready;
} Work;

extern void *isysGetThisSubThread(void);


static void func_000AB220(Work *w)
{
    isysGetThisSubThread();
    w->ready = 0;
    switch (w->mode) {
    case 0:
        if (w->state == 13) {
            w->kind = 0;
            w->ready = 1;
        }
        break;
    case 1:
        if (w->state == 14) {
            w->kind = 1;
            w->ready = 1;
        }
        break;
    case 2:
        if (w->state == 15) {
            w->kind = 2;
            w->ready = 1;
        }
        break;
    case 3:
        if (w->state == 16) {
            w->kind = 3;
            w->ready = 1;
        }
        break;
    case 4:
        if (w->state == 16) {
            w->kind = 4;
            w->ready = 1;
        }
        break;
    case 5:
        if (w->state == 15) {
            w->kind = 5;
            w->ready = 1;
        }
        break;
    case 6:
        if (w->state == 15) {
            w->kind = 6;
            w->ready = 1;
        }
        break;
    }
}
