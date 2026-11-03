#ifdef NONMATCHING /* found/aux s2-s3 register swap */
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
typedef struct { int f0; int id; } FinderEntry;
typedef struct { Vec4 geometry[4]; Vec4 position; } CollisionPoint;
static int func_000AE618(CollisionPoint *, Vec4 *, float *, Vec4 *, FinderEntry *, float);
extern int D_00136EF0;

static inline float dot3(Vec4 *a, Vec4 *b)
{
    float d;
    __asm__ __volatile__("lqc2 vf05, 0(%1)\n"
                         "lqc2 vf06, 0(%2)\n"
                         "vaddw.x vf07, vf00, vf00w\n"
                         "vmul.xyz vf06, vf05, vf06\n"
                         "vaddax.x ACC, vf00, vf06x\n"
                         "vmadday.x ACC, vf07, vf06y\n"
                         "vmaddz.x vf06, vf07, vf06z\n"
                         "qmfc2 %0, vf06\n"
                         : "=r"(d) : "r"(a), "r"(b));
    return d;
}

int NippingCheckCollisionFindetWithKeep4D(float *start, Vec4 *finish, int *finder, float keep)
{
    int count = finder[0];
    if (finder[1] < count)
        count = finder[1];
    if (count != 0) {
        Vec4 normal;
        Vec4 end;
        Vec4 auxiliary;
        CollisionPoint point;
        FinderEntry *entry = (FinderEntry *)finder[3];
        int found = 0;
        Vec4 *aux = &auxiliary;
        end.q = finish->q;
        while (--count != -1) {
            if (entry->f0 != 0 && func_000AE618(&point, &auxiliary, start, &end, entry, keep)) {
                if (found != 0 && dot3(aux, &normal) < 0.0f)
                    return 1;
                found = 1;
                end.q = point.position.q;
                normal.q = auxiliary.q;
            }
            D_00136EF0++;
            entry++;
        }
    }
    return 0;
}
#endif
