typedef struct { int on; int a; int mod; char pad[0x74]; } Smfp;
extern Smfp B_000E0DC0[];
extern void Sg2ModSetParam(int, int, int, int);

int Sg2SmfpCont(int i)
{
    if (i >= 0)
        B_000E0DC0[i].on = 2;
    Sg2ModSetParam((B_000E0DC0 + i)->mod, 0x40, 0, 0);
    return 0;
}
