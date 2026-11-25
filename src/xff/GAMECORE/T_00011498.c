/* Parked: 13 diffs, 268 words (same length). Caption job script (started by func_000118C8):
 * copies its 0x34-byte job, then while captions are enabled (D_00179FE8) fades alpha out when
 * *hidden is set, otherwise runs the fade-in / hold / fade-out / done states on its clock
 * and draws the caption strip (texture tex, row style, height pos) as a GS sprite on its layer.
 * Remaining: the r = v copy stores its low half first (the Original stores 0x48 before 0x40),
 * the second gsReg(3) loads r.h before r.y, and the second gsReg(4) y offset adds 0x8000 in
 * 64-bit (daddu with a fresh ori) where the Original adds it in SImode through the
 * assembler's macro (ori at / addu). Writing that add in SImode makes gcc keep 0x8000 in a
 * saved register across the loop (263 diffs). */
#ifdef NONMATCHING
typedef struct { int tex; int *hidden; int state; int style; int pos; int layer; float len; float fadeIn; float fadeOut; float alpha; float time; int unk2C; int *count; } CaptionJob;
typedef union { struct { int x, y, w, h; }; float f[4]; } __attribute__((aligned(8))) Rect;
typedef struct { char pad[0x180]; float dt; } GcGlobal;
extern int D_00179FE8; extern int D_00179FF0; extern GcGlobal gcGlobalVar;
extern void iosDlPushLayer(int); extern void iosDlPopLayer(void);
extern int getDrawScreenWidth(void); extern int getDrawScreenHeight(void);
extern void iosSetRootDC(void); extern void texTransRequest(int, int, int);
extern void gsRegBegin(void); extern void gsReg(long, long); extern void gsRegEnd(void); extern void scrRun(void);

static void T_00011498(CaptionJob *arg)
{
    CaptionJob job = *arg;
    CaptionJob *j = &job;
    int run = 1;
    long z;
    int w;
    int h;
    Rect r;
    Rect v;
    Rect t;

    while (D_00179FE8 != 0 && run) {
        float dt = gcGlobalVar.dt;
        if (*j->hidden != 0) {
            j->alpha -= dt / j->fadeOut;
            if (j->alpha <= 0.0f)
                j->alpha = 0.0f;
            j->state = 1;
        } else {
            j->time += dt;
            switch (j->state) {
            case 0:
                break;
            case 1:
                j->alpha += dt / j->fadeIn;
                if (1.0f <= j->alpha) {
                    j->alpha = 1.0f;
                    j->state = 2;
                }
                break;
            case 2:
                if (j->len - j->fadeOut < j->time || D_00179FF0 != 0)
                    j->state = 3;
                break;
            case 3:
                j->alpha -= dt / j->fadeOut;
                if (j->alpha <= 0.0f) {
                    j->alpha = 0.0f;
                    j->state = 4;
                }
                break;
            case 4:
                run = 0;
                break;
            }
            z = (long)0xFFFFFF << 32;
            iosDlPushLayer(j->layer);
            w = getDrawScreenWidth();
            h = getDrawScreenHeight();
            v.x = 0; v.y = j->style << 10; v.w = 0x2000; v.h = 0x400;
            t.x = 0x80; t.y = 0x80; t.w = 0x80;
            r = v;
            t.h = (int)(j->alpha * 128.0f);
            v = t;
            iosSetRootDC();
            texTransRequest(j->tex, 0, 0);
            gsRegBegin();
            gsReg(0x4A, 0);
            gsReg(0x3B, ((long)0x80 << 32) | 0x80);
            gsReg(0x47, 0x31001);
            gsReg(0x42, 0x44);
            gsReg(0x14, 0);
            gsReg(0x08, 5);
            gsReg(0, 0x156);
            gsReg(1, (long)v.x | ((long)v.y << 8) | ((long)v.w << 16) | ((long)v.h << 24) | ((long)0x3F800000 << 32));
            gsReg(3, (r.x + 8) | ((long)(r.y + 8) << 16));
            gsReg(4, (0x8000 - ((w >> 1) << 4)) | ((long)((((h >> 1) - j->pos - 0x40) << 4) + 0x8000) << 16) | z);
            gsReg(3, (r.x + r.w + 8) | ((long)(r.y + r.h + 8) << 16));
            gsReg(4, (0xA000 - ((w >> 1) << 4)) | ((long)(((h >> 1) - j->pos) << 4) + 0x8000 << 16) | z);
            gsReg(0x47, 0x50000);
            gsRegEnd();
            iosDlPopLayer();
        }
        scrRun();
    }
}
#endif
