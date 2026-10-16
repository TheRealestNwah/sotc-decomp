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

void setAttainmentPosAndDirPosAndLock(Attainment *a, Vec4 *pos, Vec4 *target)
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
    a->prevDir.q = a->dir.q;
    a->unkA8 = 1;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(&d), "r"(target), "r"(pos) : "memory");
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(&d) : "memory");
    a->dir.q = d.q;
    a->unkAC = 1;
    a->dir.f[3] = 1.0f;
}
