typedef struct {
    int v[0x93];
} CheckPoint;

extern CheckPoint B_00183B58;

void backStageCheckPointLoad(CheckPoint *src)
{
    B_00183B58 = *src;
}
