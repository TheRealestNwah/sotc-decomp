/* ~65 word diffs, same size (134 words). Static (alabel): picks the character class motion entry for the object (func_00052A80 lookup, DLD element of the result), shifts cur->prev, copies the class motion params (f8/fC/0x20/f18) and clamps or wraps f8/fC (and clamps f18) against the motion resource frame count (wrap when the entry byte +4 is set). Structure is right; remaining are scheduling (Original hoists the o->cur load between the param copies, reads the compare operand before computing the float limit) and a2-vs-v1 for the index. */
extern int DldSysUndefSymbol;
extern char *GetCharacterClass(int);
extern int GetMotionResourceOriginalFrames(void *);
extern unsigned int *func_00052A80(int, int);

typedef struct {
    int cur;
    int prev;
    float f8;
    float fC;
    char pad10[8];
    float f18;
} MotionOut;

static inline char *resourceElement(unsigned int *h)
{
    unsigned int off = *h & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;
    if (t != 0 && t != (char *)DldSysUndefSymbol) {
        return *(char **)(t + 0x10) + (((unsigned int)*h >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC);
    }
    return 0;
}

#ifdef NONMATCHING
static unsigned int *func_00052C88(int *out, char *obj)
{
    char *cls = GetCharacterClass(*(int *)(obj + 0xD00));
    char *src = cls + 0x1C0;
    int idx = -1;
    unsigned int *res;
    char *elem;
    int frames;
    float lim;
    MotionOut *o = (MotionOut *)out;

    if (*(int *)(obj + 0x750) != 0) {
        idx = *(int *)(*(int *)(obj + 0x750) + 0xC);
    }
    if (idx >= 0) {
        res = func_00052A80(*(int *)(obj + 0x10F8), *(int *)src);
    } else {
        res = 0;
    }
    o->prev = o->cur;
    if (res == 0) {
        o->cur = 0;
    } else {
        o->cur = (int)resourceElement(res);
    }
    if (*(unsigned char *)(obj + 0xD91) == 1 && *(int *)(cls + 0x1070) == 0) {
        o->prev = o->cur;
    }
    *(unsigned char *)(obj + 0xD91) = *(unsigned char *)(cls + 0x1070);
    o->f8 = *(float *)(src + 8);
    o->fC = *(float *)(src + 0xC);
    *(int *)((char *)o + 0x20) = *(int *)(src + 0x20);
    o->f18 = *(float *)(src + 0x18);
    if (o->cur != 0) {
        frames = GetMotionResourceOriginalFrames((char *)o->cur + 0x50);
        if (*((unsigned char *)res + 4) != 0) {
            frames = frames - 1;
            lim = (float)frames;
            if (lim < o->f8) {
                float v = o->f8;
                o->f8 = v - (int)(v / lim) * frames;
            }
            if (lim < o->fC) {
                float v = o->fC;
                o->fC = v - (int)(v / lim) * frames;
            }
        } else {
            lim = (float)frames;
            if (lim < o->f8) {
                o->f8 = lim;
            }
            if (lim < o->fC) {
                o->fC = lim;
            }
            if (lim < o->f18) {
                o->f18 = lim;
            }
        }
    }
    return res;
}
#endif
