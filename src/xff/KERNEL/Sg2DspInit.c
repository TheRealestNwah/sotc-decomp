extern unsigned char B_000C5B08[];

int Sg2DspInit(int reserved)
{
    void *var_v0;
    int var_v1;

    var_v1 = 1;
    var_v0 = B_000C5B08;
    do {
        var_v1 -= 1;
        (*(int *)((char *)(var_v0) + 0)) = 0;
        (*(int *)((char *)(var_v0) + 4)) = 0;
        (*(short *)((char *)(var_v0) + 0xC)) = 0;
        (*(short *)((char *)(var_v0) + 0xE)) = 0;
        (*(int *)((char *)(var_v0) + 0x10)) = 0;
        (*(int *)((char *)(var_v0) + 0x14)) = 0;
        var_v0 += 0x18;
    } while (var_v1 >= 0);
    return 0;
}
