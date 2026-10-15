typedef struct { int v; char pad[0x1D0]; } PcmIn;
extern PcmIn B_000E26D8[];
extern void func_0002F0D8(unsigned int);

void Sg2ExPcmInputSetPan(unsigned int i, int v)
{
    if (i < 4) {
        B_000E26D8[i].v = v;
        func_0002F0D8(i);
    }
}
