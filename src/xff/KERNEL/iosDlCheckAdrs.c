extern int B_00065018[];
extern int D_00040AFC;
int iosDlCheckAdrs(unsigned int a)
{
    return a < B_00065018[B_00065018[6]] + D_00040AFC * 16 - 0x1000;
}
