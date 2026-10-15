typedef struct { int a, b, seg; } Seg;
extern char *B_001517C0;

int sheetFsGetStageTexSegIndex(int x, int y)
{
    return (*(Seg **)(B_001517C0 + 8))[(4 - y) * 10 + (x + 5) % 10].seg;
}
