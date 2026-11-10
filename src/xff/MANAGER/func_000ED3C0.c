#ifdef NONMATCHING
/* 146 diffs, same length (152 words). Draft from the asm (MANAGER): weighted random pick from a dld ref array of {ref, weight} 8-byte entries ending at a null ref. Non-negative weights are subtracted from 100.0, negative ones share the remainder equally; a 16-bit rand scaled by 1/65536 is compared against the cumulative weight * 0.01 and the matching entry is returned (an assert string, euc-jp, fires if the entry resolves to the array itself). Same dld helpers as func_000AE758. Differences: the Original keeps only three callee-saved registers (neg count, entry count and the array in $s0-$s2, with the second-loop entry pointer reusing the neg register) and no extra float saves; ours needs a fourth ($s3) for the entry pointer. Candidates: reuse the neg variable as the pointer, or merge n/i. Not yet permuted. */
extern int *DldSysUndefSymbol;

static inline char *dldBase(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    return t != 0 && t != DldSysUndefSymbol ? (char *)t[4] : 0;
}

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    if (t != 0 && t != DldSysUndefSymbol)
        return (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3];
    return 0;
}

extern int rand(void);
extern void iosJumpRecoverPoint(char *);

char *func_000ED3C0(unsigned int *ref)
{
    char *arr = dldResolve(ref);
    unsigned int *p;
    float rest = 100.0f;
    int n = 0;
    int neg = 0;
    int i;

    for (p = (unsigned int *)arr; dldResolve(p) != 0; p += 2, n++) {
        float w = *(float *)(p + 1);

        if (w < 0.0f)
            neg++;
        else
            rest -= w;
    }
    {
        float r = (float)(rand() & 0xFFFF) * (1.0f / 65536.0f);
        float share = 0.0f;
        float acc = 0.0f;

        if (0.0f <= rest && neg != 0 && !(rest < 0.0f))
            share = rest / (float)neg;
        p = (unsigned int *)arr;
        for (i = 0; i < n; i++, p += 2) {
            float w = *(float *)(p + 1);

            acc += (w < 0.0f ? share : w) * 0.01f;
            if (r < acc) {
                if (dldResolve(p) == arr)
                    iosJumpRecoverPoint("\274\253\270\312\273\262\276\310\244\362\244\267\244\306\244\353\n");
                return (char *)p;
            }
        }
    }
    return arr;
}
#endif
