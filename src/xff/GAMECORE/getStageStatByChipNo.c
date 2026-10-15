typedef struct { int a, b; int stat[4]; } ChipStat;
extern ChipStat *D_0017A348;

int getStageStatByChipNo(int chip, int k)
{
    if (chip != -1)
        return D_0017A348[chip].stat[k] & 0xF;
    return 7;
}
