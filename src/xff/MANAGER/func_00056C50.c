/*
 * Parked: 4 diffs. Static, called from GetMainAnimation (same Original
 * source file, declared static in GetMainAnimation.c). A copy loop that
 * increments i before its byte-offset loads, with the pointers declared
 * da, sa, db, sb, gives the Original's base registers.
 * Remaining: the 0x724 load is scheduled after the 0x43C store and the
 * i = 0 move (and lands in $f1).
 */
#ifdef NONMATCHING
extern int DldSysUndefSymbol;
extern char *GetCharacterClass(int);
extern unsigned char *func_00052C88(void *, char *, float);
extern void func_00052170(char *, float);
extern int func_00056A78(int, float);
extern void func_00052288(char *, float);
extern void ResetAnimeFrameTableInfo(void *, void *, void *);

#define F(p, o) (*(float *)((char *)(p) + (o)))
#define I(p, o) (*(int *)((char *)(p) + (o)))
#define U8(p, o) (*(unsigned char *)((char *)(p) + (o)))
#define S8(p, o) (*(signed char *)((char *)(p) + (o)))

static inline char *resolveHandle(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;

    return (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
}

static int func_00056C50(int id, float dt)
{
    char *c = GetCharacterClass(id);
    int r = 0;
    int mode = U8(c, 0xD90);

    switch (mode) {
    case 1: {
        char *src;
        int i;
        r = func_00052C88(c + 0x1C0, c, dt) != 0;
        src = GetCharacterClass(I(c, 0xD00));
        I(c, 0x728) = 0;
        I(c, 0x43C) = 0;
        F(c, 0x724) = F(src, 0x724);
        F(c, 0x720) = F(src, 0x720);
        U8(c, 0x360) = U8(src, 0x360);
        F(c, 0x744) = F(src, 0x744);
        F(c, 0x740) = F(src, 0x740);
        U8(c, 0xC40) = U8(src, 0xC40);
        {
            int *da = (int *)(c + 0xC44);
            int *sa = (int *)(src + 0xC44);
            int *db = (int *)(c + 0xC48);
            int *sb = (int *)(src + 0xC48);
            i = 0;
            do {
                int o = i * 8;
                i++;
                *(int *)((char *)da + o) = *(int *)((char *)sa + o);
                *(int *)((char *)db + o) = *(int *)((char *)sb + o);
                __asm__("" : "+r"(i));
            } while (i <= 0);
        }
        break;
    }
    case 0:
    case 2:
        func_00052170(c, dt);
        r = func_00056A78(id, dt) != 0;
        func_00052288(c, dt);
        if (mode == 2) {
            int *d = (int *)(c + 0xD20);
            unsigned char *p = func_00052C88(d, c, dt);
            int flag;
            float len;
            r = p != 0;
            flag = 0;
            if (p != 0)
                flag = p[5];
            {
                int changed = d[1] != d[0];
                S8(c, 0xD80) = U8(c, 0x360);
                if (changed || flag != 0) {
                I(c, 0x734) = 0;
                F(c, 0x738) = F(d, 0x28) * 10.0f;
            }
            }
            len = F(c, 0x738);
            if (len <= 0.0f)
                F(c, 0x734) = 1.0f;
            else {
                float t = F(c, 0x734) + dt * 30.0f / len;
                F(c, 0x734) = t;
                if (1.0f < t) {
                    F(c, 0x734) = 1.0f;
                    F(c, 0x738) = -1.0f;
                }
            }
        }
        break;
    }
    if (S8(c, 0xD80) != 0) {
        char **dd = (char **)(c + 0xD20);
        if (U8(c, 0xD90) == 2) {
            char *cls = *dd;
            if (cls != 0)
                ResetAnimeFrameTableInfo((char *)dd + 0x30, resolveHandle((unsigned int *)(cls + 0x48)), resolveHandle((unsigned int *)(cls + 0x4C)));
        }
    }
    return r;
}
#endif
