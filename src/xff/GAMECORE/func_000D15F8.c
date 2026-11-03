typedef int s128 __attribute__((mode(TI)));

typedef struct {
    char pad0[0x41CC];
    void *volume;
} CharaAIWork;

extern CharaAIWork *GetSCRCharaAIWorkPtr(void *);
extern char *GetCharacterClass(void *);
extern int equipmentInvisibilityCloak(void);
extern char *getSCRDataCtrlWork(void *);
extern int CheckPositionInsideOfJudgeVolumeObject(void *, void *, void *, s128 *);
extern void GetVolumeClippedTargetPos(s128 *, void *, void *, s128 *);
extern int SkelFocusDef_BOSS_OPT_ATTACK;
extern void func_000D2438(void *, s128 *, int);

static inline void focusClipped(void *obj, CharaAIWork *ai, s128 *p, char *work)
{
    s128 *q;

    if (CheckPositionInsideOfJudgeVolumeObject(work, obj, ai->volume, p)) {
        func_000D2438(obj, p, SkelFocusDef_BOSS_OPT_ATTACK);
    } else {
        q = (s128 *)(work + 0x60);
        GetVolumeClippedTargetPos(q, obj, ai->volume, p);
        func_000D2438(obj, q, SkelFocusDef_BOSS_OPT_ATTACK);
    }
}

static void func_000D15F8(void *obj)
{
    CharaAIWork *ai = GetSCRCharaAIWorkPtr(obj);
    char work[0x70] __attribute__((aligned(16)));
    s128 *p = *(s128 **)(GetCharacterClass(obj) + 0x110C);

    if (!equipmentInvisibilityCloak()) {
        focusClipped(obj, ai, p, work);
    } else {
        focusClipped(obj, ai, (s128 *)(getSCRDataCtrlWork(obj) + 0x4030), work);
    }
}
