extern int isysGetThisSubThread(void);
extern int func_000B7B08(char *, char *);

#define F(o) (*(float *)(w + (o)))
#define I(o) (*(int *)(w + (o)))
#define P(o) (*(char **)(w + (o)))

static inline int isNear(char *w)
{
    return F(0x114) <= F(0x30) * 0x1.999998p-1f;
}

static inline int isFront(char *w)
{
    return F(0x120) >= 0x1.6a09e2p-1f;
}

static inline int isClose(char *w)
{
    if (F(0xB0) < 10.0f && F(0x1A0) > 1.0f)
        return 1;
    {int r = 0; if (F(0xB0) < 5.0f) r = 1; return r;}
}

static inline int isFar(char *w)
{
    return F(0xB0) >= 10.0f;
}

static inline int canSee(char *w)
{ if (I(0x244) != 0 && F(0x1D0) > 0.0f) return 1; return 0; }

static inline int isStraight(float x)
{ if (x < 0.0f) { if (!(x < -0x1.fae146p-1f)) goto one; } else if (!(x > 0x1.fae146p-1f)) goto one; return 0; one: return 1; }

static inline int isDiag(float x)
{ if (x < 0.0f) { if (!(x <= -0x1.6a09e6p-1f)) goto zero; } else if (!(0x1.6a09e6p-1f <= x)) goto zero; return 1; zero: return 0; }

static inline int dirL(char *w, char *d){ if (I(0x244) != 0) { if (isDiag(F(0x1F4))) return F(0x1C4) < 0.0f; return 0; } return *(float *)(d + 0x48) + F(0x34) <= 0.0f; }
static inline int dirR(char *w, char *d){ if (I(0x244) != 0) { if (isDiag(F(0x1F4))) return F(0x1C4) > 0.0f; return 0; } return *(float *)(d + 0x48) - F(0x34) >= 0.0f; }
static inline int canApproach(char *w)
{
    int r;
    isysGetThisSubThread();
    if (F(0xB0) < 5.0f) { r = 0; if (!(F(0x1A0) > 1.0f) && 0x1.ccccccp-1f <= F(0xBC)) r = 1; }
    else { r = 0; if (F(0xB0) < 10.0f && -0.5f <= F(0xBC)) r = 1; }
    return r;
}

#define timeUp(w) (F(0x18C) > F(0x188))

static inline int inRange(char *w)
{
    int r = 0;
    if (F(0x264) <= F(0x260))
        r = F(0x210) <= *(float *)(P(0x64) + 0x14) * F(0x260);
    return r;
}

static void func_000B7C58(char *w)
{
    isysGetThisSubThread();
    switch (I(0x158)) {
    case 3:
        if (isClose(w))
            I(0x164) = 7;
        else if (timeUp(w))
            I(0x164) = 1;
        break;
    case 4:
        if (isClose(w))
            I(0x164) = 7;
        else if (inRange(w))
            I(0x164) = 3;
        break;
    case 1:
        if (isNear(w) || isFront(w)) {
            if (isClose(w)) {
                if (canSee(w)) {
                    if (isStraight(F(0x1F4)))
                        I(0x164) = 9;
                    else
                        I(0x164) = 0xA;
                } else if (canApproach(w)) {
                    I(0x164) = 6;
                } else {
                    I(0x164) = 7;
                }
            } else if (canSee(w)) {
                if (isStraight(F(0x1F4)))
                    I(0x164) = 8;
                else if (*(int *)(P(0x64) + 0xC) != 0)
                    I(0x164) = 0xA;
            } else if (*(int *)(P(0x64) + 0xC) != 0 && func_000B7B08(w, w + 0xD0)) {
                I(0x164) = 0xA;
            } else if (F(0x188) < F(0x18C) && isNear(w)) {
                if (F(0x180) < F(0x184) && I(0x2F4) == 0)
                    I(0x164) = 4;
                else if (*(int *)(P(0x64) + 0xC) != 0)
                    I(0x164) = 0xA;
            }
        } else {
            I(0x164) = 2;
        }
        break;
    case 2:
        I(0x164) = 1;
        break;
    case 6:
        if (isFar(w))
            I(0x164) = 1;
        else
            I(0x164) = 7;
        break;
    case 7:
        if (isNear(w) || isFront(w)) {
            if (isFar(w)) {
                if (canSee(w)) {
                    if (isStraight(F(0x1F4)))
                        I(0x164) = 8;
                    else if (*(int *)(P(0x64) + 0xC) != 0)
                        I(0x164) = 0xA;
                } else
                    I(0x164) = 1;
            } else if (canSee(w)) {
                if (isStraight(F(0x1F4)))
                    I(0x164) = 9;
                else if (*(int *)(P(0x64) + 0xC) != 0)
                    I(0x164) = 0xA;
            } else if (canApproach(w)) {
                I(0x164) = 6;
            }
        } else {
            I(0x164) = 6;
        }
        break;
    case 8:
        I(0x164) = 1;
        break;
    case 9:
        I(0x164) = 1;
        break;
    case 10:
        I(0x164) = 0xC;
        break;
    case 12: {
        char *d = w + 0xD0;
        if (dirL(w, d) && I(0x174) == 0x14) { I(0x164) = 0xD; break; }
        if (dirR(w, d) && I(0x174) == 0x13) I(0x164) = 0xB;
        else if (F(0x188) < F(0x18C)) I(0x164) = 0xB;
        break;
    }
    case 11:
        I(0x164) = 1;
        break;
    case 13:
        I(0x164) = 0xC;
        break;
    case 14:
        if (timeUp(w))
            I(0x164) = 0xF;
        break;
    }
}
