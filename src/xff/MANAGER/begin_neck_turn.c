typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;
extern Vec4 ZeroVector;
typedef struct { int a; char pad[0xC]; Vec4 v10; Vec4 v20; int on; int b; } Neck;

void begin_neck_turn(Neck *n)
{
    if (n->on == 0) {
        n->a = 0;
        n->v10.q = ZeroVector.q;
        n->v20.q = ZeroVector.q;
        n->on = 1;
    }
    n->b = 0;
}
