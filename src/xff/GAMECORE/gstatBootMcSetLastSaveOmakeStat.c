typedef struct { long d[14]; } OmakeStat;
extern OmakeStat B_00188550;

void gstatBootMcSetLastSaveOmakeStat(OmakeStat *s)
{
    B_00188550 = *s;
}
