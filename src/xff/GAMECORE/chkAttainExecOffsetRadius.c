extern int ZeroVector[];
extern int chkAttainExecOffsetData();

int chkAttainExecOffsetRadius(int a, int b, int c, int d)
{
    return chkAttainExecOffsetData(a, b, c, ZeroVector, d);
}
