typedef struct {
    int v[0x93];
} CheckPoint;

extern CheckPoint B_00183B58;

void backStageCheckPointSave(CheckPoint *dst)
{
    *dst = B_00183B58;
}
