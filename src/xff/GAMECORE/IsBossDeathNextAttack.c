#define F(p, o) (*(float *)((p) + (o)))
#define L(p, o) (*(unsigned long *)((p) + (o)))

extern float func_0003D488(void *chara, char *param, int type, float *rate);

int IsBossDeathNextAttack(void *chara, char *boss, char *atk, float *ref, int type)
{
    float hp = F(boss, 0x44);
    float max, diff, ratio, lim, dmg, r, t;
    float rate;

    if (hp <= 0.0f) {
        return 0;
    }
    if (!(L(atk, 0x28) & 0xC0000000000000)) {
        return 0;
    }
    diff = F(atk, 0x1C) - *ref;
    max = F(boss, 0x40);
    r = func_0003D488(chara, atk, type, &rate);
    ratio = hp / max;
    lim = F(atk, 0x1C) * (1.0f - rate);
    dmg = F(atk, 0x1C) * r;
    if (lim < diff) {
        if ((L(atk, 0x28) & 0xC0000000000000) || 0.4f < ratio) {
            if (!(dmg < diff - lim)) {
                dmg = diff - lim;
            }
        } else {
            dmg = 0.0f;
        }
    } else {
        dmg = 0.0f;
    }
    if (type == 2 || type == 4 || type == 1) {
        t = 1.0f - rate;
        if (ratio <= t) {
            dmg = 0.0f;
        } else if ((hp - dmg) / max <= t) {
            dmg = hp - max * t;
        }
    }
    if (hp - dmg <= 0.0f) {
        return 1;
    }
    return 0;
}
