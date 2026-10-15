typedef struct {
    int value;
    char pad[0x1D0];
} PcmIn;

extern PcmIn B_000E252C[];

int Sg2ExPcmInputGetLipFrame(unsigned int ch)
{
    if (ch >= 4) {
        return -1;
    }
    return B_000E252C[ch].value;
}
