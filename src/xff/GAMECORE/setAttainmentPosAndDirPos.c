typedef int s128 __attribute__((mode(TI)));

typedef union {
    s128 q;
    float f[4];
} Vec4;

typedef struct {
    char pad0[0x60];
    Vec4 pos;
    char pad70[0x20];
    int active;
    void *target;
    char link[0xC];
    int linked;
    int unkA8;
    int unkAC;
    Vec4 dir;
    Vec4 prevDir;
    char padD0[0x340];
    int unk410;
} Attainment;

extern int memcmp(const void *, const void *, unsigned int);
extern void DeleteTwoWayLink(void *);

void setAttainmentPosAndDirPos(Attainment *a, Vec4 *pos, Vec4 *target)
{
    Vec4 d;

    if (memcmp(&a->pos, pos, 0x10) != 0) {
        a->pos.q = pos->q;
        a->pos.f[3] = 1.0f;
        a->active = 1;
    }
    if (a->linked != 0) {
        a->linked = 0;
        DeleteTwoWayLink(a->link);
    }
    a->unkA8 = 0;
    a->target = 0;
    a->unk410 = 0;
    a->unkAC = 0;
    a->unkA8 = 1;
    a->prevDir.q = a->dir.q;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)
"
                         "lqc2 vf6, 0x0(%2)
"
                         "vsub.xyzw vf7, vf5, vf6
"
                         "sqc2 vf7, 0x0(%0)
"
                         : : "r"(&d), "r"(target), "r"(pos) : "memory");
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)
"
                         "vmul.xyz vf7, vf5, vf5
"
                         "vmulax.w ACC, vf0, vf7x
"
                         "vmadday.w ACC, vf0, vf7y
"
                         "vmaddz.w vf7, vf0, vf7z
"
                         "vrsqrt Q, vf0w, vf7w
"
                         "vwaitq
"
                         "vmulq.xyz vf5, vf5, Q
"
                         "sqc2 vf5, 0x0(%0)
"
                         : : "r"(&d) : "memory");
    a->dir.q = d.q;
    a->dir.f[3] = 1.0f;
}
