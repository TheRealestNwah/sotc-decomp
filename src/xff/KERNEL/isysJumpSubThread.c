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

/* Parked: about 25 words differ: the switch matches, but the final volatile reads of B_000C28FC/B_000C2904 share the stores' address constants instead of recomputing them, and the jump into isysWakeupSubThread+0x3CC is an inline-asm guess. */
#ifdef NONMATCHING
void isysJumpSubThread(void *fn, int arg)
{
    char *th = isysGetThisSubThread();
    SubWork *w;

    switch (*(unsigned char *)(th + 8)) {
    case 6:
    case 9:
    case 11:
    case 13:
    case 14:
    case 15:
    case 22:
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
    {
        register int spv __asm__("$29") = *(volatile int *)&B_000C28FC;
        register int a0v __asm__("$4") = *(volatile int *)&B_000C2904;

        __asm__ __volatile__("j isysWakeupSubThread+0x3CC" : : "r"(spv), "r"(a0v));
    }
}
#else
extern void isysJumpSubThread(void *fn, int arg);
#endif
