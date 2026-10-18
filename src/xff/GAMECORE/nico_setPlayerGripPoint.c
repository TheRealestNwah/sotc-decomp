extern void *GetSCRCharaAIWorkPtr(void *);
extern void player_setGripHangPointGeometry(void *, char *);
void nico_setPlayerGripPoint(int actor)
{
    player_setGripHangPointGeometry((void *)actor,
        (char *)GetSCRCharaAIWorkPtr((void *)actor) + 6848);
}