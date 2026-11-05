typedef int s128 __attribute__((mode(TI)));

typedef struct {
    char pad[0x14];
    int id;
    char pad18[0x1C];
} AnimalType;

typedef struct {
    char pad[0x10];
    AnimalType *types;
} AnimalTypeTable;

typedef struct {
    char pad[0x34];
    short type;
} SObjNode;

typedef struct {
    s128 pos;
    int a;
    int b;
    int c;
    int pad;
} KitePathPoint;

typedef struct {
    KitePathPoint pts[4];
    s128 pos;
    float x;
    float y;
    int s98;
    int list[10];
    int count;
    void *obj;
    int padcc;
} KiteSub;

typedef struct {
    int a;
    int b;
    int pad8[2];
    KitePathPoint pts[6];
    s128 pos;
    float x;
    float y;
    int e8;
    int ec;
    void *obj;
    int padf4[11];
    KiteSub sub;
    char special[1];
} KitePathWork;

extern AnimalTypeTable SH_SmallAnimalTypeDEFAULT;
extern SObjNode *getSObjNode(void *);
extern void Kite_InitSpecialPathWork(void *);

static inline void initPoint(KitePathPoint *p)
{
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)" : : "r"(p) : "memory");
    p->a = -1;
    p->b = 0;
    p->c = -1;
}

void Kite_InitKitePathWork(KitePathWork *w, void *obj, float x, float y)
{
    SObjNode *n = getSObjNode(obj);
    KiteSub *s;
    int i;

    w->b = -1;
    w->a = -1;
    if (n != 0 && SH_SmallAnimalTypeDEFAULT.types != 0)
        w->b = SH_SmallAnimalTypeDEFAULT.types[n->type].id;
    initPoint(&w->pts[0]);
    initPoint(&w->pts[1]);
    initPoint(&w->pts[2]);
    initPoint(&w->pts[3]);
    initPoint(&w->pts[4]);
    initPoint(&w->pts[5]);
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)" : : "r"(&w->pos) : "memory");
    w->x = x;
    w->y = y;
    w->e8 = 0;
    w->ec = 0;
    w->obj = obj;
    s = &w->sub;
    s->obj = obj;
    initPoint(&s->pts[0]);
    initPoint(&s->pts[1]);
    initPoint(&s->pts[2]);
    initPoint(&s->pts[3]);
    s->count = 4;
    s->x = x;
    s->y = y;
    s->s98 = 0;
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)" : : "r"(&s->pos) : "memory");
    for (i = 9; i >= 0; i--)
        s->list[i] = 0;
    Kite_InitSpecialPathWork(w->special);
}
