extern int *GetDamageClass(void *);
extern int nico_GetCharacterAttackedGPAttr(void *, int);

int SCRConditionDamagedColType(void *actor, int a1, int a2, int a3, int index, long type)
{
    int attr;

    if (*GetDamageClass(actor) == 0) {
        return 0;
    }
    attr = nico_GetCharacterAttackedGPAttr(actor, index);
    if (type != -1)
        return type == attr;
    return attr != 0;
}
