extern long B_00184778;
int getClearGameHotStartFlag(void)
{
    return (int)(B_00184778 >> 8) & 1;
}
