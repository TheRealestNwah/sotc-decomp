extern void **isysGroupForFirst(void *, int);
extern void **isysGroupForNext(void *, int);
extern void isysGroupForExit(void *, int);
extern char *GetLayoutClass(void *);

static const union {
    int i;
    float f;
} RO_0017D540 = { 0x7FFFFFFF };

void *SearchNearestObjByGroup(void *group, float *pos, char **cls, float *dist)
{
    float best = RO_0017D540.f;
    void *obj = 0;
    void *found = 0;
    void **g;

    for (g = isysGroupForFirst(group, 0); g != 0; g = isysGroupForNext(g, 0)) {
        char *c;
        float d;

        obj = *g;
        c = GetLayoutClass(obj);
        __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                             "lqc2 vf5, 0x0(%2)\n"
                             "vsub.xyzw vf6, vf4, vf5\n"
                             "vmul.xyz vf6, vf6, vf6\n"
                             "vaddy.x vf6, vf6, vf6y\n"
                             "vaddz.x vf6, vf6, vf6z\n"
                             "qmfc2.ni $2, vf6\n"
                             "mtc1 $2, %0\n"
                             : "=f"(d) : "r"(*(float **)(c + 0x134)), "r"(pos) : "$2");
        if (*(signed char *)(c + 0x1B8) != 0 && d < best) {
            *cls = c;
            best = d;
            found = obj;
        }
    }
    if (obj != 0)
        isysGroupForExit(obj, 0);
    *dist = best;
    return found;
}
