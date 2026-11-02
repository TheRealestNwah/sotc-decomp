typedef struct {
    char data[0xC];
} InterpValue;

typedef struct {
    int a;
    int b;
    int c;
    union { int i; float f; } d;
    InterpValue v[3];
} ExprBlock;

typedef struct {
    ExprBlock block;
    int flag;
} ExprSlot;

typedef struct {
    int id;
    char status[0x10];
    char ratio[0x20];
    ExprBlock base[2];
    int flag;
    ExprSlot slots[30];
} Expression;

extern void GAMEUTIL_reset_status_manager(void *, int);
extern void GAMEUTIL_constructor_interp_ratio_cntrl(void *);
extern float GAMEUTIL_reset_interp_value_cntrl(void *, float);

static inline void resetBlock(ExprBlock *b)
{
    b->a = 0;
    b->d.i = 0;
    b->c = 0;
    b->b = 0;
    GAMEUTIL_reset_interp_value_cntrl(&b->v[0], b->d.f);
    GAMEUTIL_reset_interp_value_cntrl(&b->v[1], 0.0f);
    GAMEUTIL_reset_interp_value_cntrl(&b->v[2], 0.0f);
}

static inline void resetPair(ExprBlock *p)
{
    p[0].a = 0;
    p[0].d.i = 0;
    p[0].c = 0;
    p[0].b = 0;
    GAMEUTIL_reset_interp_value_cntrl(&p[0].v[0], p[0].d.f);
    GAMEUTIL_reset_interp_value_cntrl(&p[0].v[1], 0.0f);
    GAMEUTIL_reset_interp_value_cntrl(&p[0].v[2], 0.0f);
    p[1].a = 0;
    p[1].d.i = 0;
    p[1].c = 0;
    p[1].b = 0;
    GAMEUTIL_reset_interp_value_cntrl(&p[1].v[0], p[1].d.f);
    GAMEUTIL_reset_interp_value_cntrl(&p[1].v[1], 0.0f);
    GAMEUTIL_reset_interp_value_cntrl(&p[1].v[2], 0.0f);
}

void init_expression(Expression *ex, int id)
{
    int i;
    ExprSlot *s;

    ex->id = id;
    GAMEUTIL_reset_status_manager(ex->status, 0);
    GAMEUTIL_constructor_interp_ratio_cntrl(ex->ratio);
    resetPair(ex->base);
    ex->flag = 0;
    for (i = 0; i < 30; i++) {
        s = &ex->slots[i];
        resetBlock(&s->block);
        s->flag = 0;
    }
}
