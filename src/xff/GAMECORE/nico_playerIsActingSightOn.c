extern int GAMEUTIL_is_player_obj();
extern int GetSCRCharaAIWorkPtr(int);
extern int is_doing_nico_sight_on(int);

int nico_playerIsActingSightOn(int arg0)
{
    if (GAMEUTIL_is_player_obj() == 1) {
        return is_doing_nico_sight_on(GetSCRCharaAIWorkPtr(arg0) + 0x190);
    }
    return 0;
}
