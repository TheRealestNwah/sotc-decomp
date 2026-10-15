typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;

extern Vec4 ZeroVector;

typedef struct {
    int state;
    char pad4[0xC];
    Vec4 a;
    Vec4 b;
    int c;
    int d;
} NeckTurn;

void constructor_neck_turn(NeckTurn *n)
{
    n->state = 0;
    n->a.q = ZeroVector.q;
    n->b.q = ZeroVector.q;
    n->c = 0;
    n->d = 0;
}
