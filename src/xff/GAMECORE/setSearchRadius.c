extern const float RO_001812EC;

static inline float fsqrt(float x)
{
    float r;

    __asm__ __volatile__("sqrt.s %0, %1" : "=f"(r) : "f"(x));
    return r;
}

void setSearchRadius(char *w, float radius)
{
    if (radius < 0.0f) {
        *(float *)(w + 0x3B8) = fsqrt(RO_001812EC);
    } else {
        *(float *)(w + 0x3B8) = radius;
    }
}
