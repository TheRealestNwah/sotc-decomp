extern void isysMoveModuleObj(void *);
extern void isysResolveOneModuleObj(void *);
extern void shadowModelReInit(void *);

void garbageNsoCallBack(char *o)
{
    isysMoveModuleObj(o);
    isysResolveOneModuleObj(o);
    shadowModelReInit(*(void **)(o + 0x20));
}
