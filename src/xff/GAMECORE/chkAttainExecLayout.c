extern int ZeroVector[];
extern int chkAttainExecOffsetData(int, int, int, int *, int, float);

int chkAttainExecLayout(int a, int b, int c, int d)
{
    return chkAttainExecOffsetData(a, b, c, ZeroVector, d, 0.0f);
}
