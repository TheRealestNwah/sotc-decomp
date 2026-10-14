typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;

void charrootdyn_getLimitMode(Vec4 *m, char *c)
{
    if (*(signed char *)(c + 0x52D) != 0) {
        m->i[0] = 1;
        m->f[1] = *(float *)(c + 0x400);
        m->i[2] = *(int *)(c + 0xC30);
    } else {
        m->i[2] = 0;
        m->f[1] = 0.0f;
        m->i[0] = 3;
    }
}
