
extern int ScrParam_player_weapon_none;
extern char *GetSCRCharaAIWorkPtr(void *);
extern char *GetCharacterClass(void *);
extern void isysRequestDeleteObj(void *);
extern int SCRSetupWeaponPlayer(void *, int);
extern int is_doing_nico_sight_on(void *);
extern void end_nico_sight_on(void *);

static void func_00078C58(void *o)
{
    char *w = GetSCRCharaAIWorkPtr(o);
    char *e = w + 0x60;

    if (*(void **)(e + 0x4) != 0) {
        if (*(unsigned char *)(e + 0x15) == 0) {
            if (*(int *)(e + 0xC) == 0)
                isysRequestDeleteObj(*(void **)(e + 0x4));
        } else {
            isysRequestDeleteObj(*(void **)(e + 0x4));
        }
        *(void **)(e + 0x4) = 0;
        *(int *)(e + 0xC) = 1;
        *(unsigned char *)(e + 0x15) = 0;
    }
    if (*(void **)(e + 0x0) != 0) {
        if (*(unsigned char *)(e + 0x14) == 0) {
            if (*(int *)(e + 0x8) == 0)
                isysRequestDeleteObj(*(void **)(e + 0x0));
        } else {
            isysRequestDeleteObj(*(void **)(e + 0x0));
        }
        *(void **)(e + 0x0) = 0;
        *(int *)(e + 0x8) = 1;
        *(unsigned char *)(e + 0x14) = 0;
    }
    if (*(int *)(GetCharacterClass(o) + 0x111C) != ScrParam_player_weapon_none && *(int *)(e + 0x18) == 0)
        *(int *)(e + 0x18) = SCRSetupWeaponPlayer(o, *(int *)(e + 0x10));
    e = w + 0x190;
    if (is_doing_nico_sight_on(e) == 1)
        end_nico_sight_on(e);
}
