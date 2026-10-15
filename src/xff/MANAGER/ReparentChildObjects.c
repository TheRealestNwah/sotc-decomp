extern void *GetLayoutClass(void *);
extern void *GetCharacterClass(void *);
extern void ReparentCharacterObj(void *);

void ReparentChildObjects(void *o)
{
    if (GetLayoutClass(o) != 0 && GetCharacterClass(o) != 0) {
        ReparentCharacterObj(o);
        o = 0;
    }
}
