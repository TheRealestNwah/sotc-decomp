typedef struct {
    char pad[0x40];
    float sx;
    float sz;
    char pad2[8];
    float ox;
    float oz;
} StageGrid;

extern StageGrid D_0017A340;

void getSeamlessStageCenter(float *out, float *pos)
{
    int ix = (-pos[0] - D_0017A340.ox) / D_0017A340.sx;
    int iz = (-pos[2] - D_0017A340.oz) / D_0017A340.sz;

    out[0] = -((float)ix * D_0017A340.sx + D_0017A340.sx * 0.5f + D_0017A340.ox);
    out[2] = -((float)iz * D_0017A340.sz + D_0017A340.sz * 0.5f + D_0017A340.oz);
}
