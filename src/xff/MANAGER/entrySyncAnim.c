extern void *DldSysUndefSymbol;
extern char IdentityQuaternion[];
extern char ZeroPoint[];
extern char rootPtn[];

extern char *GetCharacterClass(int);
extern void SetGeometryPointerNodePosState(void *, int, int, void *, void *);
extern int CreateScriptAnimationSequence(void *);
extern void SetScariptAnimationObjMotSyncSlotId(int, int);
extern void PlayScriptAnimationSequence(int, int, int, int);
extern void SetScriptAnimationObjChildEntryGroup(int, int);
extern void ExecMotionSyncAnimation(int, int, float, float);
extern void EntryScriptAnimationObjJudgeVolumeGroup(int, void *);
extern void isysAddGroupWithLinkParam(int, int, int, int);

typedef struct {
    char node[0x40];
    char *data;
    char *ptn;
    void *nodePtr;
    int a;
    int b;
    int c;
    int chr;
    int cls;
    int d;
    int e;
    int f;
} SyncSetup;

void entrySyncAnim(int group, int chr, char *data, int slot, float speed)
{
    unsigned int *ref = (unsigned int *)(data + 0x54);
    int n = 1;

    do {
        unsigned int encoded = *ref;
        unsigned int offset = encoded & 0x3FFFF;
        char *module;
        char *def;
        char *entry;

        if (offset)
            module = *(char **)((char *)ref - offset);
        else
            module = 0;
        if (module && module != DldSysUndefSymbol) {
            def = *(char **)(module + 8);
            entry = *(char **)(module + 0x10) + ((encoded >> 18) & 0xFFF) * *(int *)(def + 0xC);
        } else {
            entry = 0;
        }
        if (entry) {
            SyncSetup s;
            char *cls = GetCharacterClass(chr);
            int obj;

            SetGeometryPointerNodePosState(s.node, chr, -1, IdentityQuaternion, ZeroPoint);
            s.data = entry;
            s.ptn = rootPtn;
            s.nodePtr = s.node;
            s.a = 0;
            s.b = 0;
            s.c = 0;
            s.chr = chr;
            s.cls = *(int *)(cls + 0x57C);
            s.d = 0;
            s.e = 0;
            s.f = -1;
            obj = CreateScriptAnimationSequence(&s.data);
            if (obj) {
                SetScariptAnimationObjMotSyncSlotId(obj, slot);
                PlayScriptAnimationSequence(obj, 0, -1, 2);
                SetScriptAnimationObjChildEntryGroup(obj, group);
                ExecMotionSyncAnimation(obj, 0, speed, 1.0f / speed);
                EntryScriptAnimationObjJudgeVolumeGroup(obj, cls + 0x2A0);
                isysAddGroupWithLinkParam(obj, group, 0, 0);
            }
        }
        n--;
        ref++;
    } while (n != -1);
}
