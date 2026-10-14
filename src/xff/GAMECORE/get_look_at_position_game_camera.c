typedef int s128 __attribute__((mode(TI)));

void get_look_at_position_game_camera(char *dst, char *src)
{
    *(s128 *)(dst + 0x0) = *(s128 *)(src + 0x13E0);
}
