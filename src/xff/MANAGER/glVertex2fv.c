typedef struct { float x, y, z; char pad[0x34]; } Vert;
typedef union { struct { char pad[0x200]; Vert v[1]; } a; struct { char pad[0x41F0]; volatile int n; } b; } GlState;
extern GlState D_00130480;
static void func_000120C8(int);
static void func_000124A0(int);

void glVertex2fv(float *p)
{
    func_000120C8(0);
    D_00130480.a.v[D_00130480.b.n].x = p[0];
    D_00130480.a.v[D_00130480.b.n].y = p[1];
    D_00130480.a.v[D_00130480.b.n].z = 3.40282347e+38f;
    func_000124A0(D_00130480.b.n);
}
