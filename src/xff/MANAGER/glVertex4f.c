typedef struct { float x, y, z, w; char pad[0x30]; } Vert;
typedef union { struct { char pad[0x200]; Vert v[1]; } a; struct { char pad[0x41F0]; volatile int n; } b; } GlState;
extern GlState D_00130480;
static void func_000120C8(int);
static void func_000124A0(int);

void glVertex4f(float x, float y, float z, float w)
{
    func_000120C8(1);
    D_00130480.a.v[D_00130480.b.n].x = x;
    D_00130480.a.v[D_00130480.b.n].y = y;
    D_00130480.a.v[D_00130480.b.n].z = z;
    D_00130480.a.v[D_00130480.b.n].w = w;
    func_000124A0(D_00130480.b.n);
}
