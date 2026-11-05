typedef struct {
    float f[4];
} __attribute__((aligned(16))) Vec4;

typedef struct {
    float m[4][4];
} __attribute__((aligned(16))) Mat4;

extern void *memset(void *, int, unsigned int);
extern char *get_cur_using_lws_anime_mode_base_class(void *);
extern void doit_double_spring_interp_cntrl3D(void *, void *, int, float);
extern int GAMEUTIL_is_nearly_equal_zero3D(void *, float);
extern int CAM_get_camera_space_axisXY(int, void *, void *, float);
extern void iosRotMatrixAxis(void *, void *, int, float);
extern void iosApplyRotMatrix(void *, void *, void *);
extern int GAMEUTIL_get_yaw_pitch_by_direction(float *, float *, void *);
extern float GAMEUTIL_increase_pitch(int, int, float, float, float, float);
extern void GAMEUTIL_get_direction_by_yaw_pitch(void *, float, float);

typedef struct {
    Vec4 pos;
    Vec4 at;
    Vec4 dir;
    float yaw;
    float pitch;
    float dist;
} CamPos;

#define DEG 0.0174532924f

static inline void scaleVecXYZ(void *out, void *in, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(in), "r"(s) : "memory");
}

static inline void addVecXYZ(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static void func_000D80A0(char *self, char *c, void *mode, int unused, float t)
{
    Vec4 tgt;
    Vec4 axis;
    Vec4 dir;
    Mat4 m;
    float yaw;
    float pitch;
    char *base;
    int p;
    int r;
    float x;
    CamPos *cp;

    memset(&tgt, 0, 0x10);
    p = 0;
    base = get_cur_using_lws_anime_mode_base_class(mode);
    if (base != 0) {
        p = *(int *)(base + 0x98);
        if (p == 0) {
            x = *(float *)(c + 0xC);
            if (0.0f < x) {
                tgt.f[0] = x * (*(float *)(base + 0xA4) * DEG);
            } else if (x < 0.0f) {
                tgt.f[0] = -x * (*(float *)(base + 0xA8) * DEG);
            }
            x = *(float *)(c + 0x10);
            if (0.0f < x) {
                tgt.f[1] = -x * (*(float *)(base + 0xAC) * DEG);
            } else if (x < 0.0f) {
                tgt.f[1] = x * (*(float *)(base + 0xB0) * DEG);
            }
        }
    }
    doit_double_spring_interp_cntrl3D(self + 0x10, &tgt, p, t);
    if (GAMEUTIL_is_nearly_equal_zero3D(self + 0x40, 0.0001f)) {
        return;
    }
    r = CAM_get_camera_space_axisXY(0, &axis, c + 0x140, 0.0f);
    cp = (CamPos *)(c + 0x120);
    if (r != 1) {
        return;
    }
    iosRotMatrixAxis(&m, &axis, 1, *(float *)(self + 0x40));
    iosApplyRotMatrix(&dir, &m, &cp->dir);
    if (GAMEUTIL_get_yaw_pitch_by_direction(&yaw, &pitch, &dir) != r) {
        return;
    }
    cp->yaw = yaw;
    cp->pitch = GAMEUTIL_increase_pitch(0, 0, pitch, *(float *)(self + 0x44), 1.48352980613708496093750f, -1.48352980613708496093750f);
    GAMEUTIL_get_direction_by_yaw_pitch(&cp->dir, cp->yaw, cp->pitch);
    scaleVecXYZ(&dir, &cp->dir, cp->dist);
    addVecXYZ(&cp->at, &cp->pos, &dir);
}
