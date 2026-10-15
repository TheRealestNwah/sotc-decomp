extern char InitialGeometryPointer[];
extern char *GetCharacterClass(void *);
extern void SendCharaAttackMsg(void *, void *, void *, int, float);

void nico_SendPlayerFallDownDamageMail(void *actor)
{
    void *g = InitialGeometryPointer;
    char *c = GetCharacterClass(actor);
    SendCharaAttackMsg(actor, actor, g, -3, *(float *)(c + 0x51C));
}
