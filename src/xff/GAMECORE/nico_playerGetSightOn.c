extern int GAMEUTIL_is_player_obj(void *);
extern int GetSCRCharaAIWorkPtr(int);

int nico_playerGetSightOn(int arg0)
{
    if (GAMEUTIL_is_player_obj((void *)arg0) == 1) {
        return GetSCRCharaAIWorkPtr(arg0) + 0x190;
    }
    return 0;
}
