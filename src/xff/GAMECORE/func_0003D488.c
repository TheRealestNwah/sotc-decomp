typedef struct {
    char pad0[0x5C];
    float level;
} DamageClass;

extern float getPlayerMaxGripRatio(void);
extern float getNowPowerRatio(void);
extern float gStatGetPlayerAccessoriesDamgeRaitoToBoss(void);
extern DamageClass *GetDamageClass(void *);

static float func_0003D488(void *chara, float *param, int type, float *rate)
{
    float damage = 0.0f;
    float r = damage;

    switch (type) {
    case 5:
        damage = param[1];
        damage *= getPlayerMaxGripRatio();
        if (GetDamageClass(chara)->level == 2.0f)
            damage *= 0.5f;
        else if (GetDamageClass(chara)->level == 3.0f)
            damage *= 3.0f;
        r = 1.0f;
        break;
    case 0:
        damage = param[1];
        damage *= getNowPowerRatio();
        if (GetDamageClass(chara)->level == 2.0f)
            damage *= 0.5f;
        else if (GetDamageClass(chara)->level == 3.0f)
            damage *= 3.0f;
        r = 1.0f;
        break;
    case 2:
        damage = param[3];
        r = 0.8f;
        break;
    case 4:
        damage = param[4];
        r = 0.8f;
        break;
    case 3:
        damage = 0.0f;
        r = damage;
        break;
    case 1:
        damage = param[2];
        if (GetDamageClass(chara)->level > 0.0f)
            damage *= 0.5f;
        r = 0.2f;
        break;
    case -1:
        damage = param[1];
        r = 1.0f;
        break;
    }
    *rate = r;
    return damage * gStatGetPlayerAccessoriesDamgeRaitoToBoss();
}
