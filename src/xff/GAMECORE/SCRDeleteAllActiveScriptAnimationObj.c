extern int allArrowRelease();
extern int DeleteAllActiveScriptAnimationObj();

int SCRDeleteAllActiveScriptAnimationObj(void)
{
    allArrowRelease();
    DeleteAllActiveScriptAnimationObj();
    return 0;
}
