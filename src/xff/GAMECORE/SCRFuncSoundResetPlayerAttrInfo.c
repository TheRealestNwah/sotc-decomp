extern int *getSScriptWork();
extern void *getPlayerColCont2(void *);
extern int ColCont2_EventAttrReset();

int SCRFuncSoundResetPlayerAttrInfo(void)
{
    return ColCont2_EventAttrReset(getPlayerColCont2((void *)*getSScriptWork()));
}
