typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;

void setWormIKAttainXVector(char *p, Vec4 *v)
{
    ((Vec4 *)(p + 0xA00))->i[0] = 1;
    ((Vec4 *)(p + 0xA10))->q = v->q;
}
