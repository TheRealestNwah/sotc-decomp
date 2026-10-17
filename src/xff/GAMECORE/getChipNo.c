typedef struct {
    char pad[0x48];
    int width;
    int height;
} MapSize;

extern MapSize D_0017A340;

int getChipNo(int x, int y)
{
    if (x < 0 || x >= D_0017A340.width || y < 0 || y >= D_0017A340.height)
        return -1;
    return y * D_0017A340.width + x;
}
