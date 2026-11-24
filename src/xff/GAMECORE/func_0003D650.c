/* Boss damage application: scales the incoming hit (hit+0x1C) by func_0003D488's result, caps damage for types 1/2/4 so hp stays above the threshold ratio, resets attack power for types 0/5, adds the pending-hit sum, then signals DEAD_BOSS when hp <= 0. The empty asm keeps the h+0x48 load after the a3 stores, as in the Original. */
extern int playerEnableDeath;
extern int ScrIntrDef_DEAD_BOSS;
extern char *GetDamageClass(void *);
extern char *GetLayoutClass(void *);
extern float func_0003D488(void *, void *, int, float *);
extern void resetAttackPower(void);
extern void scriptIntrSignal(int);


static float func_0003D650(void *obj, char *h, char *hit, float *a3)
{
    int type = *(int *)(GetDamageClass(obj) + 0x60);
    float zero = 0.0f;
    float hp = *(float *)(h + 0x44);

    if (zero < hp) {
        float dmg;
        float diff = *(float *)(hit + 0x1C) - a3[0];
        float max = *(float *)(h + 0x40);
        
        float ratio;
        float lim;
        float tmp;
        float r;

        r = func_0003D488(obj, hit, type, &tmp);
        ratio = hp / max;
        dmg = *(float *)(hit + 0x1C) * r;
        lim = *(float *)(hit + 0x1C) * (1.0f - tmp);
        if (lim < diff) {
            if ((*(long *)(hit + 0x28) & 0xC0000000000000L) != 0 || 0.4f < ratio) {
                float t = diff - lim;
                if (!(dmg < t))
                    dmg = t;
            } else {
                dmg = zero;
            }
        } else {
            dmg = zero;
        }
        if (type == 2 || type == 4 || type == 1) {
            float one = 1.0f - tmp;
            if (ratio <= one) {
                dmg = 0.0f;
            } else if ((hp - dmg) / max <= one) {
                dmg = hp - max * one;
            }
        }
        if (type == 5 || type == 0)
            resetAttackPower();
        a3[1] = dmg;
        a3[0] = a3[0] + dmg;
        __asm__ __volatile__("");
        if (*(int *)(h + 0x48) != 0 && (type == 5 || type == 0)) {
            float t = *(float *)(hit + 0x1C) - a3[0];
            if (0.0f < t) {
                a3[1] = dmg + t;
                a3[0] = *(float *)(hit + 0x1C);
            }
        }
        {
            float sum = 0.0f;
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
    if (hp <= 0.0f) {
        *(float *)(h + 0x44) = 0.0f;
        *(int *)(GetLayoutClass(obj) + 0x1AC) = 1;
        playerEnableDeath = 0;
        scriptIntrSignal(ScrIntrDef_DEAD_BOSS);
    }
    return *(float *)(h + 0x44);
}
