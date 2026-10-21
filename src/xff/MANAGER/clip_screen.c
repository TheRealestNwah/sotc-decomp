typedef float ClipMatrix[4][4];

typedef struct ClipScreen {
    int width;
    int height;
    float aspect;
    float viewAngle;
    ClipMatrix clip;
    ClipMatrix clip128;
    ClipMatrix clip256;
    ClipMatrix clipFovIgnore;
    ClipMatrix screen;
    ClipMatrix screen128;
    ClipMatrix screen256;
    int scissorW[2];
    int scissorH[2];
    ClipMatrix scissorClip[2];
} ClipScreen;

typedef struct ClipScreenEntry {
    char pad0[0x8];
    unsigned long key;
    int unk10;
    int unk14;
} ClipScreenEntry;

extern int D_00139F44;
extern ClipScreenEntry **D_00139F48;
extern float D_00139F54;
extern float D_00139F58;
extern char D_00139F5C[];

extern void *iosMallocAlign(int heap, int size, int align);
extern void iosFree(void *p);
extern int getDispScreenWidth(void);
extern int getDispScreenHeight(void);
extern int getDrawScreenHeight(void);

extern float iosGetTanf(float x);
extern void iosUnitMatrix(void *m);

static float func_000E95C8(float angle, int height);
static void func_000E9640(ClipScreen *p, float dist);
static void func_000E9730(ClipScreen *p);
static void func_000E9780(ClipScreen *p, float dist);
static void func_000E9830(ClipMatrix m, float w, float h, float dist, float near, float far);
static void func_000E9930(ClipMatrix m, int w, int h);

static ClipScreenEntry *func_000E8FD0(ClipScreenEntry *p);
void set_screen_size(ClipScreen *p, int width, int height);
void set_view_angle(ClipScreen *p, float angle);
void set_scissor_screen_size(ClipScreen *p, int i, int width, int height);
void update_clip_screen(ClipScreen *p);

static ClipScreenEntry *func_000E8F50(int type, unsigned long key)
{
    int i;

    if (type == 1) {
        key &= 0x3F000000000UL;
        for (i = 0; i < D_00139F44; i++) {
            if (key == D_00139F48[i]->key) {
                return func_000E8FD0(D_00139F48[i]);
            }
        }
    }
    return 0;
}

static ClipScreenEntry *func_000E8FD0(ClipScreenEntry *p)
{
    if (p && p->unk14) {
        return p;
    }
    return 0;
}

ClipScreen *create_clip_screen(int heap, int width, int height, float angle)
{
    ClipScreen *p;
    int i;

    p = iosMallocAlign(heap, sizeof(ClipScreen), 0x10);
    set_screen_size(p, width, height);
    set_view_angle(p, angle);
    for (i = 0; i < 2; i++) {
        set_scissor_screen_size(p, i, width, height);
    }
    update_clip_screen(p);
    return p;
}

void check_free_clip_screen(ClipScreen **pp)
{
    if (*pp) {
        iosFree(*pp);
        *pp = 0;
    }
}

void set_screen_size(ClipScreen *p, int width, int height)
{
    float *scale;
    float h;
    int dispW;
    int dispH;
    int drawH;

    scale = &D_00139F58;
    p->width = width;
    p->height = height;
    h = height;
    p->aspect = (float)width / h / 0.90909f;
    dispW = getDispScreenWidth();
    dispH = getDispScreenHeight();
    drawH = getDrawScreenHeight();
    *scale = (float)p->width / dispW / (h / dispH) * drawH / 448.0f;
}

void set_screen_wide_and_progressive(int wide, int progressive)
{
    if (wide) {
        if (!progressive) {
            D_00139F54 = 1.3333333f;
        } else {
            D_00139F54 = 1.0f;
        }
    } else {
        if (!progressive) {
            D_00139F54 = 1.0f;
        } else {
            D_00139F54 = 0.75f;
        }
    }
}

void set_view_angle(ClipScreen *p, float angle)
{
    p->viewAngle = angle;
}

void set_scissor_screen_size(ClipScreen *p, int i, int width, int height)
{
    p->scissorW[i] = width;
    p->scissorH[i] = height;
}

int get_screen_width(ClipScreen *p)
{
    return p->width;
}

int get_screen_height(ClipScreen *p)
{
    return p->height;
}

float get_aspect_ratio(ClipScreen *p)
{
    return p->aspect * D_00139F54 / D_00139F58;
}

float get_view_angle(ClipScreen *p)
{
    return p->viewAngle;
}

float get_dist_from_eye_to_screen(ClipScreen *p)
{
    return func_000E95C8(p->viewAngle, p->height);
}

float get_near_clip_z_clip_screen(void)
{
    return 0.05f;
}

float get_far_clip_z_clip_screen(void)
{
    return 65535.0f;
}

float get_z_buf_min_clip_screen(void)
{
    return 255.0f;
}

float get_z_buf_max_clip_screen(void)
{
    return 16700000.0f;
}

void update_clip_screen(ClipScreen *p)
{
    float dist;

    dist = func_000E95C8(p->viewAngle, p->height);
    func_000E9640(p, dist);
    func_000E9730(p);
    func_000E9780(p, dist);
}

void *get_screen_size_scale_screen_matrix(void)
{
    return D_00139F5C;
}

static float func_000E95C8(float angle, int height)
{
    float t;

    t = iosGetTanf(angle * 0.5f * 0.017453293f);
    return (float)height * 0.5f / t / D_00139F54;
}

static void func_000E9640(ClipScreen *p, float dist)
{
    float w;
    float h;

    w = p->width;
    h = p->height;
    func_000E9830(p->clip, w, h, dist, 0.05f, 65535.0f);
    func_000E9830(p->clip128, 128.0f, 128.0f, dist, 0.05f, 65535.0f);
    func_000E9830(p->clip256, 256.0f, 256.0f, dist, 0.05f, 65535.0f);
    func_000E9830(p->clipFovIgnore, w, h, 500.0f, 0.05f, 65535.0f);
}

static void func_000E9730(ClipScreen *p)
{
    func_000E9930(p->screen, p->width, p->height);
    func_000E9930(p->screen128, 0x80, 0x80);
    func_000E9930(p->screen256, 0x100, 0x100);
}

static void func_000E9780(ClipScreen *p, float dist)
{
    int i;

    for (i = 0; i < 2; i++) {
        func_000E9830(p->scissorClip[i], p->scissorW[i], p->scissorH[i], dist, 0.05f, 65535.0f);
    }
}

static void func_000E9830(ClipMatrix m, float w, float h, float dist, float near, float far)
{
    float sx;
    float sy;

    sy = dist / (h * 0.5f) * D_00139F54 / 0.90909f / D_00139F58;
    sx = dist / (w * 0.5f);
    iosUnitMatrix(m);
    m[0][0] = sx;
    m[2][3] = 1.0f;
    m[3][3] = 0.0f;
    m[1][1] = sy;
    m[2][2] = (far + near) / (far - near);
    m[3][2] = far * near * -2.0f / (far - near);
}

static void func_000E9930(ClipMatrix m, int w, int h)
{
    float sx;
    float sy;

    sy = (float)h * 0.5f * *(float *)D_00139F5C;
    sx = (float)w * 0.5f * *(float *)D_00139F5C;
    iosUnitMatrix(m);
    m[0][0] = sx;
    m[1][1] = -sy;
    m[2][2] = -8349872.5f;
    m[3][2] = 8350127.5f;
    m[3][0] = 2048.0f;
    m[3][1] = 2048.0f;
    m[3][3] = 1.0f;
}
