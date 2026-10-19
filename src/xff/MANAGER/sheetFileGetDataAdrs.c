char *sheetFileGetDataAdrs(void *arg0)
{
    char *var_a1;
    void *temp_v0;

    temp_v0 = (*(void **)((char *)(arg0) + 4));
    var_a1 = (*(char **)((char *)(temp_v0) + 0x10));
    if (var_a1 != 0) {
        var_a1 += (*(int *)((char *)((*(void **)((char *)(temp_v0) + 8))) + 0xC)) * (*(int *)((char *)(arg0) + 8));
    }
    return var_a1;
}
