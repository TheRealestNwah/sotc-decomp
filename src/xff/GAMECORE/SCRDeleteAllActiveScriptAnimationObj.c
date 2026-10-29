extern void allArrowRelease(void);
extern void DeleteAllActiveScriptAnimationObj(void);

int SCRDeleteAllActiveScriptAnimationObj(void)
{
    allArrowRelease();
    DeleteAllActiveScriptAnimationObj();
    return 0;
}
