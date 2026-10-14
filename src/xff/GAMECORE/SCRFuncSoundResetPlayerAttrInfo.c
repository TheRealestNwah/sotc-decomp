extern int *getSScriptWork();
extern int getPlayerColCont2();
extern int ColCont2_EventAttrReset();

int SCRFuncSoundResetPlayerAttrInfo(void)
{
    return ColCont2_EventAttrReset(getPlayerColCont2(*getSScriptWork()));
}
