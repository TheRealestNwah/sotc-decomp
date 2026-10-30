typedef struct {
    char pad0[0x30];
    int mode;
    int step;
    int active;
    int count;
    float limit;
    char pad44[0xAC - 0x44];
    int wait;
    char padB0[0xF0 - 0xB0];
    int flag;
} MoveWork;

extern void _resetBaseMoveWork(int a, MoveWork *p);
extern void func_0010A738(MoveWork *);

static const union {
    int i;
    float f;
} RO_00181598 = {0x7FFFFFFF};

static void func_0010A6E8(int a, MoveWork *p)
{
    _resetBaseMoveWork(a, p);
    p->limit = RO_00181598.f;
    p->flag = 0;
    p->step = 0;
    p->active = 1;
    p->wait = 0;
    p->mode = 1;
    p->count = 0;
    func_0010A738(p);
}
