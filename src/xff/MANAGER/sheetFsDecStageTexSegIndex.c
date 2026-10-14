typedef struct { int idx, b; } Seg;
extern Seg *B_001517B8;

int sheetFsDecStageTexSegIndex(int i)
{
    return --B_001517B8[i].idx;
}
