extern void SetCharacterObjCollisionProcFlag(void *, int);

void gextailStartColProc(void *actor)
{
    SetCharacterObjCollisionProcFlag(actor, 1);
}
