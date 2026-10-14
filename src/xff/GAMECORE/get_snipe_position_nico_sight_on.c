typedef int s128 __attribute__((mode(TI)));

void get_snipe_position_nico_sight_on(char *dst, char *src)
{
    *(s128 *)(dst + 0x0) = *(s128 *)(src + 0x1C0);
}
