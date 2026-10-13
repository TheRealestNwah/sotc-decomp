extern int B_000C5B00;

int Sg2CtrlSetTickTime(int arg0)
{
    int temp_v0;

    temp_v0 = B_000C5B00;
    B_000C5B00 = arg0;
    return temp_v0;
}
