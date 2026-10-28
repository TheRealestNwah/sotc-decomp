typedef struct { char d[0x1D4]; } PcmIn;
extern PcmIn B_000E251C[];
extern void func_0002E640(PcmIn *, int);

void Sg2ExPcmInputAutoFilterInit(unsigned int i, int filter)
{
    if (i < 4)
        func_0002E640(&B_000E251C[i], filter);
}
