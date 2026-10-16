extern int *GetDamageClass(void *);
extern int GetDamagerClassDamageSheetType(int *);

static inline int checkDamage(void *obj, int type)
{
    int *d = GetDamageClass(obj);

    if ((d != 0) & (d[0] == 1)) {
        if (GetDamagerClassDamageSheetType(d) == type)
            return 1;
    }
    return 0;
}

int AI_CheckDamage_Impact(void *a, void *obj)
{
    return checkDamage(obj, 4);
}
