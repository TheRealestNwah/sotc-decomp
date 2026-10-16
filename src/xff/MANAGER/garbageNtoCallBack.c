extern void isysMoveModuleObj(void *);

void garbageNtoCallBack(char *o)
{
    isysMoveModuleObj(o);
    *(char **)(*(char **)(*(char **)(o + 0x20) + 0xC) + 0x28) = o;
}
