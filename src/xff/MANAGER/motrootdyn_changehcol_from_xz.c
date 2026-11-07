extern char *GetCharacterClass(void *);
extern float *GetGeometryPointerSurfacePlane(void *);
extern void ParentLayoutObj(void *, void *);

static inline float vecDot(float *a, float *b)
{
    float dot;

    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vaddw.x vf7, vf0, vf0w\n"
                         "vmul.xyz vf6, vf5, vf6\n"
                         "vaddax.x ACC, vf0, vf6x\n"
                         "vmadday.x ACC, vf7, vf6y\n"
                         "vmaddz.x vf6, vf7, vf6z\n"
                         "qmfc2.ni $2, vf6\n"
                         "mtc1 $2, %0\n"
                         : "=f"(dot) : "r"(a), "r"(b) : "$2");
    return dot;
}

#define ABS(x) ((x) < 0.0f ? -(x) : (x))

void motrootdyn_changehcol_from_xz(void *obj)
{
    char *c = GetCharacterClass(obj);
    float *a;
    float *b;
    float d;

    if (*(int *)(c + 0xFBC) != 0) {
        a = GetGeometryPointerSurfacePlane(c + 0xC0);
        b = GetGeometryPointerSurfacePlane(c + 0xF70);
        d = ABS(vecDot(a, b) - 1.0f);
        if (d < 0.001f) {
            ParentLayoutObj(obj, c + 0xF70);
        }
    }
}
