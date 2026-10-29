extern void *GetCharacterClass(void *);
void ChangeCharacterObjControlTarget(void *object, int target)
{
    *(int *)((char *)GetCharacterClass(object) + 0x950) = target;
}
