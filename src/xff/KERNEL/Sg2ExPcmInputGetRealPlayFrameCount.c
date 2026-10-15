typedef struct {
    int value;
    char pad[0x1D0];
} PcmIn;

extern PcmIn B_000E26E8[];

int Sg2ExPcmInputGetRealPlayFrameCount(unsigned int ch)
{
    if (ch >= 4) {
        return -1;
    }
    return B_000E26E8[ch].value;
}
