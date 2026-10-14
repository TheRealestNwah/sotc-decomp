extern void *GetCharacterClass(void *);
extern void *GetLayoutClass(void *);

#define NULL ((void *)0)
extern void *GetGeometryPointerObject(void *);

void CharaCtrlResetAllScriptCtrlStatus(void *arg0) {
    void *temp_v0;
    void *temp_v0_2;
    void *var_s0;
    void *var_v0;

    var_v0 = GetCharacterClass(arg0);
    if (var_v0 == NULL) {
        var_s0 = NULL;
        temp_v0 = GetLayoutClass(arg0);
        if ((*(int *)((char *)(temp_v0) + 0x124)) != 0) {
            temp_v0_2 = GetGeometryPointerObject(temp_v0 + 0xC0);
            if ((*(unsigned char *)((char *)(temp_v0_2) + 8)) == 0x16) {
                var_s0 = GetCharacterClass(temp_v0_2);
            }
        }
        var_v0 = var_s0;
        if (var_v0 != NULL) {
            goto block_5;
        }
    } else {
block_5:
        (*(long *)((char *)(var_v0) + 0x920)) = 0;
    }
}
