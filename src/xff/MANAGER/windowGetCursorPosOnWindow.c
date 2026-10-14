typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;
extern Vec4 D_00139B90;

void windowGetCursorPosOnWindow(char *w, Vec4 *pos)
{
    char *o = *(char **)(w + 4);
    pos->q = D_00139B90.q;
    pos->f[0] -= *(float *)(o + 0x264);
    pos->f[1] -= *(float *)(o + 0x268);
}
