typedef struct { char pad[0x1B0]; int a; int b; char pad2[0x1C]; } PcmIn;
extern PcmIn B_000E2518[];
extern void func_0002F0D8(unsigned int);

void Sg2ExPcmInputSetPhase(unsigned int i, int a, int b)
{
    if (i < 4) {
        PcmIn *p = &B_000E2518[i];
        p->a = a;
        p->b = b;
        func_0002F0D8(i);
    }
}
