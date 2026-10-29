extern void *getSScriptWork(void);
extern void *getPlayerColCont2(void *);
extern void ColCont2_EventAttrReset(void *);

void SCRFuncSoundResetPlayerAttrInfo(void)
{
    ColCont2_EventAttrReset(getPlayerColCont2(*(void **)getSScriptWork()));
}
