extern int *GetDamageClass(void *);

int AI_CheckDamage_Bow(void *self, void *actor)
{
    int *d = GetDamageClass(actor);
    if (d != 0 && d[0] == 3 && (d[24] == 1 || d[24] == 2 || d[24] == 4))
        return 1;
    return 0;
}
