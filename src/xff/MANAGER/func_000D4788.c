/* spimdisasm labels these RO_00140EB0/RO_00140E90 inside .vutext; the relocations
   point into .rodata, so the names carry their real .rodata addresses. */
typedef struct { float f[8]; } __attribute__((aligned(8))) Color8;

extern unsigned int strlen(const char *);
extern void windowFontColor(void *, void *);
extern void windowPrintf(void *, float, float, const char *, ...);
extern Color8 RO_00140EB0;
extern char RO_00140E90[];

static void func_000D4788(void *unused, char *win)
{
    Color8 color = RO_00140EB0;
    char *item = *(char **)(win + 0x3E0);
    float cx;
    float x;

    if (*(char **)(item + 4) == 0)
        return;
    cx = *(float *)(win + 0x1B0) * 0.5f;
    x = cx - (float)(strlen(*(char **)(item + 4)) * 7) * 0.5f;
    windowFontColor(win, &color);
    windowPrintf(win, x, 4.0f, RO_00140E90, *(char **)(item + 4));
}
