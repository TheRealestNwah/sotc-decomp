typedef unsigned int u_long128 __attribute__((mode(TI)));

typedef union {
    struct {
        u_long128 q0;
        u_long128 q1;
        int tail[2];
    } s;
    char alias;
} CollisionDynamics;

void CopyCollisionDynamics(CollisionDynamics *dst, CollisionDynamics *src)
{
    int *s;
    int *d;

    dst->s.q0 = src->s.q0;
    dst->s.q1 = src->s.q1;
    s = src->s.tail;
    d = dst->s.tail;
    d[0] = s[0];
    d[1] = s[1];
}
