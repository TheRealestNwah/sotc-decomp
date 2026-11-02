typedef struct {
    char pad0[0x30];
    int width, height, unitX, unitZ;
    float sizeX, sizeZ;
    char pad48[8];
    float offsetX, offsetZ;
} AreaGrid;
extern AreaGrid D_0017A340;

/* Writes the area name for `position`, e.g. "C4": a column letter, a row
   digit and a terminator. Out-of-range cells are shifted down by 2. */
void getStageAreaName(char *name, const float *position)
{
    AreaGrid *g = &D_0017A340;
    int z = (-position[2] - g->offsetZ) / g->sizeZ;
    int x = (-position[0] - g->offsetX) / g->sizeX;
    int column = x / g->unitX;

    /* The original reuses the z coordinate's variable for the row. */
    z = g->height - z / g->unitZ - 1;
    if (column < 0 || column > g->width - 1)
        name[0] = column + 0x3F;
    else
        name[0] = column + 0x41;
    if (z < 0 || z > D_0017A340.height - 1)
        name[1] = z + 0x3F;
    else
        name[1] = z + 0x30;
    name[2] = 0;
}
