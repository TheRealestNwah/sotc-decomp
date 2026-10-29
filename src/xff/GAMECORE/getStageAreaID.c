typedef struct {
    char pad0[0x30];
    int width, height, unitX, unitZ;
    float sizeX, sizeZ;
    char pad48[8];
    float offsetX, offsetZ;
} AreaGrid;
extern AreaGrid D_0017A340;

void getStageAreaID(const float *position, int *x, int *z)
{
    AreaGrid *g = &D_0017A340;
    int iz = (-position[2] - g->offsetZ) / g->sizeZ;
    int ix = (-position[0] - g->offsetX) / g->sizeX;
    int column = ix / g->unitX;
    int row = g->height - iz / g->unitZ - 1;

    if (column < 0 || column > g->width - 1)
        *x = -1;
    else
        *x = column;
    if (row < 0 || row > D_0017A340.height - 1)
        *z = -1;
    else
        *z = row;
}
