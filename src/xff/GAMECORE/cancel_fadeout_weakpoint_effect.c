extern int D_0017ABB0;
extern char B_0018A9B0[];

void cancel_fadeout_weakpoint_effect(void)
{
    int i;
    char *p;
    if (D_0017ABB0 == 0) return;
    p = B_0018A9B0;
    for (i = 7; i >= 0; i--) {
        if ((unsigned)(*(int *)(p + 4) - 2) < 2) *(int *)(p + 4) = 0;
        p += 0x78;
    }
}
