extern int B_000C5B04;

int Sg2CtrlSetTickMode(int arg0)
{
    int temp_v0;

    temp_v0 = B_000C5B04;
    B_000C5B04 = arg0;
    return temp_v0;
}
