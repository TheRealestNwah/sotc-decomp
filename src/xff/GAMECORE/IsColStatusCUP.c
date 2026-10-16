extern char *GetLayoutClass(void *);
extern char *GetCharacterClass(void *);

int IsColStatusCUP(void *o, long m1, long m2)
{
    if (o != 0) {
        char *lc = GetLayoutClass(o);
        char *cc = GetCharacterClass(o);
        if (*(int *)(lc + 0x124) != 0 && (*(long *)(cc + 0x690) & m1 & m2) != 0) return 1;
    }
    return 0;
}
