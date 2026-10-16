#define VU_INNER_PRODUCT(ret, a, b) \
    __asm__ __volatile__("lqc2 vf05, 0x0(%1)\n" \
                         "lqc2 vf06, 0x0(%2)\n" \
                         "vaddw.x vf07, vf00, vf00w\n" \
                         "vmul.xyz vf06, vf05, vf06\n" \
                         "vaddax.x ACC, vf00, vf06x\n" \
                         "vmadday.x ACC, vf07, vf06y\n" \
                         "vmaddz.x vf06, vf07, vf06z\n" \
                         "qmfc2 $2, vf06\n" \
                         "mtc1 $2, %0\n" \
                         : "=f"(ret) : "r"(a), "r"(b) : "$2")

void GAMEUTIL_get_divide_vector_value(float *a, float *b, float *c, float *v, float *x, float *y, float *z)
{
    if (a != 0) VU_INNER_PRODUCT(*a, v, x);
    if (b != 0) VU_INNER_PRODUCT(*b, v, y);
    if (c != 0) VU_INNER_PRODUCT(*c, v, z);
}
