typedef int s128 __attribute__((mode(TI)));

typedef struct {
    s128 unk0;
    s128 pos;
    s128 vel;
    s128 unk30;
    s128 unk40;
} WormNode;

typedef struct {
    WormNode node[0x26];
    char padBE0[0xC20 - 0xBE0];
    s128 prev[0x28];
    signed char a[0x20];
    signed char b[0x20];
    signed char c[0x20];
    char padF00[0x1294 - 0xF00];
    int count;
    signed char unk1298;
    signed char unk1299;
    signed char unk129A;
    signed char unk129B;
} WormWork;

extern char *GetSCRCharaAIWorkPtr(void *);
extern void nico_calcWormGenealogicalNodeTailBase(void **);
extern int D_0017B8C8;
extern s128 ZeroVector;

void nico_calcWormGenealogicalNodeTail(void **a)
{
    WormWork *w = (WormWork *)(((int)GetSCRCharaAIWorkPtr(*a) + 0x41B3) & ~0xF);
    signed char flag = w->unk129B;

    nico_calcWormGenealogicalNodeTailBase(a);
    w->unk129B = 0;
    if (flag != 0) {
        int i = D_0017B8C8;
        int c;
        WormNode *n = (WormNode *)(i * 0x50 + (int)w);
        n->vel = ZeroVector;
        w->prev[i] = n->pos;
        w->a[i] = 0;
        w->b[i] = 0;
        w->c[i] = 0;
        w->unk1298 = 1;
        c = D_0017B8C8;
        w->unk129A = 0;
        w->count = c;
    }
}
