extern void SetCharacterObjCollisionProcFlag(void *, int);

void gextailStopColProc(void *actor)
{
    SetCharacterObjCollisionProcFlag(actor, 0);
}
