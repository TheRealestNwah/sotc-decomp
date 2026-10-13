extern int GAMEUTIL_is_player_obj();
extern void *GetSCRCharaAIWorkPtr(int);

void nico_playerSetAttentionHeadActFlag(int arg0, int arg1)
{
    if (GAMEUTIL_is_player_obj() == 1) {
        (*(int *)((char *)(GetSCRCharaAIWorkPtr(arg0)) + 0x4B0)) = arg1;
    }
}
