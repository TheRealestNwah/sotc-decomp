typedef struct { int count; void *definition; } TexSegment;
extern TexSegment *B_001517B8;
extern int B_001517BC;
int sheetFsAddStageTexSegIndex(int i)
{
    int c = B_001517B8[i].count;
    B_001517B8[i].count = c + 1;
    return c;
}
int sheetFsDecStageTexSegIndex(int i)
{
    return --B_001517B8[i].count;
}
void sheetFsExistTexSegIndexCallBack(void (*callback)(int))
{
    int i;
    for (i = 0; i < B_001517BC; i++) {
        if (B_001517B8[i].count) {
            callback(i);
            B_001517B8[i].count = 0;
        }
    }
}
void sheetFsSetStageTexSegTexSegDef(int i, void *definition)
{
    B_001517B8[i].definition = definition;
}
void *sheetFsGetStageTexSegTexSegDef(int i)
{
    return B_001517B8[i].definition;
}
