typedef struct {
    float hp;
    float hp_shown;
    float hp_target;
    int timer;
} BossLifeBar;

extern BossLifeBar D_0017B050;
extern float D_0017B064;

void bosslifebar_resethp(float max_hp, float hp)
{
    BossLifeBar *bar = &D_0017B050;
    float ratio = hp / max_hp;

    bar->timer = 0;
    D_0017B064 = max_hp * 0.01f;
    bar->hp_target = ratio;
    bar->hp_shown = ratio;
    bar->hp = ratio;
}
