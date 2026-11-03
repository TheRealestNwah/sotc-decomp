typedef struct {
    char pad0[0x40];
    int unk40;
    int unk44;
    char pad48[0x8];
    float unk50;
    float unk54;
    float unk58;
    float unk5C;
    int unk60;
} W;

extern float RO_00181444;
static void func_00103830(W *p)
{
    float f = RO_00181444;

    p->unk5C = 1.0f;
    p->unk58 = f;
    p->unk40 = 0;
    do {
        p->unk60 = 0;
    } while (0);
    p->unk44 = 0;
    p->unk54 = f;
    p->unk50 = f;
}
