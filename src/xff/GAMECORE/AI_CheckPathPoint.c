extern char *GetLayoutClass(void *);

int AI_CheckPathPoint(void *obj, float *pos, float r, float h)
{
    float r2 = r * r;
    char *c = GetLayoutClass(obj);
    float *p;
    float half;
    float d;

    if (c == 0)
        return 0;
    half = h * 0.5f;
    p = *(float **)(c + 0x134);
    if (p[1] < pos[1] - half)
        return 0;
    if (pos[1] + half < p[1])
        return 0;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xz vf7, vf7, vf7\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "qmfc2.ni $2, vf7\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(p), "r"(pos) : "$2");
    if (r2 < d)
        return 0;
    return 1;
}
