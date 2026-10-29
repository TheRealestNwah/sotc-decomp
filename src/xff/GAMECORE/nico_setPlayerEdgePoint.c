extern void *GetSCRCharaAIWorkPtr(void *);
extern void player_setEdgeHangPointGeometry(void *, char *);

void nico_setPlayerEdgePoint(void *actor)
{
    player_setEdgeHangPointGeometry(actor, (char *)GetSCRCharaAIWorkPtr(actor) + 6848);
}
