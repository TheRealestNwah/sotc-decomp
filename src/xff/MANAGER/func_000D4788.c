#ifdef NONMATCHING /* 10 diffs: the color copy and the item load are scheduled in a different order */
typedef struct { float f[8]; } __attribute__((aligned(8))) Color8;

extern unsigned int strlen(const char *);
extern void windowFontColor(void *, void *);
extern void windowPrintf(void *, float, float, const char *, ...);
extern Color8 RO_0011AC10;
extern char RO_0011ABF0[];

static void func_000D4788(void *unused, char *win)
{
    Color8 color = RO_0011AC10;
    char *item = *(char **)(win + 0x3E0);
    float cx;
    float x;

    if (*(char **)(item + 4) == 0)
        return;
    cx = *(float *)(win + 0x1B0) * 0.5f;
    x = cx - (float)(strlen(*(char **)(item + 4)) * 7) * 0.5f;
    windowFontColor(win, &color);
    windowPrintf(win, x, 4.0f, RO_0011ABF0, *(char **)(item + 4));
}
#endif
