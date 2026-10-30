typedef int s128 __attribute__((mode(TI)));

typedef union {
    s128 *v;
    int i;
    s128 q;
} Word;

extern char *GetCharacterClass(int);
extern int DeleteTwoWayLink(void *);
extern int GetStageAreaNumberByPos(void *);
extern void setDataHeaderFromAreaIdx(char *);

static inline void quatAxisZ(void *out, void *q)
{
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "vmul.xyzw vf5, vf4, vf4\n"
                         "vmr32.xyzw vf6, vf4\n"
                         "vmul.xyzw vf7, vf6, vf4\n"
                         "vmr32.xyzw vf6, vf6\n"
                         "vmul.xyzw vf8, vf6, vf4\n"
                         "vsubx.z vf6, vf0, vf5x\n"
                         "vsuby.z vf6, vf6, vf5y\n"
                         "vaddw.y vf6, vf7, vf7w\n"
                         "vsuby.x vf6, vf8, vf8y\n"
                         "vsub.w vf6, vf0, vf0\n"
                         "vadd.w vf5, vf0, vf0\n"
                         "vmulw.xyz vf6, vf6, vf5w\n"
                         "vaddw.z vf6, vf6, vf0w\n"
                         "sqc2 vf6, 0x0(%0)\n"
                         : : "r"(out), "r"(q) : "memory");
}

void resetUserPathWork(int obj, char *w)
{
    char *cc = GetCharacterClass(obj);
    int area;

    *(int *)(w + 0x380) = 0;
    *(int *)(w + 0x90) = 0;
    *(int *)(w + 0xA8) = 0;
    *(int *)(w + 0xAC) = 0;
    *(int *)(w + 0x80) = -1;
    *(int *)(w + 0x84) = -1;
    *(int *)(w + 0x88) = -1;
    *(int *)(w + 0x8C) = -1;
    if (*(int *)(w + 0xA4) != 0) {
        *(int *)(w + 0xA4) = 0;
        DeleteTwoWayLink(w + 0x98);
    }
    *(int *)(w + 0x94) = 0;
    *(int *)(w + 0x408) = 0;
    *(int *)(w + 0x40C) = 0;
    *(int *)(w + 0x410) = 0;
    *(int *)(w + 0x41C) = -1;
    *(int *)(w + 0x420) = -1;
    *(int *)(w + 0x424) = -1;
    *(float *)(w + 0xE4) = 3.14159251f;
    *(int *)(w + 0x428) = -1;
    *(int *)(w + 0x42C) = -1;
    *(int *)(w + 0x430) = -1;
    *(int *)(w + 0xE0) = 0;
    *(int *)(w + 0x3A0) = -1;
    *(int *)(w + 0x3A4) = -1;
    *(s128 *)(w + 0x0) = *((Word *)(cc + 0x134))->v;
    *(s128 *)(w + 0x10) = *((Word *)(cc + 0x134))->v;
    quatAxisZ(w + 0x20, ((Word *)(cc + 0x13C))->v);
    area = GetStageAreaNumberByPos(*(void **)(cc + 0x134));
    *(int *)(w + 0x3A8) = area;
    *(int *)(w + 0x3AC) = area;
    setDataHeaderFromAreaIdx(w);
}
