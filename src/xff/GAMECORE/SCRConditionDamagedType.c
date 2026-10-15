extern int *GetDamageClass(void *);
extern int GetDamagerClassDamageSheetType(int *);

int SCRConditionDamagedType(void *actor, int a, int b, int c, int type)
{
    int *d = GetDamageClass(actor);
    if (d[0] != 1)
        goto no;
    if (type != GetDamagerClassDamageSheetType(d))
        goto no;
    return 1;
no:
    return 0;
}
