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

#ifdef NONMATCHING /* 64 diffs: the first 0xB4 bytes (VU0 ftoi block, frame layout, flag handling) match; the ring-buffer tail differs in how the global table addresses are hoisted */
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
    Rec *r;
    int idx;
    unsigned short a, b, c;

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
    a = L.out.w[0];
    b = L.out.w[1];
    c = L.out.w[2];
    L.out.w[0] = a;
    L.out.w[1] = b;
    L.out.w[2] = c;
    r = &B_0019CF50[D_0017B370.last];
    if (r->x == a && r->y == b && r->z == c && flag == 0)
        return;
    idx = D_0017B370.next;
    B_0019CF50[idx].x = L.out.w[0];
    B_0019CF50[idx].y = L.out.w[1];
    B_0019CF50[idx].z = L.out.w[2];
    D_0017B370.last = idx;
    D_0017B370.next = idx + 1;
    B_0019CF50[idx].flags = (B_0019CF50[idx].flags & 0xFFFE) | (flag & 1);
    if (D_0017B370.next >= 0x5A0)
        D_0017B370.next = 0;
    if (D_0017B370.next == D_0017B370.count)
        D_0017B370.count++;
    D_0017B390 = cur;
}
#endif
