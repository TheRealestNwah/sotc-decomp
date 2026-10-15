typedef struct {
    long flags;
    char pad8[0x560 - 8];
} AdpcmChannel;
extern AdpcmChannel B_0014E8D0[];

int adpcmOpenChkComplete(int ch)
{
    return (int)((unsigned long)B_0014E8D0[ch].flags >> 36) & 1;
}
