extern void *GetSCRCharaAIWorkPtr(void *);
extern void player_setDangerEdgePoint(void *, char *);

void SetPlayerDangerEdgePoint(void *actor)
{
    player_setDangerEdgePoint(actor, (char *)GetSCRCharaAIWorkPtr(actor) + 7088);
}
