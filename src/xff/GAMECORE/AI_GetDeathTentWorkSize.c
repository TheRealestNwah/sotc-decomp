int AI_GetDeathTentWorkSize(void *arg0, int arg1)
{
    int var_v1;

    var_v1 = ((*(int *)((char *)(arg0) + 0x14)) << 5) + 0x429;
    if (arg1 >= (*(int *)((char *)(arg0) + 0x1C))) {
        var_v1 += (*(int *)((char *)(arg0) + 0x4C));
    }
    return var_v1;
}
