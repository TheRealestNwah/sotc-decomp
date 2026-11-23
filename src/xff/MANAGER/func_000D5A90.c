/* Draws a window's title text, faded by the window's fade table entry, truncated to the visible
   width, with the font board's flag cleared around the kPrintf call. */
typedef struct {
    unsigned int r;
    unsigned int g;
    unsigned int b;
    unsigned int a;
    int fade;
} WinColor;

extern float D_00139B68[];
extern WinColor D_00139BB0;
extern char RO_001413A0[];
extern int *getFontBoard(void);
extern int strlen(const char *);
extern int iosSPrintf(char *, const char *, ...);
extern int kColor(int, float, float, float, float);
extern void kPrintf(int, int, const char *, ...);

static inline void printAt(float x, float y, const char *s)
{
    kPrintf((int)x, (int)y, s);
}

static void func_000D5A90(char *w)
{
    char buf[0x100];
    float fade;
    char *text;
    float len;
    int *board;
    int saved;
    WinColor *c = &D_00139BB0;

    if (((int)((*(long *)(w + 0x1B8) << 30) >> 32) & 1) == 0)
        fade = D_00139B68[c->fade];
    else
        fade = 1.0f;
    text = w + 0x98;
    if (*(int *)(w + 0x230) != 0 && strlen(text) != 0) {
        kColor(1, (float)c->r / 255.0f, (float)c->g / 255.0f, (float)c->b / 255.0f,
               (float)c->a * 0.0078125f * fade);
        iosSPrintf(buf, RO_001413A0, text);
        if (*(int *)(w + 0x238) != 0)
            len = *(float *)(w + 0x2B4) - *(float *)(w + 0x284);
        else if (*(int *)(w + 0x234) != 0)
            len = *(float *)(w + 0x2A4) - *(float *)(w + 0x284);
        else
            len = *(float *)(w + 0x28C);
        buf[(int)len / 14 * 2] = 0;
        board = getFontBoard();
        saved = *board;
        *board = 0;
        __asm__ volatile("" ::: "memory");
        {
            float y = ((float *)(w + 0x264))[9];
            __asm__ __volatile__("" : "+f"(y));
            printAt(((float *)(w + 0x264))[0], y, buf);
        }
        *board = saved;
    }
}
