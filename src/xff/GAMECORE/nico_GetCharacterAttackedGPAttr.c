extern char *GetDamageClass(void *);
extern long GetGeometryPointerCharColAttr(void *);
long nico_GetCharacterAttackedGPAttr(void *actor, long mask)
{
    char *damage=GetDamageClass(actor);
    if (*(int *)damage == 3) return GetGeometryPointerCharColAttr(damage + 0x10) & mask;
    return 0;
}
