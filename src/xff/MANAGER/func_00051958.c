extern int DldSysUndefSymbol;
extern void InitAnimationClass(void *, char *);
extern void ResetAnimeFrameTableInfo(void *, char *, char *);
extern void CallMotShiftCallBackElemEntryFunc(void *, char *, int);
extern char *GetCharacterClass(int);
extern void SetGeometryPointerNodePosState(void *, int, int, void *, void *);
extern int CreateScriptAnimationSequence(void *);
extern void SetScariptAnimationObjMotSyncSlotId(int, int);
extern void PlayScriptAnimationSequence(int, int, int, int);
extern void SetScriptAnimationObjChildEntryGroup(int, char *);
extern void ExecMotionSyncAnimation(int, int, float, float);
extern void EntryScriptAnimationObjJudgeVolumeGroup(int, void *);
extern void isysAddGroupWithLinkParam(int, char *, int, int);
extern int IdentityQuaternion;
extern int ZeroPoint;
extern int rootPtn;

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;
    return (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
}

static void func_00051958(char *anim, char *src)
{
    char *a;
    char *b;

    InitAnimationClass(anim + 4, src);
    a = dldResolve((unsigned int *)(src + 0x48));
    b = dldResolve((unsigned int *)(src + 0x4C));
    ResetAnimeFrameTableInfo(anim + 0x34, a, b);
    *(int *)(anim + 0x44) = 0;
}

static void func_00051A60(int obj, char *cls, int idx, char *mot, float f)
{
    char geo[0x40];
    int prm[11];
    char *anim;
    void (**cb)(int);
    unsigned int *rp;
    char *res;
    char *chr;
    int seq;
    int i;
    int n;

    anim = *(char **)(cls + 0x30C) + (idx << 7);
    func_00051958(anim, mot);
    cb = (void (**)(int))(mot + 0x94);
    for (i = 4; i >= 0; i--) {
        if (*cb != 0)
            (*cb)(obj);
        cb++;
    }
    CallMotShiftCallBackElemEntryFunc(cls + 0x2C8, mot, obj);
    CallMotShiftCallBackElemEntryFunc(cls + 0x2C8, mot, obj);
    rp = (unsigned int *)(mot + 0x54);
    for (n = 1; n != -1; n--) {
        res = dldResolve(rp);
        if (res != 0) {
            chr = GetCharacterClass(obj);
            SetGeometryPointerNodePosState(geo, obj, -1, &IdentityQuaternion, &ZeroPoint);
            prm[0] = (int)res;
            prm[1] = (int)&rootPtn;
            prm[2] = (int)geo;
            prm[3] = 0;
            prm[4] = 0;
            prm[5] = 0;
            prm[6] = obj;
            prm[7] = *(int *)(chr + 0x57C);
            prm[8] = 0;
            prm[9] = 0;
            prm[10] = -1;
            seq = CreateScriptAnimationSequence(prm);
            if (seq != 0) {
                SetScariptAnimationObjMotSyncSlotId(seq, idx);
                PlayScriptAnimationSequence(seq, 0, -1, 2);
                SetScriptAnimationObjChildEntryGroup(seq, anim);
                ExecMotionSyncAnimation(seq, 0, f, 1.0f / f);
                EntryScriptAnimationObjJudgeVolumeGroup(seq, chr + 0x2A0);
                isysAddGroupWithLinkParam(seq, anim, 0, 0);
            }
        }
        rp++;
    }
}
