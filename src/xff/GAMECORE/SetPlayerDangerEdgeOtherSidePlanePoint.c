extern int GetSCRCharaAIWorkPtr();
extern int player_setDangerEdgeOtherSidePlanePoint();

int SetPlayerDangerEdgeOtherSidePlanePoint(int a)
{
    return player_setDangerEdgeOtherSidePlanePoint(a, GetSCRCharaAIWorkPtr(a) + 7088);
}
