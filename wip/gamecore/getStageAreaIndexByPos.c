struct StageArea {
    char pad[0x30];
    int countX;
    int countZ;
    int divX;
    int divZ;
    float sizeX;
    float sizeZ;
    int areaX;
    int areaZ;
    float originX;
    float originZ;
};

extern struct StageArea D_0017A340;
static inline int clampX(int x)
{
    if (x < 0 || D_0017A340.countX - 1 < x)
        x = -1;
    return x;
}

static inline int clampZ(int z)
{
    if (z < 0 || D_0017A340.countZ - 1 < z)
        z = -1;
    return z;
}

static inline int calcIndex(int x, int z)
{
    if (x < 0 || x >= D_0017A340.areaX || z < 0 || z >= D_0017A340.areaZ)
        return -1;
    return z * D_0017A340.areaX + x;
}

int getStageAreaIndexByPos(float *pos)
{
    float fx = (-pos[0] - D_0017A340.originX) / D_0017A340.sizeX;
    float fz = (-pos[2] - D_0017A340.originZ) / D_0017A340.sizeZ;
    int x = (int)fx / D_0017A340.divX;
    int z = D_0017A340.countZ - (int)fz / D_0017A340.divZ - 1;

    return calcIndex(clampX(x), clampZ(z));
}
