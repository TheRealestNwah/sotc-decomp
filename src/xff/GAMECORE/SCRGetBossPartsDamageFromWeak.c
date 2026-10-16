typedef struct {
    int attr;
    char pad04[0x24];
    long weak;
    char pad30[0x28];
} BossParts;

extern char *GetSCRCharaAIWorkPtr(void *);

BossParts *SCRGetBossPartsDamageFromWeak(long weak, void *a)
{
    char *tbl = *(char **)GetSCRCharaAIWorkPtr(a);
    int n = *(int *)(tbl + 0x54);
    BossParts *ret = 0;
    int i;

    for (i = 0; i < n; i++) {
        if (weak == (*(BossParts **)(tbl + 0x10))[i].weak) {
            ret = &(*(BossParts **)(tbl + 0x10))[i];
            break;
        }
    }
    return ret;
}
