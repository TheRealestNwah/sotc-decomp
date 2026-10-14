extern int _omakeGetFlagChk();

int SCRConditionGetOmakeFlag(int a, int b, int c, int d)
{
    return _omakeGetFlagChk(b, b, c, d);
}
