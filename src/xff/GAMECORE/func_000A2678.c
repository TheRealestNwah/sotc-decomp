#ifdef NONMATCHING
/* 6 diffs: gcc orders the three else-branch stores 98/9C/A0 instead of A0/98/9C; permuter found nothing. */
extern void AI_GetAccelA3XYZ(float *out, float *a, float *b, float *c, float *d, float *e, float t);
extern void AI_GetAccelB3XYZ(float *out, float *a, float *b, float *c, float *d, float *e, float t);
extern void AI_GetAccelC3XYZ(float *out, float *a, float *b, float *c, float *d, float *e, float t);
extern float AI_GetAccelA3(float, float, float, float, float, float);
extern float AI_GetAccelB3(float, float, float, float, float, float);
extern float AI_GetAccelC3(float, float, float, float, float, float);

static void func_000A2678(void *u, char *w)
{
    float zero = 0.0f;

    AI_GetAccelC3XYZ((float *)(w + 0x20), (float *)(w + 0x30), (float *)(w + 0x40), (float *)(w + 0x50), (float *)(w + 0x60), (float *)(w + 0x70), *(float *)(w + 0x90));
    AI_GetAccelA3XYZ((float *)w, (float *)(w + 0x30), (float *)(w + 0x50), (float *)(w + 0x60), (float *)(w + 0x70), (float *)(w + 0x20), *(float *)(w + 0x90));
    AI_GetAccelB3XYZ((float *)(w + 0x10), (float *)(w + 0x30), (float *)(w + 0x40), (float *)(w + 0x50), (float *)(w + 0x60), (float *)(w + 0x20), *(float *)(w + 0x90));
    if (*(float *)(w + 0x94) != zero) {
        *(float *)(w + 0xA0) = AI_GetAccelC3(zero, zero, zero, zero, *(float *)(w + 0x94), *(float *)(w + 0x90));
        *(float *)(w + 0x98) = AI_GetAccelA3(zero, zero, zero, *(float *)(w + 0x94), *(float *)(w + 0x90), *(float *)(w + 0xA0));
        *(float *)(w + 0x9C) = AI_GetAccelB3(zero, zero, zero, zero, *(float *)(w + 0x90), *(float *)(w + 0xA0));
    } else {
        *(float *)(w + 0x98) = zero;
        *(float *)(w + 0x9C) = zero;
        *(float *)(w + 0xA0) = zero;
    }
}
#endif
