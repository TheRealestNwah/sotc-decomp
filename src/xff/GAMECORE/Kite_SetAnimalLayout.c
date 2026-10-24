typedef int s128 __attribute__((mode(TI)));

/* The zero constant is reloaded for the second test, as with an inlined
   helper. */
static inline float sub_or_keep(float v, float d)
{
    float r = v - d;

    if (r > 0.0f) {
        return r;
    }
    return v;
}

/* Same layout as AI_SetAnimalLayout; each value is reduced by ofs when
   the result stays positive. */
void Kite_SetAnimalLayout(char *p, s128 *v, float a, float b, float ofs)
{
    *(s128 *)p = *v;
    {
        float x = sub_or_keep(a, ofs);
        float y = sub_or_keep(b, ofs);

        *(float *)(p + 0x10) = x;
        *(float *)(p + 0x14) = y;
    }
}
