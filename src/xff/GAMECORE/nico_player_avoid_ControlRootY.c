typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
typedef struct { Vec4 geometry[4]; Vec4 position; } CollisionPoint;
typedef struct { int f0, id; } FinderEntry;
typedef struct { Vec4 m[4]; } Matrix;
extern char *GetCharacterClass(void *);
extern FinderEntry *ClipCollisionFinderCallBack(char *, float *, Vec4 *, int *,
    int (*)(FinderEntry *, void *), void *);
extern int character_ikcolattrfilter(FinderEntry *, void *);

void nico_player_avoid_ControlRootY(void **object)
{
    Vec4 start, finish;
    CollisionPoint hit;
    char *character = GetCharacterClass(object[0]);
    Matrix *matrix = (Matrix *)((int)object[5] * 64 + (int)object[2]);

    start.q = matrix->m[3].q;
    finish.q = start.q;
    start.f[1] = *(float *)(character + 0x44);
    finish.f[1] = matrix->m[3].f[1] + 0.15f;
    if (ClipCollisionFinderCallBack((char *)&hit, start.f, &finish,
            (int *)(character + 0xE20), character_ikcolattrfilter, 0) != 0)
        *(float *)(character + 0x44) -= finish.f[1] - hit.position.f[1];
}
