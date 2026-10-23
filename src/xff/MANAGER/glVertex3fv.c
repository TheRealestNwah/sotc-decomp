typedef int s128 __attribute__((mode(TI)));
typedef struct { s128 q; char pad[0x30]; } Vert;
typedef union { struct { char pad[0x200]; Vert v[1]; } a; struct { char pad[0x41F0]; volatile int n; } b; } GlState;
extern GlState D_00130480;
static void func_000120C8(int);
static void func_000124A0(int);

void glVertex3fv(float *p)
{
    func_000120C8(1);
    (D_00130480.a.v + D_00130480.b.n)->q = *(s128 *)p;
    func_000124A0(D_00130480.b.n);
}
