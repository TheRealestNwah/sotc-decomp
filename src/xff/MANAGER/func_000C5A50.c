#ifdef NONMATCHING
/* 23 diffs: scheduling of the 0x114-0x144 field stores around the vector copies and of the 0x190 store */
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;
extern Vec4 ZeroVector;
extern Vec4 All1Vector;
extern Vec4 ZUnitVector;
extern char InitialCollisionFinder[];
extern void CopyGeometryPointer(char *, int);
extern void func_000BFC68(char *, char *, int);
extern int func_000C5CC0(char *, char *, char *, char *);
extern int func_000C5D48(char *, char *);
extern void CopyCollisionFinder(char *, char *);

static void func_000C5A50(char *e, int g, int a2, int a3, int t0, char *d)
{
    char *s = (char *)*(int *)(d + 0xD4);
    int *v;

    *(int *)(e + 0xC0) = t0;
    *(int *)(e + 0xC4) = 1;
    CopyGeometryPointer(e + 0xD0, g);
    *(s128 *)(e + 0x0) = ZeroVector.q;
    func_000BFC68(e, d, 1);
    *(int *)(e + 0x110) = 0;
    *(s128 *)(e + 0x70) = All1Vector.q;
    *(s128 *)(e + 0x80) = All1Vector.q;
    *(s128 *)(e + 0x90) = ZUnitVector.q;
    *(int *)(e + 0x114) = 0;
    *(int *)(e + 0x118) = 0;
    *(int *)(e + 0x11C) = 0;
    *(int *)(e + 0x120) = 0;
    v = (int *)(e + 0x124);
    v[2] = 0;
    v[0] = 0;
    v[1] = 0;
    *(float *)(e + 0x144) = 1.0f;
    *(int *)(e + 0x130) = 0;
    *(int *)(e + 0x134) = 0;
    *(float *)(e + 0x138) = 1.0f;
    *(float *)(e + 0x13C) = 1.0f;
    *(float *)(e + 0x140) = 1.0f;
    *(int *)(e + 0x148) = func_000C5CC0(e + 0x14C, e, s, d);
    if (*(int *)(d + 0xCC) == 0 && func_000C5D48(e, s) == 0) {
        *(int *)(e + 0x114) = 1;
        *(int *)(e + 0xC4) = 0;
    }
    *(int *)(e + 0x15C) = a2;
    *(int *)(e + 0x160) = a3;
    *(int *)(e + 0x158) = 1;
    *(int *)(e + 0x168) = 1;
    *(int *)(e + 0x164) = 0;
    *(int *)(e + 0x16C) = 0;
    CopyCollisionFinder(e + 0x170, InitialCollisionFinder);
    *(int *)(e + 0x184) = 0;
    *(int *)(e + 0x188) = 0;
    *(int *)(e + 0x190) = 1;
    *(int *)(e + 0x18C) = *(int *)(d + 0xD8);
    *(int *)(e + 0x198) = 0;
    *(int *)(e + 0x194) = 0;
}
#endif
