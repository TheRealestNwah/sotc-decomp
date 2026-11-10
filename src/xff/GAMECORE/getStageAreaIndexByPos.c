typedef struct {
    char pad0[0x30];
    int cols;
    int rows;
    int cw;
    int ch;
    float sx;
    float sy;
    int width;
    int height;
    float ox;
    float oz;
} AreaMap;

extern AreaMap D_0017A340;

#ifdef NONMATCHING /* 55 diffs: scheduling of the float loads and int/float divides; the divisors at 0x38/0x3C are ints with a zero check */
int getStageAreaIndexByPos(float *p)
{
    float pz = p[2];
    float px = p[0];
    int y = (D_0017A340.rows - ((int)((-pz - D_0017A340.oz) / D_0017A340.sy) / D_0017A340.ch)) - 1;
    int x = (int)((-px - D_0017A340.ox) / D_0017A340.sx) / D_0017A340.cw;

    if (x < 0 || D_0017A340.cols - 1 < x)
        x = -1;
    if (y < 0 || D_0017A340.rows - 1 < y)
        y = -1;
    if (x < 0 || x >= D_0017A340.width || y < 0 || y >= D_0017A340.height)
        return -1;
    return y * D_0017A340.width + x;
}
#else
extern int getStageAreaIndexByPos(float *p);
#endif
