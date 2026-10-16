extern char InitialGeometryPointer[];
extern void SendCharaAttackMsg(void *, void *, void *, int, float);

void nico_SendSuicideMail(void *a)
{
    SendCharaAttackMsg(a, a, InitialGeometryPointer, -3, 65535.0f);
}
