extern void isysMoveModuleObj(int *);
extern void isysResolveOneModuleObj(int *);
extern void modelReInitialize(int, int);
void garbageNmoCallBack(int *p)
{
    isysMoveModuleObj(p);
    isysResolveOneModuleObj(p);
    modelReInitialize(p[0], p[8]);
}
