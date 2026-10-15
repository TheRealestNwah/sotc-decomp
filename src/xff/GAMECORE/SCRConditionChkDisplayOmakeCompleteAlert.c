extern int dispCompleteAlertNormal;
extern int dispCompleteAlertHard;

int SCRConditionChkDisplayOmakeCompleteAlert(void *actor, int hard)
{
    return hard ? dispCompleteAlertHard : dispCompleteAlertNormal;
}
