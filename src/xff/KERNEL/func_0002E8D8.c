typedef struct {
    int time;
    int x4;
    int type;
    float x;
    float y;
} Node;
typedef struct {
    char pad0[0x30];
    int x30;
    int x34;
    int x38;
    Node *x3C;
    Node *loop;
    int count;
} Filt;
extern char B_000E251C[];
extern char B_000E2368[];
extern int DIntr(void);
extern void EIntr(void);
/* Parked attempt: 25 words differ (register allocation and scheduling). */
#ifdef NONMATCHING
extern void func_0002E728(Filt *base, int i, int time, int cb, float x, float y);

static void func_0002E8D8(Node *node, int ch, int a2, int a3)
{
    int intr = DIntr();
    Filt *f;
    int sel;
    int type;
    int d;
    int time;
    float x, y;

    if (ch >= 4)
        f = (Filt *)B_000E2368;
    else
        f = (Filt *)(B_000E251C + ch * 0x1D4);
    type = node->type;
    sel = 0;
    switch (type) {
    case 12:
        f->count = node->x4;
        node++;
        f->loop = node;
        func_0002E8D8(node, ch, a2, a3);
        break;
    case 13:
        if (--f->count == 0) {
            f->loop = 0;
            node++;
            goto set;
        }
        if (f->count < 0)
            f->count = -1;
        func_0002E8D8(f->loop, ch, a2, a3);
        break;
    default:
        if (type >= 6) {
            sel = 1;
            type -= 6;
        }
    set:
        time = node->x4;
        f->x34 = a3;
        f->x30 = a2;
        f->x3C = node;
        x = node->x;
        y = node->y;
        if (node[0].time == 0x7FFFFFFF || node[1].time == 0x7FFFFFFF)
            d = 0x7FFFFFFF;
        else
            d = node[1].time - node[0].time;
        f->x38 = d;
        func_0002E728(f, sel, time, type, x, y);
        break;
    }
    if (intr)
        EIntr();
}
#endif
