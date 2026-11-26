/* Camera objects: the layout object holding a camera's position, direction,
 * up direction, clip screen and transform matrix set. */

typedef int s128 __attribute__((mode(TI)));
typedef union {
    s128 q;
    float f[4];
    int i[4];
} Vec4;

typedef struct {
    char pad[8];
    unsigned char type;
} LayoutObj;

typedef struct {
    int pad0;
    int active;
    char pad8[0x3C - 0x8];
    int id;
} CamWork;

extern void *memset(void *, int, unsigned int);
extern char *_isysCreateObj(void *, int, int, int, void *, int);
extern void isysInitISYSLetterObj(void *);
extern void isysFlushISYSLetterObj(void *);
extern void InitLayoutObj(void *, void *);
extern int GetLayoutObjWorkSize(CamWork *);
extern int create_clip_screen(void *, void *, void *, float);
extern int create_transform_matrix_set(void *);
extern void check_free_clip_screen(void *);
extern void check_free_transform_matrix_set(void *);
extern void set_screen_size(void *, int, int);
extern void update_clip_screen(int);
extern void update_transform_matrix_set(int, void *, int);
extern void *get_WV_matrix(void *);
extern void iosUnitMatrix(void *);
extern void iosCopyMatrix(void *, void *);
extern void GetQuaternionFromMatrix(void *, void *);
extern int iosSetCameraMatrix();

void set_camera_position(char *dst, Vec4 *src);
void set_camera_direction(char *a0, Vec4 *a1);
void set_camera_up_direction(char *a0, Vec4 *a1);
void update_camera_obj(char *cam);
Vec4 *get_camera_position(char *cam);
Vec4 *get_camera_direction(char *cam);
Vec4 *get_camera_up_direction(char *cam);
char *get_camera_obj_layout_class(char *cam);
void *get_transform_matrix_set(char *cam);
int create_original_view_matrix(char *a, char *b, char *c, char *d);
static int func_000E7CA8(CamWork *w);
static void T_000E7CE8(void *obj);

static inline void vecScale(Vec4 *out, Vec4 *in, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyzw vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(in), "r"(s) : "memory");
}

static inline void vecCross(Vec4 *out, Vec4 *a, Vec4 *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vopmula.xyz ACC, vf5, vf6\n"
                         "vopmsub.xyz vf7, vf6, vf5\n"
                         "vsub.w vf7, vf7, vf7\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void vecNormalize(Vec4 *out, Vec4 *in)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(in) : "memory");
}

static inline void matInverse(void *dst, void *src)
{
    __asm__ __volatile__("lqc2 vf24, 0x30(%1)\n"
                         "vsubw.x vf25, vf0, vf0w\n"
                         "vmulx.xyz vf28, vf24, vf25x\n"
                         "vsub.w vf28, vf28, vf28\n"
                         "lq $8, 0x0(%1)\n"
                         "lq $9, 0x10(%1)\n"
                         "lq $10, 0x20(%1)\n"
                         "qmfc2.ni $11, vf0\n"
                         "pextlw $12, $9, $8\n"
                         "pextuw $13, $9, $8\n"
                         "pextlw $14, $11, $10\n"
                         "pextuw $15, $11, $10\n"
                         "pcpyld $8, $14, $12\n"
                         "pcpyud $9, $12, $14\n"
                         "pcpyld $10, $15, $13\n"
                         "pcpyud $11, $13, $15\n"
                         "qmtc2.ni $8, vf24\n"
                         "qmtc2.ni $9, vf25\n"
                         "qmtc2.ni $10, vf26\n"
                         "vmulax.xyzw ACC, vf24, vf28x\n"
                         "vmadday.xyzw ACC, vf25, vf28y\n"
                         "vmaddaz.xyzw ACC, vf26, vf28z\n"
                         "vmaddw.xyzw vf29, vf0, vf28w\n"
                         "vsub.w vf29, vf29, vf29\n"
                         "vadd.w vf29, vf29, vf0\n"
                         "sqc2 vf24, 0x0(%0)\n"
                         "sqc2 vf25, 0x10(%0)\n"
                         "sqc2 vf26, 0x20(%0)\n"
                         "sqc2 vf29, 0x30(%0)\n"
                         : : "r"(dst), "r"(src) : "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15", "memory");
}

static inline void matMul(void *dst, void *a, void *b)
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
                         : : "r"(dst), "r"(a), "r"(b) : "memory");
}

char *create_camera_obj(void *sys, void *a1, void *a2, float f)
{
    Vec4 pos;
    Vec4 dir;
    Vec4 up;
    char layout[0x80];
    char *obj;

    memset(&pos, 0, 0x10);
    pos.f[3] = 1.0f;
    memset(&dir, 0, 0x10);
    dir.f[2] = 1.0f;
    memset(&up, 0, 0x10);
    up.f[1] = 1.0f;
    obj = _isysCreateObj(sys, 0x11, 0x260, func_000E7CA8((CamWork *)layout), T_000E7CE8, 0x10);
    isysInitISYSLetterObj(obj);
    InitLayoutObj(obj, layout);
    set_camera_position(obj, &pos);
    set_camera_direction(obj, &dir);
    set_camera_up_direction(obj, &up);
    *(int *)(obj + 0x250) = create_clip_screen(sys, a1, a2, f);
    *(int *)(obj + 0x254) = create_transform_matrix_set(sys);
    update_camera_obj(obj);
    return obj;
}

/* Copies the camera into its layout class: position, orientation and the
 * world-view matrices. */
static void func_000E7930(char *cam)
{
    Vec4 m[4];
    char *lc;
    void *tm;
    Vec4 *pos;

    lc = get_camera_obj_layout_class(cam);
    tm = get_transform_matrix_set(cam);
    pos = get_camera_position(cam);
    (*(Vec4 **)(lc + 0x134))->q = pos->q;
    iosUnitMatrix(m);
    m[2].q = get_camera_direction(cam)->q;
    vecScale(&m[1], get_camera_up_direction(cam), -1.0f);
    vecCross(&m[0], &m[1], &m[2]);
    vecNormalize(&m[0], &m[0]);
    vecCross(&m[1], &m[2], &m[0]);
    GetQuaternionFromMatrix(*(void **)(lc + 0x13C), m);
    (*(Vec4 **)(lc + 0x154))->q = (*(Vec4 **)(lc + 0x13C))->q;
    iosCopyMatrix(*(void **)(lc + 0x168), *(void **)(lc + 0x164));
    iosCopyMatrix(*(void **)(lc + 0x164), get_WV_matrix(tm));
    matInverse(*(void **)(lc + 0x158), *(void **)(lc + 0x164));
    iosCopyMatrix(*(void **)(lc + 0x15C), *(void **)(lc + 0x158));
    matMul(*(void **)(lc + 0x16C), *(void **)(lc + 0x158), *(void **)(lc + 0x168));
}

void set_camera_obj_screen_size(char *camera, int width, int height)
{
    set_screen_size(*(void **)(camera + 0x250), width, height);
}

LayoutObj *dynamic_cast_to_camera_obj(LayoutObj *p)
{
    if (p->type != 0x11) {
        __asm__ __volatile__("break 0");
        return 0;
    }
    return p;
}

void update_camera_obj(char *cam)
{
    create_original_view_matrix(cam + 0x210, cam + 0x1E0, cam + 0x1F0, cam + 0x200);
    update_clip_screen(*(int *)(cam + 0x250));
    update_transform_matrix_set(*(int *)(cam + 0x254), cam, *(int *)(cam + 0x250));
    func_000E7930(cam);
}

void set_camera_position(char *dst, Vec4 *src)
{
    *(s128 *)(dst + 0x1E0) = src->q;
}

void set_camera_direction(char *a0, Vec4 *a1)
{
    __asm__ __volatile__(".set noreorder\n"
        "lqc2 vf5, 0x0(%0)\n"
        "vmul.xyz vf7, vf5, vf5\n"
        "vmulax.w ACC, vf0, vf7x\n"
        "vmadday.w ACC, vf0, vf7y\n"
        "vmaddz.w vf7, vf0, vf7z\n"
        "vrsqrt Q, vf0w, vf7w\n"
        "vwaitq\n"
        "vmulq.xyz vf5, vf5, Q\n"
        "sqc2 vf5, 0x0(%1)\n"
        ".set reorder\n"
        : : "r"(a1), "r"((char *)a0 + 0x1F0) : "memory");
}

void set_camera_up_direction(char *a0, Vec4 *a1)
{
    __asm__ __volatile__(".set noreorder\n"
        "lqc2 vf5, 0x0(%0)\n"
        "vmul.xyz vf7, vf5, vf5\n"
        "vmulax.w ACC, vf0, vf7x\n"
        "vmadday.w ACC, vf0, vf7y\n"
        "vmaddz.w vf7, vf0, vf7z\n"
        "vrsqrt Q, vf0w, vf7w\n"
        "vwaitq\n"
        "vmulq.xyz vf5, vf5, Q\n"
        "sqc2 vf5, 0x0(%1)\n"
        ".set reorder\n"
        : : "r"(a1), "r"((char *)a0 + 0x200) : "memory");
}

Vec4 *get_camera_position(char *cam)
{
    return (Vec4 *)(cam + 0x1E0);
}

Vec4 *get_camera_direction(char *cam)
{
    return (Vec4 *)(cam + 0x1F0);
}

Vec4 *get_camera_up_direction(char *cam)
{
    return (Vec4 *)(cam + 0x200);
}

char *get_camera_obj_layout_class(char *cam)
{
    return cam + 0x20;
}

void *get_clip_screen(char *cam)
{
    return *(void **)(cam + 0x250);
}

void *get_transform_matrix_set(char *cam)
{
    return *(void **)(cam + 0x254);
}

int create_original_view_matrix(char *a, char *b, char *c, char *d)
{
    return iosSetCameraMatrix(a, b, c, d);
}

static int func_000E7CA8(CamWork *w)
{
    memset(w, 0, 0x7C);
    w->active = 1;
    w->id = -1;
    return GetLayoutObjWorkSize(w);
}

/* Delete callback of a camera object. */
static void T_000E7CE8(void *obj)
{
    char *cam = (char *)dynamic_cast_to_camera_obj(obj);

    if (cam) {
        isysFlushISYSLetterObj(cam);
        check_free_clip_screen(cam + 0x250);
        check_free_transform_matrix_set(cam + 0x254);
    }
}
