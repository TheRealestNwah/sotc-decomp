typedef int s128 __attribute__((mode(TI)));
typedef float Mtx[4][4] __attribute__((aligned(16)));

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
    Mtx m40;
    Mtx m80;
    Mtx mC0;
    Mtx m100;
    s128 pos;
    s128 dir;
    s128 up;
    s128 oldPos;
    s128 oldDir;
    s128 oldUp;
    Mtx view;
    Mtx clip;
    Mtx scissor0;
    Mtx scissor1;
    Mtx clip128;
    char pad2E0[0x360 - 0x2E0];
    Mtx clip256;
    char pad3A0[0x420 - 0x3A0];
    Mtx fovignore;
    Mtx screen;
    Mtx screenClip;
    Mtx screenClip128;
    Mtx screenClip256;
    Mtx screenFov;
    Mtx clipView;
    Mtx scissorView;
    Mtx m620;
    Mtx screenClipView;
} CamCtx;

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
