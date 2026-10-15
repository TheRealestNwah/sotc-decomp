typedef struct Ptn Ptn;
extern Ptn rootPtn;
typedef struct { void *func; int a; int stack; int prio; void *arg; char pad[0x10]; int x, y; } LwsParam;
extern void *memset(void *, int, unsigned int);
extern void func_0001CA80();
extern void *CreateLwsDemoOrientManagerObj(Ptn *, int, LwsParam *);

void *StartLwsDemoManager(int x, int y, void *arg)
{
    LwsParam p;
    memset(&p, 0, 0x24);
    p.arg = arg;
    p.x = x;
    p.y = y;
    p.func = func_0001CA80;
    p.stack = 0x1000;
    p.prio = 4;
    return CreateLwsDemoOrientManagerObj(&rootPtn, 0, &p);
}
