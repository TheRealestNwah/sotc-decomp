extern int Kite_CmpPathPoint(char *, char *);
extern void *isysGetThisSubThread(void);
extern char *GetLayoutClass(void *);
extern int AI_CheckInAnimalLayout(float *, void *);

static inline float distXZSq(float *a, float *b)
{
    float d;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xz vf7, vf7, vf7\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "qmfc2.ni $2, vf7\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(a), "r"(b) : "$2");
    return d;
}

static inline float distXZ(float *a, float *b)
{
    float d;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xz vf7, vf7, vf7\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "vsqrt Q, vf7x\n"
                         "vwaitq\n"
                         "cfc2.ni $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(a), "r"(b) : "$2");
    return d;
}

static int func_000A1950(char *k)
{
    if (*(int *)(k + 0x38) != 0) {
        if (!Kite_CmpPathPoint(k + 0x600, k + 0x620)) {
            char *path = k + 0x7D0;
            char *lay = GetLayoutClass(isysGetThisSubThread());
            float *pos = (float *)(k + 0x560);
            float dPlayer = distXZSq(*(float **)(lay + 0x134), pos);
            float dTarget = distXZSq((float *)(k + 0x800), pos);
            float dist = distXZ(*(float **)(lay + 0x134), (float *)(k + 0x800));
            int far;

            if (!AI_CheckInAnimalLayout((float *)(k + 0x800), k + 0x50))
                far = 1;
            else if (AI_CheckInAnimalLayout(pos, *(void **)(lay + 0x134)))
                far = 0;
            else if (dTarget < dPlayer)
                far = 1;
            else
                far = 100.0f < *(float *)(path + 0x40) - dist;
            if (!far)
                return 1;
        }
        if (8.0f < *(float *)(k + 0x324) && AI_CheckInAnimalLayout((float *)(k + 0x800), k + 0x50))
            return 1;
    }
    return 0;
}
