extern void sceGsResetGraph(short, short, short, short);

void iosResetGraph(short mode, short inter, short omode, short ffmode)
{
    if (mode != 0) {
        *(volatile unsigned long *)0x12001000 = 0x100;
        return;
    }
    *(volatile unsigned long *)0x12001000 = 0x200;
    sceGsResetGraph(0, inter & 1, omode, ffmode & 1);
}
