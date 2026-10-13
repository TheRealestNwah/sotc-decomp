typedef struct {
    char pad0[0x3BC];
    int searchPointMax;
} Way;

void setSearchPointMax(Way *way, int max)
{
    if (max <= 0) {
        way->searchPointMax = 0x380;
    } else {
        way->searchPointMax = max;
    }
}
