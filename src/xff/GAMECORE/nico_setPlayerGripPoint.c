extern int GetSCRCharaAIWorkPtr();
extern int player_setGripHangPointGeometry();

int nico_setPlayerGripPoint(int a)
{
    return player_setGripHangPointGeometry(a, GetSCRCharaAIWorkPtr(a) + 6848);
}
