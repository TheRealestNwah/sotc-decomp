extern int DIntr();
extern void EIntr();
extern unsigned char B_000C5B08[1];

short Sg2DspEffectSetDepth2(int arg0, short arg1, short arg2)
{
    short temp_s0;
    int temp_v0;
    void *temp_v1;

    temp_v0 = DIntr();
    temp_v1 = &B_000C5B08 + (arg0 * 0x18);
    (*(short *)((char *)(temp_v1) + 0xE)) = arg2;
    temp_s0 = (*(short *)((char *)(temp_v1) + 0xC));
    (*(short *)((char *)(temp_v1) + 0xC)) = arg1;
    if (temp_v0 != 0) {
        EIntr();
    }
    return temp_s0;
}
