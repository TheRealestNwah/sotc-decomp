typedef int s128 __attribute__((mode(TI)));

extern s128 D_00179AF0;

void GAMEUTIL_set_custom_boss_interest_position(s128 *v)
{
    D_00179AF0 = *v;
}
