/* ~50 diffs, 1 word short (66 vs 67). Maps a world position to a stage-area grid cell: x/z are negated and offset by D_0017A340 f50/f54, divided by the cell sizes f40/f44, the integer cells divided again by d38 / d3C (the C divide-by-zero guards are the `break 0, 7` words) with the row flipped (n34 - z/d3C - 1), both clamped to -1 outside [0, n30) / [0, n34), and the index is row * n48 + col only when col < n48 and row < n4C, else -1. Original loads pos[2] first and checks the d3C divisor before the d38 one; ours loads x first and checks d38 first (source-order variants and 10 minutes of permuter did not move it: best 50, permuter 2850 -> 2355). */
typedef struct {
    char pad0[0x30];
    int n30;
    int n34;
    int d38;
    int d3C;
    float f40;
    float f44;
    int n48;
    int n4C;
    float f50;
    float f54;
} StageGrid;

extern StageGrid D_0017A340;


#ifdef NONMATCHING
int getStageAreaIndexByPos(float *pos)
{
    int row;
    int col;
    float fz = -pos[2] - D_0017A340.f54;
    float fx = -pos[0] - D_0017A340.f50;
    row = (int)(fz / D_0017A340.f44);
    col = (int)(fx / D_0017A340.f40);
    row = D_0017A340.n34 - row / D_0017A340.d3C - 1;
    col = col / D_0017A340.d38;
    if (col < 0 || col > D_0017A340.n30 - 1)
        col = -1;
    if (row < 0 || row > D_0017A340.n34 - 1)
        row = -1;
    if (col >= 0 && col < D_0017A340.n48 && row >= 0 && row < D_0017A340.n4C)
        return row * D_0017A340.n48 + col;
    return -1;
}
#endif
