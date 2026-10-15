extern char *GetLayoutClass(void *);
extern char *GetCharacterClass(void *);

int IsColStatus(void *o, unsigned long mask, unsigned long val)
{
    if (o != 0) {
        char *l = GetLayoutClass(o);
        char *c = GetCharacterClass(o);
        if (*(int *)(l + 0x124) != 0 && (*(unsigned long *)(c + 0x690) & mask) == val)
            return 1;
    }
    return 0;
}
