int charrootdyn_isParentToEdge(void *arg0)
{
    int var_v1;

    var_v1 = 0;
    if ((*(int *)((char *)(arg0) + 0x124)) != 0) {
        var_v1 = (*(int *)((char *)(arg0) + 0xF0)) == 4;
    }
    return var_v1;
}
