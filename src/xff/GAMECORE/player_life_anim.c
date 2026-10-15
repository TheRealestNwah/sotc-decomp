extern unsigned int D_0017B040;
extern void SpriteMenuSetAnimParam(int, int, int, int, float);
extern void func_000BC988(int);

void player_life_anim(int *o)
{
    unsigned int m = D_0017B040;
    if (m != 0) {
        if (m & 1)
            SpriteMenuSetAnimParam(o[1], 3, 0, 1, 0.0f);
        else if (m & 2)
            SpriteMenuSetAnimParam(o[1], 4, 0, 1, 0.0f);
    }
    if ((((unsigned int *)o[1])[2] >> 27) & 0xF) {
        func_000BC988(4);
        o = 0;
    }
}
