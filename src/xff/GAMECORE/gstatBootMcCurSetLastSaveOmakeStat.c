typedef struct { long d[14]; } OmakeStat;
extern OmakeStat B_001884D0;
extern OmakeStat B_00188550;
extern int D_0017A298;
extern int D_0017A29C;
extern int getGameClearCnt(void);

void gstatBootMcCurSetLastSaveOmakeStat(void)
{
    int n;
    int one;

    B_00188550 = B_001884D0;
    n = getGameClearCnt();
    one = 1;
    D_0017A298 = one;
    D_0017A29C = n;
}
