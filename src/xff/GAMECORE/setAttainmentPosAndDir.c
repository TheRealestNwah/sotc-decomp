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

void setAttainmentPosAndDir(Attainment *a, Vec4 *pos, Vec4 *dir)
{
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
    a->dir.q = dir->q;
    a->unkA8 = 1;
}
