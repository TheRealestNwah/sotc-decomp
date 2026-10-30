typedef struct {
    int rgba[4] __attribute__((aligned(16)));
    int flag;
    int pad[3];
} FontColor;

extern void *memset(void *, int, unsigned int);
extern void windowSpriteNoTex(void *, float *, void *, float);
extern void windowFontColor(void *, void *);
extern void windowPrintf(void *, float, float, const char *, ...);
extern int D_001396C0[];

static void func_000D4638(void *unused, char *w)
{
    float rect[4];

    memset(rect, 0, sizeof(rect));
    rect[3] = 16.0f;
    {
        FontColor color = { { 0xFF, 0xFF, 0xFF, 0x80 }, 1 };

        windowSpriteNoTex(w, rect, D_001396C0, 16777215.0f);
        windowFontColor(w, &color);
    }
    windowPrintf(w, *(float *)(w + 0x26C) - 77.0f - 2.0f, 2.0f, "%11s", *(char **)(w + 0x3E8));
}
