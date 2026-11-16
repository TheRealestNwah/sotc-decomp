typedef struct { int v[4]; } __attribute__((aligned(8))) Rect;

typedef struct {
    char pad0[0x3E0];
    char *info;
    char pad3E4[4];
    char *buf;
} WinOwner;

typedef struct {
    WinOwner *owner;
    char ch;
    char pad5[0x3B];
    Rect x40;
    Rect x50;
    Rect x60;
    Rect x70;
    Rect x80;
    Rect x90;
    int xA0;
    int xA4;
    int xA8;
    char padAC[8];
    int xB4;
} InputWin;

extern unsigned int strlen(const char *);
extern char *strcat(char *, const char *);
extern void windowCloseRequest(void *);
extern void windowCursorBlink(Rect *, Rect *);

static void T_000D2F18(InputWin *w)
{
    int flags = w->xB4;
    char *info = w->owner->info;
    char *buf;
    unsigned int i;

    if (flags & 1) {
        windowCursorBlink(&w->x40, &w->x60);
        w->x70 = w->x90;
        w->xA0 = w->xA8;
    } else {
        w->x40 = w->x50;
        w->x70 = w->x80;
        w->xA0 = w->xA4;
    }
    if (w->xB4 & 0x20020) {
        buf = w->owner->buf;
        if ((*(int *)(info + 0x18) == 0 || *(int *)(info + 0x18) == 2) && strlen(buf) < 11) {
            switch (w->ch) {
            case '-':
                if (strlen(buf) != 0)
                    break;
            case '0' ... '9':
                strcat(buf, &w->ch);
                break;
            case '.':
                if (*(int *)(info + 0x18) == 2) {
                    if (strlen(buf) >= 2 || (strlen(buf) == 1 && buf[0] != '-')) {
                        for (i = 0; i < strlen(buf); i++) {
                            if (buf[i] == w->ch)
                                break;
                            if (i == strlen(buf) - 1)
                                strcat(buf, &w->ch);
                        }
                    }
                }
                break;
            }
        }
        switch (w->ch) {
        case 'O':
            windowCloseRequest(w->owner);
            return;
        case 'C':
            windowCloseRequest(w->owner);
            *buf = 0;
            break;
        case 'D':
            if (strlen(buf) != 0)
                buf[strlen(buf) - 1] = 0;
            break;
        }
    }
}