extern char *GetSCRCharaAIWorkPtr(int);
extern void player_setDangerEdgeOtherSidePlanePoint(int, char *);
extern int SetInertiaRotInterpMode(int);

int SetPlayerDangerEdgeOtherSidePlanePointWithInertiaRot(int a)
{
    player_setDangerEdgeOtherSidePlanePoint(a, GetSCRCharaAIWorkPtr(a) + 0x1BB0);
    return SetInertiaRotInterpMode(a);
}
