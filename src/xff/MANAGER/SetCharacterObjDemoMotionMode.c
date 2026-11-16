typedef int s128 __attribute__((mode(TI)));
extern void *DldSysUndefSymbol;
extern s128 ZeroPoint;
extern char IdentityQuaternion[];
extern unsigned int *SetDemoMotionOrientInfo(void *);
extern void ReleaseCharacterClassMotSyncAnim(void *);
extern void entrySyncAnim(void *, void *, char *, int, float);
extern void callEntryFunc(void *, void *, char *);
extern void ResetCharacterClassMotionShiftInfo(void *, void *, float);
extern void InitGazeAddChannelDef(char *, char *);
extern void FinishCharacterObjAllAdditionMotion(void *);
extern void character_motchange_adjustrootrot(void *, char *, int, void *, float);
extern void ForceAcceptMotionControlChange(void *, int);

static inline char *GetCharacterClass(void *character)
{
    char *obj = character;

    switch ((unsigned char)obj[8]) {
    case 9:
        return obj + 0x90;
    case 0x16:
        return obj + 0x90;
    default:
        return 0;
    }
}

static inline char *resourceData(unsigned int *reference)
{
    unsigned int encoded = *reference;
    unsigned int offset = encoded & 0x3FFFF;
    char *module;
    if (offset)
        module = *(char **)((char *)reference - offset);
    else
        module = 0;
    if (module && module != DldSysUndefSymbol) {
        int index = (encoded >> 18) & 0xFFF;
        char *definition = *(char **)(module + 8);
        char *data = *(char **)(module + 0x10);
        return data + index * *(int *)(definition + 0xC);
    }
    return 0;
}

static inline int resourceCount(unsigned int *reference)
{
    unsigned int offset = *reference & 0x3FFFF;
    char *module = offset ? *(char **)((char *)reference - offset) : 0;
    return (module && module != DldSysUndefSymbol) ? *(int *)(module + 0xC) : 0;
}

int SetCharacterObjDemoMotionMode(void *obj, float rate)
{
    char *cls = GetCharacterClass(obj);
    unsigned int *info;
    char *anim;

    if (cls) {
        info = SetDemoMotionOrientInfo(cls + 0x1080);
        ReleaseCharacterClassMotSyncAnim(obj);
        if (info) {
            anim = resourceData(info);
            if (anim) {
                entrySyncAnim(cls + 0xD92, obj, anim, -1, 0.0f);
                callEntryFunc(cls, obj, anim);
            }
            ResetCharacterClassMotionShiftInfo(cls, anim, rate);
            {
                char *gaze = *(char **)(cls + 0x334);
                unsigned int *ref = (unsigned int *)(*(char **)(cls + 0x1140) + 0x134);
                int n = resourceCount(ref);
                if (n) {
                    char *def;
                    int t = (int)resourceData(ref);
                    def = (char *)t;
                    while (n--) {
                        InitGazeAddChannelDef(gaze, def);
                        gaze += 0x10;
                        def += 0x14;
                    }
                }
            }
            FinishCharacterObjAllAdditionMotion(obj);
            *(int *)(cls + 0x1070) = 1;
            *(char *)(cls + 0x360) = 0;
        } else {
            int *root = (int *)(cls + 0x1C0);
            if (root[0])
                character_motchange_adjustrootrot(cls, *(char **)(cls + 0x2AC) + 0x50, root[0], IdentityQuaternion,
                                                  ((float *)root)[2]);
            {
                char *c = GetCharacterClass(obj);
                if (c) {
                    char *m;
                    *(int *)(c + 0x1070) = 0;
                    m = *(char **)(c + 0x358);
                    *(s128 *)(c + 0x6D0) = ZeroPoint;
                    if (m)
                        *(float *)(c + 0x6D4) = *(float *)(m + 0x14);
                }
            }
            ResetCharacterClassMotionShiftInfo(cls, *(void **)(cls + 0x2AC), rate);
            ForceAcceptMotionControlChange(cls, *(int *)(cls + 0x2B0));
            *(int *)(cls + 0x578) = 0;
        }
    }
    return 0;
}
