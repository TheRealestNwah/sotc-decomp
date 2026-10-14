extern void *GetLayoutClass(void *);
extern void *getSCRDataCtrlWork(int);
extern void setAttainmentPosAndDirPos(void *, int, int);

void SCRFuncSetPlayerAttainDir(int arg0)
{
    void *temp_s1;
    void *temp_v0;

    temp_s1 = GetLayoutClass((void *)arg0);
    temp_v0 = getSCRDataCtrlWork(arg0);
    setAttainmentPosAndDirPos(temp_v0, (*(int *)((char *)(temp_s1) + 0x134)), (*(int *)((char *)((*(void **)((char *)(temp_v0) + 0x407C))) + 0x134)));
}
