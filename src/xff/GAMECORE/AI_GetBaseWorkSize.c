int AI_GetBaseWorkSize(int arg0, int arg1)
{
    int var_v1;

    var_v1 = (arg0 * 4) + 0xD6;
    if (arg1 > 0) {
        var_v1 = var_v1 + (arg0 * 0x30) + 0x33;
    }
    return var_v1;
}
