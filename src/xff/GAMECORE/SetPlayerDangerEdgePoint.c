extern int GetSCRCharaAIWorkPtr();
extern int player_setDangerEdgePoint();

int SetPlayerDangerEdgePoint(int a)
{
    return player_setDangerEdgePoint(a, GetSCRCharaAIWorkPtr(a) + 7088);
}
