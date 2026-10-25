extern void *GetSCRCharaAIWorkPtr(void *);
extern void player_setDangerEdgeOtherSidePlanePoint(void *, char *);
extern void SetInertiaRotInterpMode(void *);

void SetPlayerDangerEdgeOtherSidePlanePointWithInertiaRot(void *obj)
{
    player_setDangerEdgeOtherSidePlanePoint(obj, (char *)GetSCRCharaAIWorkPtr(obj) + 0x1BB0);
    SetInertiaRotInterpMode(obj);
}
