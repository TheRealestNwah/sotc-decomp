extern char InitialGeometryPointer[];
extern float player_GetBoundDamageLevel(void *);
extern void SendCharaAttackMsg(void *, void *, void *, float, int);

void nico_SendPlayerBoundDamageMail(void *actor)
{
    void *g = InitialGeometryPointer;
    float d = player_GetBoundDamageLevel(actor);
    SendCharaAttackMsg(actor, actor, g, d, -4);
}
