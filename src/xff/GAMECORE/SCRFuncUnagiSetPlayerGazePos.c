typedef int s128 __attribute__((mode(TI)));

extern void *GetSCRCharaAIWorkPtr(void *);
extern void GAMEUTIL_set_custom_boss_interest_position(s128 *v);
extern void GAMEUTIL_set_auto_get_flag_boss_interest_position(int arg0);

void SCRFuncUnagiSetPlayerGazePos(void *actor)
{
    GAMEUTIL_set_custom_boss_interest_position((s128 *)((char *)GetSCRCharaAIWorkPtr(actor) + 0x5AF0));
    GAMEUTIL_set_auto_get_flag_boss_interest_position(0);
}
