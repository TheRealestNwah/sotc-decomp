void SetScriptCharacterObjReleaseCallBackFunc(unsigned char *p, int a, int b)
{
    char *c = p[8] != 9 ? 0 : (char *)p + 0x20;

    *(int *)(c + 0x1208) = a;
    *(int *)(c + 0x120C) = b;
}
