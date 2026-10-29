extern int getArrowObjParent(void *);

int SCRConditionArrowParentOverNum(int a, int n)
{
    return getArrowObjParent((void *)a) >= n;
}
