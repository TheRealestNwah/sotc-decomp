extern int D_0017B060;
extern void SpriteMenuSetAnimParam(int, int, int, int, float);

void boss_life_anim(int *p)
{
    if (D_0017B060 != 0)
        SpriteMenuSetAnimParam(p[1], 3, 0, 1, 0.0f);
}
