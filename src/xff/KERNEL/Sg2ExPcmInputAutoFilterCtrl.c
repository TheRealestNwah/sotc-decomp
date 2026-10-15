extern char B_000E2530[];

void Sg2ExPcmInputAutoFilterCtrl(unsigned int ch, int band, int on)
{
    if (ch < 4) {
        *(int *)(B_000E2530 + (band * 0xC4 + ch * 0x1D4)) = on;
    }
}
