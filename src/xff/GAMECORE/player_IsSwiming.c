extern int GAMEUTIL_is_swimming_now(void *);
int player_IsSwiming(void *actor)
{
    return GAMEUTIL_is_swimming_now(actor);
}
