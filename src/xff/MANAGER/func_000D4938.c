typedef struct { long a; long b; } Pair16;
extern void windowCursorBlink(void *, void *);
extern void windowCloseRequest(void *);

static void func_000D4938(char *w)
{
    char *item = *(char **)(*(char **)w + 0x3E0);

    if (*(int *)(w + 0xB4) & 1) {
        windowCursorBlink(w + 0x40, w + 0x60);
        *(Pair16 *)(w + 0x70) = *(Pair16 *)(w + 0x90);
        *(int *)(w + 0xA0) = *(int *)(w + 0xA8);
    } else {
        *(Pair16 *)(w + 0x40) = *(Pair16 *)(w + 0x50);
        *(Pair16 *)(w + 0x70) = *(Pair16 *)(w + 0x80);
        *(int *)(w + 0xA0) = *(int *)(w + 0xA4);
    }
    if (*(int *)(w + 0xB4) & 0x20020) {
        switch (*(signed char *)(w + 4)) {
        case 'Y':
            windowCloseRequest(*(void **)w);
            if (*(void (**)(void))(item + 0x10) != 0)
                (*(void (**)(void))(item + 0x10))();
            break;
        case 'N':
            windowCloseRequest(*(void **)w);
            if (*(void (**)(void))(item + 0x14) != 0)
                (*(void (**)(void))(item + 0x14))();
            break;
        }
    }
}
