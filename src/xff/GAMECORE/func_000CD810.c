/* Parked: 16 diffs, same size. Remaining: glBlendFunc loads a1=6 before a0=5;
 * second block schedules the RO_00180BC0 copy load after lw a3 and swaps the
 * sd 0x18/0x30 order; tail reaches gcGlobalVar through a1/v1 instead of v1/v0. */

#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));
typedef struct { short x, y, z; unsigned short flags; } Rec;
typedef struct { int head; int next; } Ring;
typedef union { s128 q; float f[4]; int w[4]; } V4;
typedef struct { char pad[0x168]; float time; int pad16C; float f170; } GcGlobal;
typedef struct {
    char pad0[0x18]; float scale; char pad1C[0x28 - 0x1C];
    float px, py, pz; char pad34[0x40 - 0x34];
    float sx, sy, ox, oy, ox2, oy2; int layer; float anim;
} Menu;

extern GcGlobal gcGlobalVar;
extern Ring D_0017B370;
extern void *D_0017B37C;
extern Rec B_0019CF50[];
extern const char RO_00180BB0[];
extern const V4 RO_00180BC0;
extern int texSearchMopByName(const char *);
extern void iosDlPushLayer(int);
extern void iosDlPopLayer(void);
extern void texTransRequest(int, int, int);
extern void gsRegBegin(void);
extern void gsReg(int, int);
extern void gsRegEnd(void);
extern void glDisable(int);
extern void glEnable(int);
extern void glBegin(int);
extern void glEnd(void);
extern void glBlendFunc(int, int);
extern void glColor4fv(float *);
extern void glTexCoord2f(float, float);
extern void glVertex2f(float, float);
extern void *memset(void *, int, unsigned int);
extern void texAnimationOne(int, float, float);

static inline void itof(V4 *out, V4 *in)
{
    if (in->w[0] & 0x8000)
        in->w[0] |= 0xFFFF0000;
    if (in->w[1] & 0x8000)
        in->w[1] |= 0xFFFF0000;
    if (in->w[2] & 0x8000)
        in->w[2] |= 0xFFFF0000;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)
"
        "vitof12.xz vf6, vf5
"
        "vitof4.y vf6, vf5
"
        "sqc2 vf6, 0x0(%0)
"
        : : "r"(out), "r"(in) : "memory");
}

static inline unsigned short brk(Rec *r)
{
    return r->flags & 1;
}

void func_000CD810(Menu *menu, int flag, float r, float g, float b, float a)
{
    float col[4];
    V4 iv;
    V4 fv;
    V4 c2;
    int tex;
    int i, n;
    float u, t, px, pz, x, y, d, e, x0, y0, x2, y2;

    i = D_0017B370.next;
    tex = texSearchMopByName(RO_00180BB0);
    u = gcGlobalVar.time * 0.2f;
    if (D_0017B370.next == D_0017B370.head)
        return;
    u = u - (float)(int)u;
    iosDlPushLayer(menu->layer + 1);
    texTransRequest(tex, 0, 0);
    gsRegBegin();
    gsReg(8, 0);
    gsRegEnd();
    glDisable(9);
    glDisable(1);
    if (flag != 0 && a == 1.0f)
        glEnable(7);
    else
        glDisable(7);
    glEnable(0);
    glEnable(3);
    glBegin(2);
    col[0] = r;
    col[1] = g;
    col[2] = b;
    col[3] = a;
    n = 0;
    glBlendFunc(5, 6);
    pz = 0.0f;
    glColor4fv(col);
    if (D_0017B37C == 0) {
        x0 = menu->scale * (menu->px * menu->sx * 0.1f);
        y0 = menu->scale * (-menu->pz * menu->sy * 0.1f + menu->py * -0.067f);
        glTexCoord2f(pz, u);
        glVertex2f(x0 + menu->ox + menu->ox2, y0 + menu->oy + menu->oy2);
    }
    i--;
    pz = -menu->pz;
    if (i < 0)
        i = 0x59F;
    px = menu->px;
    while (i != D_0017B370.head) {
        memset(&fv, 0, 0x10);
        fv.w[0] = B_0019CF50[i].x;
        fv.w[1] = B_0019CF50[i].y;
        fv.w[2] = B_0019CF50[i].z;
        iv = fv;
        e = col[3] - (D_0017B37C != 0 ? 0.00069444446f : 0.01f);
        col[3] = e;
        if (e < 0.0f)
            col[3] = 0.0f;
        glColor4fv(col);
        itof(&fv, &iv);
        x = menu->scale * (fv.f[0] * menu->sx * 0.1f);
        y = menu->scale * (fv.f[2] * menu->sy * 0.1f + fv.f[1] * -0.067f);
        d = px - fv.f[0];
        if (d < 0.0f)
            d = -d;
        e = pz - fv.f[2];
        u += (e < 0.0f) ? d - e : d + e;
        px = fv.f[0];
        pz = fv.f[2];
        glTexCoord2f(0.0f, u);
        glVertex2f(x + menu->ox + menu->ox2, y + menu->oy + menu->oy2);
        if (brk(&B_0019CF50[i])) {
            glEnd();
            glBegin(2);
        }
        i--;
        if (i < 0)
            i = 0x59F;
        if (!(++n < (D_0017B37C != 0 ? 0x5A1 : 0x65)))
            break;
        if (col[3] <= 0.0f)
            break;
    }
    glEnd();
    glDisable(7);
    glEnable(1);
    if (D_0017B37C != 0) {
        i = D_0017B370.next;
        i--;
        if (i < 0)
            i = 0x59F;
        glEnable(3);
        glBegin(7);
        memset(&fv, 0, 0x10);
        fv.w[0] = B_0019CF50[i].x;
        fv.w[1] = B_0019CF50[i].y;
        fv.w[2] = B_0019CF50[i].z;
        iv = fv;
        c2 = RO_00180BC0;
        itof(&fv, &iv);
        x2 = menu->scale * (fv.f[0] * menu->sx * 0.1f);
        y2 = menu->scale * (fv.f[2] * menu->sy * 0.1f + fv.f[1] * -0.067f);
        glColor4fv(c2.f);
        glVertex2f(x2 + menu->ox + menu->ox2 - 2.0f, y2 + menu->oy + menu->oy2 - 2.0f);
        glVertex2f(x2 + menu->ox + menu->ox2 + 2.0f, y2 + menu->oy + menu->oy2 + 2.0f);
        glEnd();
    }
    iosDlPopLayer();
    texAnimationOne(tex, menu->anim, gcGlobalVar.f170);
}
#endif
