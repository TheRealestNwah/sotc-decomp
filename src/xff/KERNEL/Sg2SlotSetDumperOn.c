extern unsigned char B_000DE370[1];

void Sg2SlotSetDumperOn(int arg0)
{
    int *temp_v0;

    temp_v0 = &B_000DE370 + (arg0 * 0xE0);
    *temp_v0 |= 8;
}
