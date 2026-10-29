typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
typedef struct { Vec4 geometry[4]; Vec4 position; } CollisionPoint;
typedef struct { int f0, id; } FinderEntry;
extern char B_0018B7B0[], B_0018B7E0[], B_0018B7F0[];
extern int B_0018B804;
extern float B_0018B800;
static float func_00091CE0(void *, s128 *, char *, char *, char *, int);
extern char *GetCharacterClass(void *);
extern FinderEntry *ClipCollisionFinderCallBack(char *, float *, Vec4 *, int *,
    int (*)(FinderEntry *, void *), void *);
extern int character_ikcolattrfilter(FinderEntry *, void *);

void nico_player_pendulum_Leg(void *object)
{
    CollisionPoint hit;
    Vec4 start;
    int found;
    char *character = GetCharacterClass(*(void **)object);
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(&start), "r"(B_0018B7B0), "r"((char *)object + 0x20) : "memory");
    found = (int)ClipCollisionFinderCallBack((char *)&hit, start.f, (Vec4 *)B_0018B7B0,
        (int *)(character + 0xE20), character_ikcolattrfilter, 0);
    B_0018B804 = found;
    if (found != 0)
        B_0018B800 = func_00091CE0(object, &hit.position.q, B_0018B7B0, B_0018B7F0, B_0018B7E0, 1);
}
