extern int GetSCRCharaAIWorkPtr();
extern int player_setHellDangerPoint();

int SetPlayerHellDangerPoint(int a)
{
    return player_setHellDangerPoint(a, GetSCRCharaAIWorkPtr(a) + 7088);
}
