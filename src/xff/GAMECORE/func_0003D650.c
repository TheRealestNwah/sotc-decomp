/* ~116 diffs, same length (156 words). Boss damage application: scales incoming hit (hit+0x1C) against a limit from func_0003D488, caps damage for types 1/2/4 so hp stays above the threshold ratio, resets attack power for types 0/5, adds the pending-hit sum, then signals DEAD_BOSS when hp <= 0. The original keeps 0.0 in f24 across the whole function (zero local gets it from 140 to 116) and orders the incoming args as s1=h, s2=hit, s3=a3; ours still swaps registers around the func_0003D488 call. */
extern int playerEnableDeath;
extern int ScrIntrDef_DEAD_BOSS;
extern char *GetDamageClass(void *);
extern char *GetLayoutClass(void *);
extern void func_0003D488(void *, void *, int, float *);
extern void resetAttackPower(void);
extern void scriptIntrSignal(int);

#ifdef NONMATCHING
float func_0003D650(void *obj, char *h, char *hit, float *a3)
{
    int type = *(int *)(GetDamageClass(obj) + 0x60);
    float zero = 0.0f;
    float hp = *(float *)(h + 0x44);

    if (zero < hp) {
        float dmg = zero;
        float diff = *(float *)(hit + 0x1C) - a3[0];
        float max = *(float *)(h + 0x40);
        float f4;
        float ratio;
        float lim;
        float tmp;

        func_0003D488(obj, hit, type, &tmp);
        f4 = tmp;
        ratio = hp / max;
        lim = *(float *)(hit + 0x1C) * (1.0f - f4);
        if (lim < diff) {
            if ((*(long *)(hit + 0x28) & 0xC0000000000000L) != 0 || 0.4f < ratio) {
                float t = diff - lim;
                dmg = *(float *)(hit + 0x1C) * a3[0];
                if (dmg < t)
                    dmg = t;
            } else {
                dmg = zero;
            }
        }
        if (type == 2 || type == 4 || type == 1) {
            float one = 1.0f - f4;
            if (ratio <= one) {
                dmg = zero;
            } else if ((hp - dmg) / max <= one) {
                dmg = hp - max * one;
            }
        }
        if (type == 5 || type == 0)
            resetAttackPower();
        a3[1] = dmg;
        a3[0] = a3[0] + dmg;
        if (*(int *)(h + 0x48) != 0 && (type == 5 || type == 0)) {
            float t = *(float *)(hit + 0x1C) - a3[0];
            if (zero < t) {
                a3[1] = dmg + t;
                a3[0] = *(float *)(hit + 0x1C);
            }
        }
        {
            float sum = zero;
            int n = *(int *)(h + 0x54);
            if (n > 0) {
                float *p = (float *)(*(char **)(h + 0xE8) + 0x24);
                do {
                    sum += *p;
                    p += 2;
                } while (--n);
            }
            hp = *(float *)(h + 0x40) - sum;
        }
    }
    *(float *)(h + 0x44) = hp;
    if (hp <= zero) {
        *(float *)(h + 0x44) = zero;
        *(int *)(GetLayoutClass(obj) + 0x1AC) = 1;
        playerEnableDeath = 0;
        scriptIntrSignal(ScrIntrDef_DEAD_BOSS);
    }
    return *(float *)(h + 0x44);
}
#endif
