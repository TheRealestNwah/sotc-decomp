extern char B_000E26C0[];

void Sg2ExPcmInputSetOutputMode(unsigned int ch, int mode)
{
    if (ch < 4) {
        *(int *)(B_000E26C0 + ch * 0x1D4) = mode;
    }
}
