extern unsigned char B_000DE370[1];

void Sg2SlotSetPoltamentParam(int arg0, int arg1, float fparg0)
{
    float var_f12;
    int temp_v0;
    int temp_v0_2;
    void *temp_v1;

    var_f12 = fparg0;
    temp_v1 = &B_000DE370 + (arg0 * 0xE0);
    temp_v0 = (*(int *)((char *)(temp_v1) + 0));
    if (!(temp_v0 & 0x200)) {
        temp_v0_2 = (*(int *)((char *)(temp_v1) + 0x24));
        (*(int *)((char *)(temp_v1) + 0)) = (int) (temp_v0 | 0x200);
        (*(int *)((char *)(temp_v1) + 0xDC)) = 0;
        (*(int *)((char *)(temp_v1) + 0xCC)) = temp_v0_2;
        (*(int *)((char *)(temp_v1) + 0xD0)) = temp_v0_2;
    }
    (*(int *)((char *)(temp_v1) + 0xD4)) = arg1;
    if (arg1 < (*(int *)((char *)(temp_v1) + 0xD0))) {
        var_f12 = -var_f12;
    }
    (*(float *)((char *)(temp_v1) + 0xD8)) = var_f12;
}
