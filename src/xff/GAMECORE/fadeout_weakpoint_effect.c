typedef struct {
    int a;
    int state;
    int b[2];
    int x10;
    char pad[0x78 - 0x14];
} WeakPointEffect;

extern int D_0017ABB0;
extern WeakPointEffect B_0018A9B0[8];

void fadeout_weakpoint_effect(void)
{
    WeakPointEffect *p;
    int i;
    if (D_0017ABB0 == 0) return;
    p = B_0018A9B0;
    for (i = 0; i < 8; i++, p++) {
        p->x10 = 0;
        p->state = 2;
    }
}
