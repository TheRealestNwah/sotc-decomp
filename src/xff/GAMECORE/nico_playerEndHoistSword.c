extern char *GetSCRCharaAIWorkPtr(void *);
extern int is_doing_nico_sight_on(void *);
extern void end_nico_sight_on(void *);

void nico_playerEndHoistSword(void *actor)
{
    char *s = GetSCRCharaAIWorkPtr(actor) + 0x190;
    if (is_doing_nico_sight_on(s) == 1)
        end_nico_sight_on(s);
}
