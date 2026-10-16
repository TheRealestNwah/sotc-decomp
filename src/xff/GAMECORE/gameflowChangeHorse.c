extern int checkPointChangeHorse;
extern int _omakeSelectFlagChk(int);
extern void omakeGetAndSelectSet(int);
extern void omakeGetAndSelectCls(int);
extern void gStatOmakeSave(void);

void gameflowChangeHorse(void)
{
    if (checkPointChangeHorse == 1) {
        if (!_omakeSelectFlagChk(8))
            omakeGetAndSelectSet(8);
        else
            omakeGetAndSelectCls(8);
        gStatOmakeSave();
    } else if (checkPointChangeHorse == 2) {
        if (!_omakeSelectFlagChk(9))
            omakeGetAndSelectSet(9);
        else
            omakeGetAndSelectCls(9);
        gStatOmakeSave();
    }
    checkPointChangeHorse = 0;
}
