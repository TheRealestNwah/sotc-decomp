extern void *GetCharacterClass(void *);

void DebugDispTargetStatusForce(void *a, void *t)
{
    void *c = GetCharacterClass(t);
    c = 0;
}
