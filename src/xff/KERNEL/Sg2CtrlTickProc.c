typedef struct { void (*func)(void); int count; } Ctrl;
extern Ctrl B_000C5A80[];
extern volatile int B_000C5B00;

void Sg2CtrlTickProc(void)
{
    int i;
    Ctrl *c = B_000C5A80;
    B_000C5B00++;
    for (i = 15; i >= 0; i--, c++) {
        c->func();
        c->count++;
    }
}
