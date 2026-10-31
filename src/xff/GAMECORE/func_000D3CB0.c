typedef int s128 __attribute__((mode(TI)));

typedef struct {
    char pad0[0x41CC];
    void *volume;
} CharaAIWork;

extern CharaAIWork *GetSCRCharaAIWorkPtr(void *);
extern s128 *getAimIKWork(void *);
extern int CheckPositionInsideOfJudgeVolumeObject(void *, void *, void *, s128 *);
extern void GetVolumeClippedTargetPos(s128 *, void *, void *, s128 *);
extern int SkelFocusDef_BOSS_OPT_ATTACK;
extern void func_000D2438(void *, s128 *, int);

static void func_000D3CB0(void *obj)
{
    CharaAIWork *ai = GetSCRCharaAIWorkPtr(obj);
    char work[0x60];
    s128 pos;
    s128 *p;
    s128 *aim;

    aim = getAimIKWork(obj);
    p = &pos;
    pos = *aim;

    if (CheckPositionInsideOfJudgeVolumeObject(work, obj, ai->volume, p)) {
        func_000D2438(obj, p, SkelFocusDef_BOSS_OPT_ATTACK);
    } else {
        GetVolumeClippedTargetPos(p, obj, ai->volume, p);
        func_000D2438(obj, p, SkelFocusDef_BOSS_OPT_ATTACK);
    }
}
