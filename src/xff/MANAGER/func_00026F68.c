extern int getDrawScreenWidth(void);
extern int getDrawScreenHeight(void);
/* Defined before its caller: as an extern prototype gcc fills the last branch as bnel. */
static int func_00026DB0(float *p)
{
    if (p[0] < 0.0f || p[1] < 0.0f || p[2] < 0.0f || p[3] < 0.0f ||
        p[3] < 0.0f || p[4] < 0.0f || p[5] < 0.0f || p[6] < 0.0f ||
        p[6] < 0.0f || p[7] < 0.0f || p[8] < 0.0f || p[9] < 0.0f ||
        p[9] < 0.0f || p[10] < 0.0f || p[11] < 0.0f || p[12] < 0.0f ||
        4096.0f <= p[0] || 4096.0f <= p[1] || 4096.0f <= p[2] || 4096.0f <= p[3] ||
        4096.0f <= p[3] || 4096.0f <= p[4] || 4096.0f <= p[5] || 4096.0f <= p[6] ||
        4096.0f <= p[6] || 4096.0f <= p[7] || 4096.0f <= p[8] || 4096.0f <= p[9] ||
        4096.0f <= p[9] || 4096.0f <= p[10] || 4096.0f <= p[11] || 4096.0f <= p[12])
        return 1;
    return 0;
}

static inline int allXLess(float *p, float l)
{
    if (p[0] < l && p[2] < l && p[3] < l && p[5] < l && p[6] < l && p[8] < l && p[9] < l && p[11] < l)
        return 1;
    return 0;
}

static inline int allYLess(float *p, float l)
{
    if (p[1] < l && p[3] < l && p[4] < l && p[6] < l && p[7] < l && p[9] < l && p[10] < l && p[12] < l)
        return 1;
    return 0;
}

static inline int allXMore(float *p, float l)
{
    if (l < p[0] && l < p[2] && l < p[3] && l < p[5] && l < p[6] && l < p[8] && l < p[9] && l < p[11])
        return 1;
    return 0;
}

static inline int allYMore(float *p, float l)
{
    if (l < p[1] && l < p[3] && l < p[4] && l < p[6] && l < p[7] && l < p[9] && l < p[10] && l < p[12])
        return 1;
    return 0;
}

static int func_00026F68(float *p)
{
    int left = 0x800 - (getDrawScreenWidth() >> 1);
    int right = (getDrawScreenWidth() >> 1) + 0x800;
    int top = 0x800 - (getDrawScreenHeight() >> 1);
    int bottom = (getDrawScreenHeight() >> 1) + 0x800;

    if (allXLess(p, left) || allYLess(p, top) || allXMore(p, right) || allYMore(p, bottom) ||
        func_00026DB0(p))
        return 1;
    return 0;
}
