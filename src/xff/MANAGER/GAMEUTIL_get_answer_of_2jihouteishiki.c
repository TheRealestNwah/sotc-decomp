static inline float sqrtF(float x)
{
    float r;
    __asm__ __volatile__("sqrt.s %0, %1" : "=f"(r) : "f"(x));
    return r;
}

int GAMEUTIL_get_answer_of_2jihouteishiki(float *x1, float *x2, float a, float b, float c)
{
    float d = b * b - a * 4.0f * c;
    int ok = 1;
    float t;
    if (d < 0.0f) ok = 0;
    d = sqrtF(d);
    *x1 = (d - b) / (a + a);
    *x2 = (-b - d) / (a + a);
    t = *x1;
    if (t < *x2) {
        *x1 = *x2;
        *x2 = t;
    }
    return ok;
}
