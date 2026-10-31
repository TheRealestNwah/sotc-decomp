typedef int qword __attribute__((mode(TI)));

typedef struct {
    qword q0;
    qword pos;
    qword vel;
    char pad30[0x20];
} WormNode;

typedef struct {
    WormNode node[38];
    char padBE0[0x40];
    qword hist[40];
    char a[0x20];
    char b[0x20];
    char c[0x20];
    char padF00[0x39B];
    char active;
} WormWork;

extern qword ZeroVector;
extern int D_0017B8C8;
extern char *GetSCRCharaAIWorkPtr(void *obj);
extern void nico_calcWormGenealogicalNodeNextBase(void **arg);

void nico_calcWormGenealogicalNodeNext(void **arg)
{
    WormWork *w;
    int i;

    w = (WormWork *)(((int)GetSCRCharaAIWorkPtr(*arg) + 0x41B3) & ~0xF);
    nico_calcWormGenealogicalNodeNextBase(arg);
    if (w->active != 0) {
        WormNode *n;

        i = D_0017B8C8;
        n = (WormNode *)(i * 0x50 + (int)w);

        n->vel = ZeroVector;
        w->hist[i] = n->pos;
        w->a[i] = 0;
        w->b[i] = 0;
        w->c[i] = 0;
    }
    D_0017B8C8++;
}
