int SetScriptAnimationObjGeometryOverrideCallBackFunc(unsigned char *p, int func, int arg)
{
    unsigned char *c = p[8] != 0xD ? 0 : p + 0x20;
    if (*(int *)(c + 0x358) != 0)
        goto fail;
    *(int *)(c + 0x358) = func;
    *(int *)(c + 0x35C) = arg;
    return 1;
fail:
    return 0;
}
