extern void isysMoveModuleObj(int *);
extern int isysResolveOneModuleObj(void *);
extern void modelReInitialize(int, int);
void garbageNmoCallBack(int *p)
{
    isysMoveModuleObj(p);
    isysResolveOneModuleObj(p);
    modelReInitialize(p[0], p[8]);
}
