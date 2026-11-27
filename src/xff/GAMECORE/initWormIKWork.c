extern char ZeroVector[], YUnitVector[];
extern char *GetSCRCharaAIWorkPtr(int);
extern char *GetCharacterClass(int);
extern void *memset(void *, int, unsigned int);
extern void ReflectIK_initWormDynamics(char *, void *, void *, void *, float);

#ifdef NONMATCHING /* 63 diffs, 124 vs 127 words: n is not copied into a second register on both paths of the n<=0 branch, so the post-loop constant and div.s schedule differs */
void initWormIKWork(int obj, float k)
{
    char *w = (char *)(((int)GetSCRCharaAIWorkPtr(obj) + 0x41B3) & -16);
    char *chr = GetCharacterClass(obj);
    char *s5 = *(char **)(chr + 0x358);
    float sum = 0.0f, avg;
    int i = 0x1F, n, cnt;
    char *q, *z;
    char *p;

    memset(w, 0, 0x18D0);
    w[0x1298] = 0;
    z = w + 0xEA0;
    q = w;
    do {
        ReflectIK_initWormDynamics(q, ZeroVector, YUnitVector, ZeroVector, k);
        q += 0x50;
        *z++ = 0;
    } while (--i >= 0);
    n = *(int *)(s5 + 4);
    *(int *)(w + 0x1294) = n;
    p = *(char **)(s5 + 8) + 0x10;
    for (cnt = 0; cnt < n; cnt++) {
            float len;
            __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                                 "vmul.xyz vf7, vf7, vf7\n"
                                 "vmulax.w ACC, vf0, vf7x\n"
                                 "vmadday.w ACC, vf0, vf7y\n"
                                 "vmaddz.w vf7, vf0, vf7z\n"
                                 ".word 0x4BA703BD\n"
                                 "vwaitq\n"
                                 "cfc2.ni $2, $vi22\n"
                                 "mtc1 $2, %0\n"
                                 : "=f"(len) : "r"(p) : "$2");
            sum += len;
            p += 0x40;
    }
    avg = sum / (float)(n - 1);
    *(float *)(w + 0x1280) = 10.0f;
    *(float *)(w + 0x1284) = -7.3499999f;
    *(float *)(w + 0x1288) = 0.5f;
    w[0x129B] = 1;
    *(float *)(w + 0x1290) = avg * 6.0f;
    {
        int j = 0x1F;
        char *y = w + 0xF00;
        do {
            *(int *)(y + 8) = 0;
            *(int *)(y + 0xC) = 0;
            *(int *)(y + 0x10) = 0;
            *(int *)(y + 0x14) = 0;
            y += 0x1C;
        } while (--j >= 0);
    }
    *(float *)(w + 0x128C) = 2.0f;
    {
        char *t = w + 0x12A0;
        float v = avg * *(float *)(chr + 0x90);
        t[0x60C] = 1;
        *(int *)(t + 0x604) = 0;
        *(int *)(t + 0x608) = 0;
        *(float *)(t + 0x600) = v;
    }
}
#endif
