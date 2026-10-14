extern int GetSCRCharaAIWorkPtr();
extern int player_setEdgeHangPointGeometry();

int nico_setPlayerEdgePoint(int a)
{
    return player_setEdgeHangPointGeometry(a, GetSCRCharaAIWorkPtr(a) + 6848);
}
