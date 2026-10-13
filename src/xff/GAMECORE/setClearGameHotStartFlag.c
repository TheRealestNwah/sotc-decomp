extern long B_00184778;

void setClearGameHotStartFlag(int arg0)
{
    B_00184778 = (B_00184778 & ~0x100) | ((arg0 & 1) << 8);
}
