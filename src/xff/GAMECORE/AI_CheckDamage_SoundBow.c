extern int *GetDamageClass(void *);

int AI_CheckDamage_SoundBow(void *self, void *actor)
{
    int *d = GetDamageClass(actor);
    if (d != 0 && d[0] == 3 && d[24] == 3)
        return 1;
    return 0;
}
