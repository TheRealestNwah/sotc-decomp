extern unsigned char B_000E2210[1];

int vab_set_semastervol(int arg0, int arg1)
{
    int *temp_v1;
    int temp_v0;

    temp_v1 = &B_000E2210 + (arg0 * 0x2C);
    temp_v0 = *temp_v1;
    *temp_v1 = arg1;
    return temp_v0;
}
