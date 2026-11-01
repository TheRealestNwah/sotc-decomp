typedef struct {
    int max;
    void **slots;
    int count;
    int pad;
} ShockTable;

typedef struct {
    unsigned char active;
    char pad[0x3F];
} ShockWork;

typedef struct {
    int max;
    ShockWork *work;
} ShockWorkPool;

extern ShockTable *D_000408F8;
extern ShockTable B_00053F10;
extern void *B_00053F20[2];
extern ShockWorkPool B_00053F28;
extern ShockWork B_00053F30[16];

static inline void shock_table_init(ShockTable *t, void **slots, int max)
{
    int i;

    if (t != 0 && slots != 0) {
        t->slots = slots;
        t->max = max;
        D_000408F8 = t;
        for (i = 0; i < max; i++)
            D_000408F8->slots[i] = 0;
        D_000408F8->count = 0;
    }
}

static inline void shock_pool_init(ShockWorkPool *p, ShockWork *work, int max)
{
    int i;

    if (p != 0 && work != 0) {
        p->max = max;
        p->work = work;
        for (i = 0; i < max; i++)
            work[i].active = 0;
    } else {
        p->max = 0;
    }
}

void Init_Shock(void)
{
    shock_table_init(&B_00053F10, B_00053F20, 2);
    shock_pool_init(&B_00053F28, B_00053F30, 16);
}
