typedef struct {
    int id;
    int x4;
    int x8;
    union {
        int i;
        float f;
    } xC;
    char interp0[0xC];
    char interp1[0xC];
    char interp2[0xC];
    int x34;
} ExprNode;

typedef struct {
    char pad0[0x9C];
    int n;
    ExprNode node[30];
} ExprWork;

extern void GAMEUTIL_reset_interp_value_cntrl(void *, float);

static inline void resetInterp(void *p)
{
    GAMEUTIL_reset_interp_value_cntrl(p, 0.0f);
}

/* Each access recomputes the node address, which gives the original
   (n * size) + w operand order. */
#define NODE (&w->node[n])

void add_node_expression(ExprWork *w, int id)
{
    int n = w->n;

    if (n >= 30)
        return;
    NODE->xC.i = 0;
    NODE->id = 0;
    NODE->x8 = 0;
    NODE->x4 = 0;
    GAMEUTIL_reset_interp_value_cntrl(NODE->interp0, NODE->xC.f);
    resetInterp(NODE->interp1);
    resetInterp(NODE->interp2);
    NODE->x34 = 0;
    NODE->id = id;
    w->n++;
}
