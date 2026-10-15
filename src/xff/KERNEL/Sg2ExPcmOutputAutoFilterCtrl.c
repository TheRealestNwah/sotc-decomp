typedef struct {
    int on;
    char pad[0xC0];
} PcmOut;

extern PcmOut B_000E237C[];

void Sg2ExPcmOutputAutoFilterCtrl(int ch, int on)
{
    B_000E237C[ch].on = on;
}
