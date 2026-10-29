extern void *GetSCRCharaAIWorkPtr(void *);
extern void player_setDangerEdgeOtherSidePlanePoint(void *, char *);

void SetPlayerDangerEdgeOtherSidePlanePoint(void *actor)
{
    player_setDangerEdgeOtherSidePlanePoint(actor, (char *)GetSCRCharaAIWorkPtr(actor) + 7088);
}
