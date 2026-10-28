extern int GAMEUTIL_is_player_obj(void *);
extern void *GetSCRCharaAIWorkPtr(int);

void nico_playerSetAttentionHeadActFlag(int arg0, int arg1)
{
    if (GAMEUTIL_is_player_obj((void *)arg0) == 1) {
        (*(int *)((char *)(GetSCRCharaAIWorkPtr(arg0)) + 0x4B0)) = arg1;
    }
}
