typedef struct { int v; char pad[0x14]; } E;
extern E B_000C5B08[];

int Sg2DspGetMasterVolume(int i)
{
    return B_000C5B08[i].v;
}
