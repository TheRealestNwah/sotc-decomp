typedef struct {
    char pad[0x14];
    float w;
    float h;
    char pad2[0x18];
    int nx;
    int nz;
} StageInfo;

extern StageInfo *D_0017A868;

void stagemanager_getCenterFromAreaId(float *out, int id)
{
    StageInfo *s = D_0017A868;
    int x = id % s->nx;
    int z = id / s->nx;

    out[0] = -(((float)x - (float)s->nx * 0.5f) * s->w + s->w * 0.5f);
    *(int *)&out[1] = 0;
    out[2] = ((float)z - (float)D_0017A868->nz * 0.5f) * D_0017A868->h + D_0017A868->h * 0.5f;
    out[3] = 1.0f;
}
