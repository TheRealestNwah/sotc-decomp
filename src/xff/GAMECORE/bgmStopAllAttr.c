extern unsigned char B_001888E8[];

void bgmStopAllAttr(int arg0, int arg1)
{
    void *var_v1;
    int var_a2;

    var_a2 = 2;
    var_v1 = B_001888E8;
    do {
        var_a2 -= 1;
        if (((*(int *)((char *)(var_v1) + 8)) != 0) && ((*(int *)((char *)(var_v1) + 4)) & arg0)) {
            (*(int *)((char *)(var_v1) + 0x20)) = 0;
            (*(int *)((char *)(var_v1) + 0x24)) = (int) ((*(int *)((char *)(var_v1) + 0x24)) | 4);
            (*(float *)((char *)(var_v1) + 0x18)) = (float) arg1;
        }
        var_v1 += 0x34;
    } while (var_a2 >= 0);
}
