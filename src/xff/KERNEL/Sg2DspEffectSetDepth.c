extern int DIntr();
extern void EIntr();
extern unsigned char B_000C5B08[];

short Sg2DspEffectSetDepth(int arg0, short arg1)
{
    short temp_s1;
    int temp_v0;
    void *temp_v1;

    temp_v0 = DIntr();
    temp_v1 = B_000C5B08 + (arg0 * 0x18);
    temp_s1 = (*(short *)((char *)(temp_v1) + 0xC));
    (*(short *)((char *)(temp_v1) + 0xE)) = arg1;
    (*(short *)((char *)(temp_v1) + 0xC)) = arg1;
    if (temp_v0 != 0) {
        EIntr();
    }
    return temp_s1;
}
