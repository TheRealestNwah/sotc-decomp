typedef unsigned long u64;

typedef struct {
    float x, y, w, h;
} Rect;

typedef struct {
    int r, g, b, a;
} Color;

typedef struct {
    char pad0[0x198];
    float unk198;
    float unk19C;
    char pad1A0[0x26C - 0x1A0];
    float unk26C;
    float unk270;
} Window;

extern void iosDlPushLayer(int);
extern void iosDlPopLayer(void);
extern void gsRegBegin(void);
extern void gsReg(int, u64);
extern void gsRegEnd(void);
extern void spriteDrawNoTex(int x, int y, int w, int h, int z, int r, int g, int b, int a);

void windowSpriteNoTex(Window *win, Rect r, Color *col, float z)
{
    int x, y;

    iosDlPushLayer(0x1E);
    gsRegBegin();
    gsReg(0x47, 0x30000);
    x = (int)(r.x + win->unk198 - win->unk26C * 0.5f);
    y = (int)(r.y + win->unk19C - win->unk270 * 0.5f);
    spriteDrawNoTex(x, y,
                    (r.w == 0.0f) ? (int)(win->unk26C + 1.0f) : (int)r.w,
                    (r.h == 0.0f) ? (int)(win->unk270 + 1.0f) : (int)r.h,
                    (int)z, col->r, col->g, col->b, col->a);
    gsReg(0x47, 0x5140B);
    gsRegEnd();
    iosDlPopLayer();
}
