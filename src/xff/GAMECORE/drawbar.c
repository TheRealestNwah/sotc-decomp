typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

typedef struct {
    float x, y, w, h;
    Vec4 col0;
    Vec4 col1;
    char pad30[8];
    float max;
    int vert;
    float cur;
    float prev;
    float value;
    float shake;
    float speed;
    float flash;
} Bar;

typedef struct {
    char unknown000[0x180];
    float frameRate;
} GlobalVar;

extern GlobalVar gcGlobalVar;
typedef struct {
    float f[4];
} __attribute__((aligned(16))) Float4;

static const Float4 RO_0017D520 = { { 0.8f, 0.8f, 0.8f, 0.7f } };
extern void *memset(void *, int, unsigned int);
extern void iosDlPushLayer(int);
extern void iosDlPopLayer(void);
extern void glEnable(int);
extern void glDisable(int);
extern void glBegin(int);
extern void glEnd(void);
extern void glBlendFunc(int, int);
extern void glColor4fv(void *);
extern void glVertex2f(float, float);

static inline void vecSub(Vec4 *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void vecScale(Vec4 *dst, Vec4 *src, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyzw vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(src), "r"(s) : "memory");
}

static inline void vecScale3(Vec4 *dst, Vec4 *src, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(src), "r"(s) : "memory");
}

static inline void vecAdd(Vec4 *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

void drawbar(Bar *p, float alpha)
{
    Vec4 c;
    Vec4 c0;
    Vec4 lerp;
    Vec4 frame;
    Vec4 hl;
    float cur;
    float value;
    float bw;
    float bh;
    float prev;
    float now;
    float t;

    *(Float4 *)&frame = RO_0017D520;
    memset(&hl, 0, 0x10);
    value = p->value;
    cur = p->cur;
    hl.f[3] = 0.3f;
    if (value < cur) {
        float n = cur - p->speed * gcGlobalVar.frameRate * 30.0f;
        p->cur = n;
        if (n <= value) {
            p->cur = value;
            p->prev = value;
            p->speed = 0;
        }
    }
    hl.f[3] *= alpha;
    if (p->vert == 0) {
        bw = (value + p->shake) * p->w / p->max;
        if (bw < 0.0f)
            bw = 0.0f;
        bh = p->h;
    } else {
        bh = (value + p->shake) * p->h / p->max;
        bw = p->w;
        if (bh < 0.0f)
            bh = 0.0f;
    }
    c.q = p->col1.q;
    c.f[3] *= alpha * 0.7f;
    iosDlPushLayer(0x19);
    prev = p->prev / p->max;
    t = p->value / p->max;
    now = p->cur / p->max;
    vecSub(&lerp, &p->col1, &p->col0);
    vecScale(&lerp, &lerp, t);
    vecAdd(&lerp, &lerp, &p->col0);
    c0.q = p->col0.q;
    vecScale3(&c0, &c0, p->flash);
    vecScale3(&lerp, &lerp, p->flash);
    c0.f[3] *= alpha;
    lerp.f[3] *= alpha;
    glEnable(3);
    glBegin(7);
    glBlendFunc(5, 6);
    if (p->vert == 0) {
        glColor4fv(&c);
        glVertex2f(p->x + bw + 0.5f, p->y + 0.5f);
        glVertex2f(p->x + p->w * prev - 0.5f, p->y + bh - 0.5f);
        glBlendFunc(5, 1);
        glVertex2f(p->x + bw + 0.5f, p->y + 0.5f);
        glVertex2f(p->x + p->w * now - 0.5f, p->y + bh - 0.5f);
    } else {
        glColor4fv(&c);
        glVertex2f(p->x + 0.5f, p->y + p->h - p->h * prev + 0.5f);
        glVertex2f(p->x + p->w - 0.5f, p->y + p->h - bh - 0.5f);
        glBlendFunc(5, 1);
        glVertex2f(p->x + 0.5f, p->y + p->h - p->h * now + 0.5f);
        glVertex2f(p->x + p->w - 0.5f, p->y + p->h - bh - 0.5f);
    }
    glEnd();
    glBegin(5);
    glBlendFunc(5, 6);
    if (p->vert == 0) {
        glColor4fv(&c0);
        glVertex2f(p->x + 0.5f, p->y + 0.5f);
        glColor4fv(&lerp);
        glVertex2f(p->x + bw - 0.5f, p->y + 0.5f);
        glColor4fv(&c0);
        glVertex2f(p->x + 0.5f, p->y + bh - 0.5f);
        glColor4fv(&lerp);
        glVertex2f(p->x + bw - 0.5f, p->y + bh - 0.5f);
    } else {
        glColor4fv(&lerp);
        glVertex2f(p->x + 0.5f, p->y + p->h - bh + 0.5f);
        glColor4fv(&lerp);
        glVertex2f(p->x + bw - 0.5f, p->y + p->h - bh + 0.5f);
        glColor4fv(&c0);
        glVertex2f(p->x + 0.5f, p->y + p->h - 0.5f);
        glColor4fv(&c0);
        glVertex2f(p->x + bw - 0.5f, p->y + p->h - 0.5f);
    }
    glEnd();
    glBegin(7);
    glColor4fv(&hl);
    glVertex2f(p->x + bw + 0.5f, p->y + 0.5f);
    glVertex2f(p->x + p->w - 0.5f, p->y + p->h - 0.5f);
    glEnd();
    vecScale3(&frame, &frame, p->flash);
    c.q = frame.q;
    c.f[3] *= alpha;
    glBegin(2);
    glColor4fv(&c);
    glVertex2f(p->x, p->y);
    glVertex2f(p->x + p->w, p->y);
    glVertex2f(p->x + p->w, p->y + p->h);
    glVertex2f(p->x, p->y + p->h);
    glVertex2f(p->x, p->y);
    glEnd();
    glDisable(3);
    if (0.5f < alpha) {
        glEnable(7);
        glBegin(2);
        glColor4fv(&c);
        if (p->vert == 0) {
            glVertex2f(p->x + bw, p->y + 0.5f);
            glVertex2f(p->x + bw, p->y + p->h - 0.5f);
        } else {
            glVertex2f(p->x + 0.5f, p->y + p->h - bh + 0.5f);
            glVertex2f(p->x + bw - 0.5f, p->y + p->h - bh - 0.5f);
        }
        glEnd();
        glDisable(7);
    }
    if (1.0f < p->flash)
        p->flash *= 0.98f;
    else
        p->flash = 1.0f;
    iosDlPopLayer();
    if (p->shake != 0.0f)
        p->shake *= -0.8f;
}
