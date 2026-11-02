typedef struct {
    char pad0[0xC];
    int a;
    char pad10[0x4];
    int b;
    char pad18[0xC];
} ClothEntry;

typedef struct {
    short id;
    int count;
    int c;
    char padC[0x1C];
    ClothEntry *entries;
    int flag;
    char pad30[0x4];
} ClothResource;

void DebugDumpClothResources(ClothResource *res)
{
    int i, j;

    for (; res->id >= 0; res++) {
        for (i = 0; i < res->count; i++) {
            for (j = 0; j < res->entries[i].a; j++) {
            }
            for (j = 0; j < res->entries[i].b; j++) {
            }
            if (res->flag >= 0) {
                for (j = 0; j < res->c; j++) {
                }
            }
        }
    }
}
