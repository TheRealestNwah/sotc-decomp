typedef struct {
    int d0;
    int d4;
    char pad8[4];
    int dC;
    int d10;
    int d14;
    char pad18[8];
} SubWork;

extern int B_000C28FC;
extern int B_000C2904;
extern int B_000C2908;
extern void *isysGetThisSubThread(void);
extern void isysWakeupSubThread(void);

void isysJumpSubThread(void *fn, int arg)
{
    char *th = isysGetThisSubThread();
    SubWork *w;

    switch (*(unsigned char *)(th + 8)) {
    case 6:
    case 9:
    case 11:
    case 12:
    case 13:
    case 14:
    case 22:
    case 29:
    case 33:
        w = (SubWork *)(th + 0x20);
        break;
    default:
        w = 0;
        break;
    }
    w->d4 = (int)fn;
    w->d0 = (int)fn;
    w->d10 = w->dC + w->d14;
    B_000C2904 = arg;
    B_000C28FC = w->d10;
    B_000C2908 = w->d4;
    __asm__ __volatile__(
        ".set noreorder\n"
        "lui $2, %hi(B_000C28FC)\n"
        "nop\n"
        "addiu $2, $2, %lo(B_000C28FC)\n"
        "nop\n"
        "lw $29, 0($2)\n"
        "lui $2, %hi(B_000C2904)\n"
        "nop\n"
        "addiu $2, $2, %lo(B_000C2904)\n"
        "nop\n"
        "lw $4, 0($2)\n"
        "j isysWakeupSubThread+0x3CC\n"
        "nop\n"
        ".set reorder\n");
}
