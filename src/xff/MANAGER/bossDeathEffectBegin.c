typedef unsigned long u64;

typedef struct {
    int psm;
    int fbp;
    int tbp;
    int tw;
    int th;
    int w;
    int h;
} Fb;

typedef struct {
    Fb fb[6];
} FbTbl;

extern int getDrawScreenWidth(void);
extern int getDrawScreenHeight(void);
extern int getDrawBufferAddressFBP(void);
extern int getDrawBufferAddressTBP(void);
extern int getFrameBufferSize(void);
extern int getFrameBufferSizeFBP(void);
extern void iosDlPushLayer(int);
extern void iosDlPopLayer(void);
extern void texResetVRAMRequest(int);
extern void gsRegBegin(void);
extern void gsRegEnd(void);
extern void gsReg(int, u64);
extern void *memset(void *, int, unsigned int);
extern void spriteNoTexFast(int, int, int, int, int, int *, int);
extern void glDisable(int);
extern void glEnable(int);
extern void glBegin(int);
extern void glEnd(void);
extern void glColor4fv(float *);
extern void glVertex2f(float, float);
extern float iosGetSinf(float);
extern float iosGetCosf(float);

extern int D_00130370[];
extern int D_00130380;
extern float D_00130388;
extern float D_0013038C;
extern float B_00147300[];

typedef struct { int x, y, w, h; } __attribute__((aligned(16))) Rect;
static const Rect D_0013C8D0 = {-0x800, -0x800, 0x1000, 0x1000};

static inline u64 gsFrame(int fbp, int w, int psm)
{
    return (u64)fbp | ((u64)((w >> 6) & 0x3F) << 16) | ((u64)(psm & 0xF) << 24);
}

static inline u64 gsFrameSize(int size, int w)
{
    return gsFrame(size >> 11, w, 0);
}

static inline u64 gsXyoffset(int w, int h)
{
    return (u64)((0x800 - w / 2) << 4) | ((u64)((0x800 - h / 2) << 4) << 32);
}

static inline u64 gsScissor(int w, int h)
{
    return ((u64)(w - 1) << 16) | ((u64)(h - 1) << 48);
}

static inline void drawFull(Fb *fb, int *col)
{
    gsReg(0x4C, gsFrame(fb->fbp, fb->w, fb->psm));
    gsReg(0x18, gsXyoffset(fb->w, fb->h));
    gsReg(0x40, gsScissor(fb->w, fb->h));
    if (col != 0)
        spriteNoTexFast(-fb->w * 8, -fb->h * 8, fb->w * 16, fb->h * 16, 0xFFFFFF, col, 0);
}

void bossDeathEffectBegin(float dt)
{
    FbTbl tbl;
    union {
        FbTbl t;
        struct { Rect rect; int col[4]; } r;
        struct { float c0[4]; float c1[4]; } c;
    } w;
    int i;
    float cx;
    float cy;
    float a;
    float s;

    w.t.fb[0].psm = 0;
    w.t.fb[0].fbp = getDrawBufferAddressFBP();
    w.t.fb[0].tbp = getDrawBufferAddressTBP();
    w.t.fb[0].tw = 9;
    w.t.fb[0].th = 9;
    w.t.fb[0].w = getDrawScreenWidth();
    w.t.fb[0].h = getDrawScreenHeight();
    w.t.fb[1].psm = 0;
    w.t.fb[1].fbp = getFrameBufferSize() >> 11;
    w.t.fb[1].tbp = getFrameBufferSize() >> 6;
    w.t.fb[1].tw = 9;
    w.t.fb[1].th = 9;
    w.t.fb[1].w = getDrawScreenWidth();
    w.t.fb[1].h = getDrawScreenHeight();
    w.t.fb[2].psm = 0;
    w.t.fb[2].fbp = (getFrameBufferSize() >> 11) + ((getDrawScreenWidth() * getDrawScreenHeight()) >> 11);
    w.t.fb[2].tbp = (getFrameBufferSize() >> 6) + ((getDrawScreenWidth() * getDrawScreenHeight()) >> 6);
    w.t.fb[2].tw = 8;
    w.t.fb[2].th = 8;
    w.t.fb[2].w = 0x100;
    w.t.fb[2].h = 0x100;
    w.t.fb[3].psm = 0;
    w.t.fb[3].fbp = (getFrameBufferSize() >> 11) + ((getDrawScreenWidth() * getDrawScreenHeight()) >> 11) + 0x20;
    w.t.fb[3].tbp = (getFrameBufferSize() >> 6) + ((getDrawScreenWidth() * getDrawScreenHeight()) >> 6) + 0x400;
    w.t.fb[3].tw = 7;
    w.t.fb[3].th = 7;
    w.t.fb[3].w = 0x80;
    w.t.fb[3].h = 0x80;
    w.t.fb[4].psm = 0;
    w.t.fb[4].fbp = (getFrameBufferSize() >> 11) + ((getDrawScreenWidth() * getDrawScreenHeight()) >> 11) + 0x28;
    w.t.fb[4].tbp = (getFrameBufferSize() >> 6) + ((getDrawScreenWidth() * getDrawScreenHeight()) >> 6) + 0x500;
    w.t.fb[4].tw = 6;
    w.t.fb[4].th = 6;
    w.t.fb[4].w = 0x40;
    w.t.fb[4].h = 0x40;
    w.t.fb[5].psm = 0;
    w.t.fb[5].fbp = (getFrameBufferSize() >> 11) + ((getDrawScreenWidth() * getDrawScreenHeight()) >> 11) + 0x2A;
    w.t.fb[5].tbp = (getFrameBufferSize() >> 6) + ((getDrawScreenWidth() * getDrawScreenHeight()) >> 6) + 0x540;
    w.t.fb[5].tw = 6;
    w.t.fb[5].th = 6;
    w.t.fb[5].w = 0x40;
    w.t.fb[5].h = 0x40;
    tbl = w.t;
    if (D_00130380 == 0)
        return;
    iosDlPushLayer(8);
    texResetVRAMRequest((getDrawScreenWidth() * getDrawScreenHeight() + 0x15000) >> 6);
    if (D_00130380 & 1) {
        if (dt > 0.0f)
            D_00130388 += D_0013038C * dt;
        if (1.0f <= D_00130388)
            D_00130388 = 1.0f;
        i = 0;
        gsRegBegin();
        gsReg(0x4C, (getFrameBufferSizeFBP() + ((getDrawScreenWidth() * getDrawScreenHeight()) >> 11)) | 0x40000);
        gsReg(0x18, gsXyoffset(0x100, 0x100));
        gsReg(0x40, gsScissor(0x100, 0x100));
        gsReg(0x42, 0x44 | ((u64)0x80 << 32));
        gsReg(0x47, 0x31001);
        w.r.rect = D_0013C8D0;
        memset(w.r.col, 0, sizeof(w.r.col));
        spriteNoTexFast(w.r.rect.x, w.r.rect.y, w.r.rect.w, w.r.rect.h, 0xFFFFFF, w.r.col, 1);
        gsRegEnd();
        glDisable(2);
        glBegin(6);
        {
            memset(w.c.c0, 0, sizeof(w.c.c0));
            w.c.c0[3] = 1.0f;
            memset(w.c.c1, 0, sizeof(w.c.c1));
            w.c.c1[3] = 1.0f;
            cx = B_00147300[0] * 256.0f - 128.0f;
            cy = B_00147300[1] * 256.0f - 128.0f;
            glColor4fv(w.c.c1);
            glVertex2f(cx, cy);
            glColor4fv(w.c.c0);
            do {
                a = 2.0f * (i * 3.1415926f) * 0.0625f;
                i++;
                s = iosGetSinf(a);
                glVertex2f(cx + iosGetCosf(a) * 256.0f * D_00130388, cy + s * 256.0f * D_00130388);
            } while (i < 16);
            glVertex2f(cx + iosGetCosf(0.0f) * 256.0f * D_00130388, cy + iosGetSinf(0.0f) * 256.0f * D_00130388);
        }
        glEnd();
        glEnable(2);
    }
    gsRegBegin();
    gsReg(0x4C, gsFrameSize(getFrameBufferSize(), getDrawScreenWidth()));
    gsReg(0x18, gsXyoffset(getDrawScreenWidth(), getDrawScreenHeight()));
    gsReg(0x40, gsScissor(getDrawScreenWidth(), getDrawScreenHeight()));
    gsReg(0x4D, gsFrameSize(getFrameBufferSize(), getDrawScreenWidth()));
    gsReg(0x19, gsXyoffset(getDrawScreenWidth(), getDrawScreenHeight()));
    gsReg(0x41, gsScissor(getDrawScreenWidth(), getDrawScreenHeight()));
    gsReg(0x47, 0x31001);
    drawFull(&tbl.fb[1], D_00130370);
    gsRegEnd();
    iosDlPopLayer();
}
