typedef int s128 __attribute__((mode(TI)));

typedef struct {
    short x, y, z;
    unsigned short flags;
} Rec;

typedef struct {
    int count;
    int next;
    int last;
} Ring;

extern char gcGlobalVar[];
extern float D_0017B390;
extern Ring D_0017B370;
extern Rec B_0019CF50[];
extern float getAreaSize(void);

typedef union {
    s128 q;
    float f[4];
    int w[4];
} V4;

static void func_000CDEB0(float *pos, int arg1)
{
    struct {
        V4 out;
        V4 in;
    } L __attribute__((aligned(16)));
    int flag = arg1 & 0xFFFF;
    float cur = *(float *)(gcGlobalVar + 0x178);
    float inv = 1.0f / getAreaSize();
    int idx;

    if (D_0017B390 == 0.0f)
        D_0017B390 = cur;
    if (flag == 0 && cur - D_0017B390 < 5.0f)
        return;
    L.in.f[0] = -pos[0] * inv;
    L.in.f[1] = pos[1];
    L.in.f[2] = pos[2] * inv;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)
"
                         "vftoi12.xz vf6, vf5
"
                         "vftoi4.y vf6, vf5
"
                         "sqc2 vf6, 0x0(%0)
"
                         : : "r"(&L.out), "r"(&L.in) : "memory");
    L.out.w[0] = (unsigned short)L.out.w[0];
    L.out.w[1] = (unsigned short)L.out.w[1];
    L.out.w[2] = (unsigned short)L.out.w[2];
    if (B_0019CF50[D_0017B370.last].x == L.out.w[0] && B_0019CF50[D_0017B370.last].y == L.out.w[1]
        && B_0019CF50[D_0017B370.last].z == L.out.w[2] && flag == 0)
        return;
    idx = D_0017B370.next;
    { Rec *p = &B_0019CF50[idx];
    p->x = L.out.w[0];
    B_0019CF50[idx].y = L.out.w[1];
    B_0019CF50[idx].z = L.out.w[2];
    D_0017B370.last = idx;
    D_0017B370.next = idx + 1;
    p->flags = (p->flags & 0xFFFE) | (flag & 1); }
    if (D_0017B370.next >= 0x5A0)
        D_0017B370.next = 0;
    if (D_0017B370.next == D_0017B370.count)
        D_0017B370.count++;
    D_0017B390 = cur;
}
