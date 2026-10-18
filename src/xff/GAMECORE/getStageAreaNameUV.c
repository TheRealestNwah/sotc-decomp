typedef struct { char pad[0x30]; int width, height, unitX, unitZ; } AreaGrid;
extern AreaGrid D_0017A340;
void getStageAreaNameUV(char *name, int x, int z)
{
    int column = x / D_0017A340.unitX;
    int row = D_0017A340.height - z / D_0017A340.unitZ - 1;
    if (column < 0 || column > D_0017A340.width - 1)
        name[0] = column + 0x3F;
    else
        name[0] = column + 0x41;
    if (row < 0 || row > D_0017A340.height - 1)
        name[1] = row + 0x3F;
    else
        name[1] = row + 0x30;
    name[2] = 0;
}