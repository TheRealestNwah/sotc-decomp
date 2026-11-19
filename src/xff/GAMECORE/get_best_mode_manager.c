typedef unsigned int u_long128 __attribute__((mode(TI)));

extern int *DldSysUndefSymbol;
extern int get_base_default_direction(void *, void *, void *, void *, void *, void *, void *, void *, void *);
extern int GAMEUTIL_get_yaw_pitch_by_direction(float *, float *, void *);
extern float GAMEUTIL_increase_yaw(void *, float, float);
extern float GAMEUTIL_increase_pitch_limit_clip(void *, void *, float, float, float, float);
extern void GAMEUTIL_get_direction_by_yaw_pitch(void *, float, float);

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return (t != 0 && t != DldSysUndefSymbol) ? (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}

static inline float dotXYZ(void *a, void *b)
{
    float r;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vaddw.x vf7, vf0, vf0w\n"
                         "vmul.xyz vf6, vf5, vf6\n"
                         "vaddax.x ACC, vf0, vf6x\n"
                         "vmadday.x ACC, vf7, vf6y\n"
                         "vmaddz.x vf6, vf7, vf6z\n"
                         "qmfc2.ni $2, vf6\n"
                         "mtc1 $2, %0\n"
                         : "=f"(r) : "r"(a), "r"(b) : "$2");
    return r;
}

char *get_best_mode_manager(char *list, char *a1, char *a2)
{
    char *mgr[2];
    u_long128 ref[1];
    u_long128 dir[1];
    float yaw;
    float pitch;
    char *cur;
    int multi = 0;
    int n = 0;
    int i;
    char *best = 0;
    float max;

    for (i = 0; i < 2; i++) {
        mgr[i] = dldResolve((unsigned int *)(list + 0x3C) + i);
        if (mgr[i] != 0)
            n++;
    }
    if (n >= 2)
        multi = 1;
    else if (n <= 0)
        __asm__ __volatile__("break 0");

    if (multi == 1) {
        *(u_long128 *)&ref = *(u_long128 *)(a2 + 0xC0);
        cur = *(char **)(a1 + 0x664);
        max = -2.0f;
        for (i = 0; i < 2; i++) {
            char *m = mgr[i];
            char *prm;
            int r;
            float d;
            if (m == 0)
                continue;
            prm = dldResolve(*(unsigned int **)(m + 0x14));
            if (m == cur) {
                best = m;
                break;
            }
            r = get_base_default_direction((void *)&dir, 0, 0, 0, 0, 0, 0, prm, a2);
            if (best == 0)
                best = m;
            if (r != 1)
                continue;
            if (GAMEUTIL_get_yaw_pitch_by_direction(&yaw, &pitch, (void *)&dir) != r)
                continue;
            {
                float z = 0.0f;
                __asm__("" : "+f"(z));
                if (*(int *)(prm + 0xA8) == 1)
                    pitch = z;
            }
            yaw = GAMEUTIL_increase_yaw(0, yaw, *(float *)(prm + 0xC8) * 0.0174532925f);
            pitch = GAMEUTIL_increase_pitch_limit_clip(0, 0, pitch, *(float *)(prm + 0xCC) * 0.0174532925f,
                                                       *(float *)(prm + 0xAC) * 0.0174532925f,
                                                       *(float *)(prm + 0xB0) * 0.0174532925f);
            GAMEUTIL_get_direction_by_yaw_pitch((void *)&dir, yaw, pitch);
            d = dotXYZ((void *)&dir, (void *)&ref);
            if (max < d) {
                best = m;
                max = d;
            }
        }
    } else {
        for (i = 0; i < 2; i++) {
            if (mgr[i] != 0) {
                best = mgr[i];
                break;
            }
        }
    }
    return best;
}
