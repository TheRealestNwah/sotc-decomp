extern int getArrowObjParent();

int SCRConditionArrowParentOverNum(int a, int n)
{
    return getArrowObjParent() >= n;
}
