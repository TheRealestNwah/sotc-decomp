extern char padManagerData[];
extern void windowCloseRequest(char *p);
extern int D_00139720;
extern int D_00139724;

static void func_000D4708(void *unused, char *w)
{
    if (*(int *)(w + 0x1C4) & 0x40040) {
        windowCloseRequest(w);
        D_00139724 = 0;
        D_00139720 = 1;
    } else if (*(int *)(padManagerData + 8) & 0xA000) {
        D_00139720 = 1;
        D_00139724 = D_00139724 == 0;
    }
}
