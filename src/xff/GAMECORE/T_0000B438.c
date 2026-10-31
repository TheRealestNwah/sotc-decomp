extern void *GAMEUTIL_get_boss_obj(void);
extern void GAMEUTIL_set_auto_get_flag_boss_interest_position(int);
extern void scrRun(void);

static void T_0000B438(void)
{
    for (;;) {
        if (GAMEUTIL_get_boss_obj() == 0) {
            GAMEUTIL_set_auto_get_flag_boss_interest_position(1);
        }
        scrRun();
    }
}
