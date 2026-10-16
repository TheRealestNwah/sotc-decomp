typedef struct {
    int attr;
    char pad04[0x24];
    long weak;
    char pad30[0x28];
} BossParts;

extern char *GetSCRCharaAIWorkPtr(void *);

char *SCRGetBackStageBossPartsDamageFromColAttr(int attr, void *a)
{
    char *tbl = *(char **)GetSCRCharaAIWorkPtr(a);
    int n = *(int *)(tbl + 0x54);
    char *ret = 0;
    int i;

    attr &= 0x3F0;
    for (i = 0; i < n; i++) {
        if (attr == (*(BossParts **)(tbl + 0x10))[i].attr) {
            ret = *(char **)(tbl + 0xE8) + i * 8 + 0x24;
            break;
        }
    }
    return ret;
}
