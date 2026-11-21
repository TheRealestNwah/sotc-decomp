typedef int s128 __attribute__((mode(TI)));
typedef struct {
    char b[0x60];
} VolInfo;

extern char *GetCharacterClass(int);
extern void *GetJudgeVolumeClassObjectGroupById(void *, int);
extern void **isysGroupForFirst(void *, int);
extern void **isysGroupForNext(void **, int);
extern void isysGroupForExit(void *, int);
extern int ScriptAnimationObjCheckPositionInsideOfJudgeVolumeObject(VolInfo *, void *, s128 *);
extern float ClipJudgeVolumeInfo(s128 *, VolInfo *, s128 *);

#ifdef NONMATCHING
/* 18 diffs, same size: the Original keeps the copy destination (sp+0) in s6
 * and rematerializes the info buffer (sp+0x60); this keeps the info pointer
 * in s6 instead, which also swaps the struct copy loop's registers. */
void GetVolumeClippedTargetPos(s128 *out, int obj, unsigned int *ref, s128 *pos)
{
    VolInfo v[2];
    VolInfo *pi;
    s128 clip;
    char *chr = GetCharacterClass(obj);
    int id = (*ref >> 18) & 0xFFF;
    void **it;
    void *vol;
    float best;
    int first;
    void **it0;

    pi = &v[0];
    if (id < 0) {
        *out = *pos;
        return;
    }
    best = 0.0f;
    it0 = isysGroupForFirst(GetJudgeVolumeClassObjectGroupById(chr + 0x2A0, id), 0);
    first = 1;
    vol = 0;
    for (it = it0; it != 0; it = isysGroupForNext(it, 0)) {
        int take;
        float d;

        vol = *it;
        if (ScriptAnimationObjCheckPositionInsideOfJudgeVolumeObject(pi, vol, pos)) {
            *out = *pos;
            v[1] = v[0];
            break;
        }
        take = 0;
        d = ClipJudgeVolumeInfo(&clip, pi, pos);
        if (first) {
            first = 0;
            take = 1;
        } else if (d < best) {
            take = 1;
        }
        if (take) {
            best = d;
            *out = clip;
            v[1] = v[0];
        }
    }
    if (vol)
        isysGroupForExit(vol, 0);
}
#else
extern void GetVolumeClippedTargetPos(s128 *out, int obj, unsigned int *ref, s128 *pos);
#endif
