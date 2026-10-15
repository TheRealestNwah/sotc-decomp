typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;
extern void GetMotionNodeQuaternionPos(Vec4 *, void *, void *, int, int);

void SCRGetCharNodePos(void *c, void *pos, int *node)
{
    Vec4 q;
    GetMotionNodeQuaternionPos(&q, c, pos, node[2], 1);
}
