/* Parked: 22 diffs. Motion-shift step for one entry of the character class motion table: resolves the info relocatable ref to the current motion resource, decides from info->xC whether the shift fires, then either leaves the old motion (callbacks, two CallMotShiftCallBackElemLeaveFunc calls, ReleaseCharacterClassAddMotSyncAnim, func_00051A60) or restarts it (func_00051958), runs info->fn and sets the blend frames. One pointer `p` walks the two leave callbacks at mot+0xA8 and is then reused for class+0x2C8, which puts that in $s0 like the Original (25 before). Remaining: prologue argument spills and register choice for the ref decode and the tab[i].xC limit. The `long` return type came from a 25-minute permuter run (27 diffs with `int`); the Original most likely returns int. */
#ifdef NONMATCHING
typedef struct {
    char pad0[4];
    char *mot;
    char pad8[4];
    float xC;
    char pad10[0x1C];
    float x2C;
    char pad30[0x14];
    int x44;
    char pad48[8];
    float x50;
    float x54;
    char pad58[0x28];
} MotEntry;

typedef struct {
    char pad0[8];
    unsigned int ref;
    float xC;
    float x10;
    void (*fn)(int);
} MotInfo;

extern int DldSysUndefSymbol;
extern char *GetCharacterClass(int);
extern void CallMotShiftCallBackElemLeaveFunc(void *, void *, int);
extern void ReleaseCharacterClassAddMotSyncAnim(void *);
extern float GetMotionResourceOriginalFrames(int);
extern void func_00051958(MotEntry *, char *);
extern void func_00051A60(int, char *, int, int, float);

long func_00053058(int obj, int idx, MotInfo *info_, int res, float f)
{
    register MotInfo *info __asm__("$23") = info_;
    volatile int vidx;
    char *volatile vcls;
    volatile int ret;
    char *cls;
    MotEntry *tab;
    MotEntry *ent;
    unsigned int *rp;
    unsigned int ref;
    unsigned int off;
    char *r;
    int cur;
    void (*fn)(int);
    register char *chr __asm__("$22");
    char *mot;
    int i;
    int n;
    float lim;
    int changed;
    int stopped;
    int fr;
    char *p;

    vidx = idx;
    cls = GetCharacterClass(obj);
    vcls = cls;
    rp = &info->ref;
    i = vidx;
    tab = *(MotEntry **)(cls + 0x30C);
    ref = *rp;
    off = ref & 0x3FFFF;
    lim = tab[i].xC;
    if (off != 0)
        r = *(char **)((char *)rp - off);
    else
        r = 0;
    cur = 0;
    if (r != 0 && (int)r != DldSysUndefSymbol)
        cur = *(int *)(r + 0x10) + ((ref >> 18) & 0xFFF) * *(int *)(*(char **)(r + 8) + 0xC);
    ent = &tab[i];
    changed = res != cur;
    stopped = ent->x44 == -1;
    ret = 0;
    if (info->xC < 0.0f) {
        if (stopped)
            ret = 1;
    } else if (info->xC * ent->x2C < lim) {
        ret = 1;
    }
    if (ret != 0) {
        fn = info->fn;
        if (changed) {
            chr = GetCharacterClass(obj);
            mot = ent->mot;
            ent->x44 = -2;
            p = mot + 0xA8;
            for (n = 1; n >= 0; n--) {
                if (*(void (**)(int))p != 0)
                    (*(void (**)(int))p)(obj);
                p += 4;
            }
            p = chr + 0x2C8;
            CallMotShiftCallBackElemLeaveFunc(p, mot, obj);
            CallMotShiftCallBackElemLeaveFunc(p, mot, obj);
            ReleaseCharacterClassAddMotSyncAnim(ent);
            func_00051A60(obj, vcls, vidx, cur, f);
        } else {
            func_00051958(&tab[i], tab[i].mot);
        }
        if (fn != 0)
            fn(obj);
        if (info->x10 == 0.0f) {
            ent->x50 = 0.0f;
            ent->x54 = 1.0f;
        } else {
            fr = cur != 0 ? cur + 0x50 : 0;
            if (fr != 0)
                GetMotionResourceOriginalFrames(fr);
            lim = info->x10 * ent->x2C;
            ent->x54 = 0.0f;
            ent->x50 = lim;
        }
    }
    return ret;
}
#endif
