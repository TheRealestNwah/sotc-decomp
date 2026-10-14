typedef struct { int a; int b; char finder[0x14]; int c; } VuColiDisp;
extern VuColiDisp B_00183B30;
extern char rootPtn[];
extern void InitCollisionFinder(void *, void *, int);

void initVuColiDispWork(int a)
{
    B_00183B30.a = a;
    B_00183B30.b = 2;
    B_00183B30.c = 0;
    InitCollisionFinder(B_00183B30.finder, rootPtn, 0x400);
}
