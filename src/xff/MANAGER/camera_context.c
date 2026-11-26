/* Camera context: the stack of view contexts and the matrices each one
 * caches from its camera and clip screen. */

typedef struct { float x, y, z, w; } __attribute__((aligned(8))) Vec4;
typedef float Mtx[4][4];
typedef int s128 __attribute__((mode(TI)));
typedef float AMtx[4][4] __attribute__((aligned(16)));
typedef float Vector[4] __attribute__((aligned(16)));


typedef struct {
    char pad0[0x10];
    float f10;
    float f14;
    float f18;
    float f1C;
    float f20;
    float f24;
    float f28;
    float f2C;
    float f30;
    char pad34[0x40 - 0x34];
    Mtx m40;
    Mtx m80;
    Mtx mC0;
    Mtx m100;
} VS;

typedef struct {
    int width;
    int height;
    float aspect;
    float dist;
    char pad10[0x24 - 0x10];
    float zmin;
    float zmax;
    float nearz;
    float farz;
    char pad34[0x40 - 0x34];
    AMtx m40;
    AMtx m80;
    AMtx mC0;
    AMtx m100;
    s128 pos;
    s128 dir;
    s128 up;
    s128 oldPos;
    s128 oldDir;
    s128 oldUp;
    AMtx view;
    AMtx clip;
    AMtx scissor0;
    AMtx scissor1;
    AMtx clip128;
    char pad2E0[0x360 - 0x2E0];
    AMtx clip256;
    char pad3A0[0x420 - 0x3A0];
    AMtx fovignore;
    AMtx screen;
    AMtx screenClip;
    AMtx screenClip128;
    AMtx screenClip256;
    AMtx screenFov;
    AMtx clipView;
    AMtx scissorView;
    AMtx m620;
    AMtx screenClipView;
} CamCtx;

typedef struct {
    char pad0[8];
    float far;
    float near;
    float vs10;
    float vs14;
    float vs18;
} ViewScreen;

typedef struct {
    int width;
    int height;
    float aspect;
    int pad0C;
    float dist;
    int pad14[2];
    float unk1C;
    float unk20;
    float unk24;
    float far;
    float near;
    float unk30;
} ViewContext;

typedef union {
    unsigned short h[2];
    int i;
} DCSize;

typedef struct {
    char pad[0x168];
    DCSize size;
} DC;

extern int getDrawScreenWidth(void);
extern int getDrawScreenHeight(void);
extern void iosUnitMatrix(Mtx);
extern int get_clip_screen(void *);
extern s128 *get_camera_position(void *);
extern s128 *get_camera_direction(void *);
extern s128 *get_camera_up_direction(void *);
extern float (*get_view_matrix(void *))[4];
extern float (*get_clip_matrix(int))[4];
extern float (*get_clip_matrix128(int))[4];
extern float (*get_clip_matrix256(int))[4];
extern float (*get_clip_matrix_fovignore(int))[4];
extern float (*get_screen_matrix(int))[4];
extern float (*get_screen_matrix128(int))[4];
extern float (*get_screen_matrix256(int))[4];
extern float (*get_scissor_clip_matrix(int, int))[4];
extern int get_screen_width(int);
extern int get_screen_height(int);
extern float get_dist_from_eye_to_screen(int);
extern float get_z_buf_min_clip_screen(int);
extern float get_z_buf_max_clip_screen(int);
extern float get_near_clip_z_clip_screen(int);
extern float get_far_clip_z_clip_screen(int);
extern void iosCopyMatrix(void *, void *);

extern char rootPtn[];
extern void *iosMallocAlign(void *, int, int);
extern void iosFree(void *);
extern DC *iosGetCurrentDC(void);
extern char B_0015D530[];
extern void *B_0015D4B0[];
extern int D_00139F3C;

void constructor_camera_context(ViewContext *v);

static inline void mulMatrix(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf14, 0x0(%1)\n"
                         "lqc2 vf15, 0x10(%1)\n"
                         "lqc2 vf16, 0x20(%1)\n"
                         "lqc2 vf17, 0x30(%1)\n"
                         "lqc2 vf24, 0x0(%2)\n"
                         "lqc2 vf25, 0x10(%2)\n"
                         "lqc2 vf26, 0x20(%2)\n"
                         "lqc2 vf27, 0x30(%2)\n"
                         "vmulax.xyzw ACC, vf14, vf24x\n"
                         "vmadday.xyzw ACC, vf15, vf24y\n"
                         "vmaddaz.xyzw ACC, vf16, vf24z\n"
                         "vmaddw.xyzw vf24, vf17, vf24w\n"
                         "vmulax.xyzw ACC, vf14, vf25x\n"
                         "vmadday.xyzw ACC, vf15, vf25y\n"
                         "vmaddaz.xyzw ACC, vf16, vf25z\n"
                         "vmaddw.xyzw vf25, vf17, vf25w\n"
                         "vmulax.xyzw ACC, vf14, vf26x\n"
                         "vmadday.xyzw ACC, vf15, vf26y\n"
                         "vmaddaz.xyzw ACC, vf16, vf26z\n"
                         "vmaddw.xyzw vf26, vf17, vf26w\n"
                         "vmulax.xyzw ACC, vf14, vf27x\n"
                         "vmadday.xyzw ACC, vf15, vf27y\n"
                         "vmaddaz.xyzw ACC, vf16, vf27z\n"
                         "vmaddw.xyzw vf27, vf17, vf27w\n"
                         "sqc2 vf24, 0x0(%0)\n"
                         "sqc2 vf25, 0x10(%0)\n"
                         "sqc2 vf26, 0x20(%0)\n"
                         "sqc2 vf27, 0x30(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void transform(Vector out, void *matrix, Vector v)
{
    __asm__ __volatile__(".set noreorder\n"
                         "lqc2 vf8, 0(%2)\n"
                         "lqc2 vf14, 0(%0)\n"
                         "lqc2 vf15, 0x10(%0)\n"
                         "lqc2 vf16, 0x20(%0)\n"
                         "lqc2 vf17, 0x30(%0)\n"
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf17, vf8w\n"
                         "sqc2 vf10, 0(%1)\n"
                         ".set reorder\n"
                         : : "r"(matrix), "r"(out), "r"(v)
                         : "memory");
}
#define ABS(x) ((x) < 0.0f ? -(x) : (x))

static inline void setDefaultViewContext(ViewContext *v, int width, int height)
{
    v->width = width;
    v->height = height;
    v->aspect = 0.94f;
    v->dist = 500.0f;
    v->unk1C = 2048.0f;
    v->unk20 = 2048.0f;
    v->unk24 = 0.25f;
    v->far = 16770000.0f;
    v->near = 0.05f;
    v->unk30 = 65536.0f;
}

void toggleDebPcWinWindow(void)
{

}

static void func_000E4F38(VS *vs)
{
    Vec4 half = { getDrawScreenWidth() >> 1, getDrawScreenHeight() >> 1, 0, 0 };
    Vec4 full = { 512.0f, 512.0f, 0, 0 };
    Mtx t;
    float tz, tw;
    float sx, sy;

    tw = (-vs->f28 * vs->f2C + vs->f24 * vs->f30) / (vs->f30 - vs->f2C);
    tz = vs->f30 * vs->f2C * (vs->f28 - vs->f24) / (vs->f30 - vs->f2C);
    iosUnitMatrix(vs->mC0);
    vs->mC0[0][0] = vs->f10;
    vs->mC0[2][2] = 0;
    vs->mC0[3][3] = 0;
    vs->mC0[3][2] = 1.0f;
    vs->mC0[2][3] = 1.0f;
    vs->mC0[1][1] = -vs->f10;
    iosUnitMatrix(t);
    t[0][0] = vs->f14;
    t[1][1] = vs->f18;
    t[3][0] = vs->f1C;
    t[3][1] = vs->f20;
    t[2][2] = tz;
    t[3][2] = tw;
    mulMatrix(vs->mC0, t, vs->mC0);

    sx = vs->f2C * half.x / vs->f10;
    sy = vs->f2C * half.y / vs->f10;
    iosUnitMatrix(vs->m40);
    vs->m40[0][0] = vs->f2C / sx;
    vs->m40[2][3] = 1.0f;
    vs->m40[1][1] = vs->f2C / sy;
    vs->m40[3][3] = 0;
    vs->m40[2][2] = (vs->f30 + vs->f2C) / (vs->f30 - vs->f2C);
    vs->m40[3][2] = vs->f30 * vs->f2C * -2.0f / (vs->f30 - vs->f2C);

    iosUnitMatrix(vs->m80);
    vs->m80[0][0] = vs->f10 * vs->f14 * sx / vs->f2C;
    vs->m80[3][3] = 1.0f;
    vs->m80[3][0] = vs->f1C;
    vs->m80[3][1] = vs->f20;
    vs->m80[2][2] = (vs->f24 - vs->f28) * 0.5f;
    vs->m80[3][2] = (vs->f28 + vs->f24) * 0.5f;
    vs->m80[1][1] = -vs->f10 * vs->f18 * sy / vs->f2C;

    sx = vs->f2C * full.x / vs->f10;
    sy = vs->f2C * full.y / vs->f10;
    iosUnitMatrix(vs->m100);
    vs->m100[0][0] = vs->f2C / sx;
    vs->m100[2][3] = 1.0f;
    vs->m100[1][1] = vs->f2C / sy;
    vs->m100[3][3] = 0;
    vs->m100[2][2] = (vs->f30 + vs->f2C) / (vs->f30 - vs->f2C);
    vs->m100[3][2] = vs->f30 * vs->f2C * -2.0f / (vs->f30 - vs->f2C);
}

void update_camera_context(CamCtx *c, void *cam)
{
    int scr = get_clip_screen(cam);
    int w, h;
    float dist, zmin, zmax, nearz, farz;

    c->oldPos = c->pos;
    c->pos = *get_camera_position(cam);
    c->oldDir = c->dir;
    c->dir = *get_camera_direction(cam);
    c->oldUp = c->up;
    c->up = *get_camera_up_direction(cam);
    iosCopyMatrix(c->view, get_view_matrix(cam));
    iosCopyMatrix(c->clip, get_clip_matrix(scr));
    iosCopyMatrix(c->clip128, get_clip_matrix128(scr));
    iosCopyMatrix(c->clip256, get_clip_matrix256(scr));
    iosCopyMatrix(c->fovignore, get_clip_matrix_fovignore(scr));
    iosCopyMatrix(c->screen, get_screen_matrix(scr));
    mulMatrix(c->screenClip, c->screen, c->clip);
    mulMatrix(c->screenClip128, get_screen_matrix128(scr), c->clip);
    mulMatrix(c->screenClip256, get_screen_matrix256(scr), c->clip);
    mulMatrix(c->screenFov, get_screen_matrix(scr), c->fovignore);
    mulMatrix(c->clipView, c->clip, c->view);
    mulMatrix(c->screenClipView, c->screen, c->clipView);
    iosCopyMatrix(c->scissor0, get_scissor_clip_matrix(scr, 0));
    iosCopyMatrix(c->scissor1, get_scissor_clip_matrix(scr, 1));
    mulMatrix(c->scissorView, c->scissor0, c->view);
    iosCopyMatrix(c->m40, c->clip);
    iosCopyMatrix(c->m100, c->scissor0);
    iosCopyMatrix(c->m80, c->screen);
    iosCopyMatrix(c->mC0, c->screenClip);
    w = get_screen_width(scr);
    h = get_screen_height(scr);
    dist = get_dist_from_eye_to_screen(scr);
    zmin = get_z_buf_min_clip_screen(scr);
    zmax = get_z_buf_max_clip_screen(scr);
    nearz = get_near_clip_z_clip_screen(scr);
    farz = get_far_clip_z_clip_screen(scr);
    c->width = w;
    c->farz = farz;
    c->dist = dist;
    c->zmin = zmin;
    c->zmax = zmax;
    c->nearz = nearz;
    c->height = h;
    c->aspect = (float)w / (float)h;
}

static inline float cameraZ(char *camera, Vector position)
{
    Vector unused;
    Vector out;
    transform(out, camera + 0x1A0, position);
    return out[2];
}
#define ABS(x) ((x) < 0.0f ? -(x) : (x))
float GetScreenRadius(char *camera, Vector position, float radius)
{
    float depth = ABS(cameraZ(camera, position));
    Vector out;
    Vector v = {radius, 0.0f, depth, 1.0f};
    transform(out, camera + 0xC0, v);
    return out[0] / out[3] - 2048.0f;
}

void SetVSMatrix(ViewScreen *vs)
{
    vs->vs10 = vs->near;
    vs->vs14 = 1.0f;
    vs->vs18 = vs->far;
    func_000E4F38((VS *)vs);
}

void SetDefaultViewContext(ViewContext *v, int width, int height)
{
    v->width = width;
    v->height = height;
    v->aspect = 0.94f;
    v->dist = 500.0f;
    v->unk1C = 2048.0f;
    v->unk20 = 2048.0f;
    v->unk24 = 0.25f;
    v->far = 16770000.0f;
    v->near = 0.05f;
    v->unk30 = 65536.0f;
}

void SetViewContext(void *arg0, int arg1, int arg2, float fparg0, float fparg1, float fparg2, float fparg3, float fparg4)
{
    (*(float *)((char *)(arg0) + 0x30)) = fparg4;
    (*(float *)((char *)(arg0) + 0xC)) = fparg0;
    (*(float *)((char *)(arg0) + 0x24)) = fparg1;
    (*(float *)((char *)(arg0) + 0x28)) = fparg2;
    (*(float *)((char *)(arg0) + 0x2C)) = fparg3;
    (*(int *)((char *)(arg0) + 0)) = arg1;
    (*(int *)((char *)(arg0) + 4)) = arg2;
    (*(float *)((char *)(arg0) + 8)) = (float) ((float) arg1 / (float) arg2);
}

void *create_camera_context(void)
{
    void *c = iosMallocAlign(rootPtn, 0x6A0, 0x10);
    constructor_camera_context(c);
    return c;
}

void release_camera_context(void *p)
{
    if (p != 0) {
        iosFree(p);
    }
}

void constructor_camera_context(ViewContext *v)
{
    DC *dc = iosGetCurrentDC();
    setDefaultViewContext(v, dc->size.h[0], dc->size.h[1]);
}

float GetScreenRadiusParticle(void *camera, float z, float x)
{
    float out[4] __attribute__((aligned(16)));
    float v[4] __attribute__((aligned(16))) = { x, 0.0f, z, 1.0f };

    __asm__ __volatile__(".set noreorder\n"
                         "lqc2 vf8, 0(%2)\n"
                         "lqc2 vf14, 0(%0)\n"
                         "lqc2 vf15, 0x10(%0)\n"
                         "lqc2 vf16, 0x20(%0)\n"
                         "lqc2 vf17, 0x30(%0)\n"
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf17, vf8w\n"
                         "sqc2 vf10, 0(%1)\n"
                         ".set reorder\n"
                         : : "r"((char *)camera + 0xC0), "r"(out), "r"(v)
                         : "memory");
    return out[0] / out[3] - 2048.0f;
}

void init_camera_context_manager(void)
{
    char *c = B_0015D530;
    constructor_camera_context((ViewContext *)c);
    D_00139F3C = 0;
    B_0015D4B0[0] = c;
}

void push_camera_context(void *m)
{
    if (D_00139F3C < 31) {
        D_00139F3C++;
        B_0015D4B0[D_00139F3C] = m;
        SetVSMatrix(m);
    }
}

void pop_camera_context(void)
{
    if (D_00139F3C > 0) {
        D_00139F3C--;
        SetVSMatrix(B_0015D4B0[D_00139F3C]);
    }
}
