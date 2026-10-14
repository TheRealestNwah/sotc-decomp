typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;

int get_predict_hit_position_nico_sight_on(Vec4 *out, char *p)
{
    out->q = ((Vec4 *)(p + 0x1D0))->q;
    return ((Vec4 *)(p + 0x1D0))[1].i[0];
}
