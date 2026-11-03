typedef struct {
    void *obj;
} SysGroup;

typedef struct {
    int count;
    int *groups;
    int *labels;
} JudgeVolumeWork;

extern char *GetCharacterClass(unsigned char *);
extern char *GetScriptAnimationClass(unsigned char *);
extern SysGroup *isysGroupForFirst(void *, int);
extern SysGroup *isysGroupForNext(SysGroup *, int);
extern void isysGroupForExit(void *, int);
extern int ScriptAnimationObjCheckPositionInsideOfJudgeVolumeObject(void *, void *, void *);

static inline JudgeVolumeWork *getJudgeVolumeClass(unsigned char *p)
{
    JudgeVolumeWork *r;

    switch (p[8]) {
    case 9:
    case 0x16:
        r = (JudgeVolumeWork *)(GetCharacterClass(p) + 0x2A0);
        break;
    case 0xD:
        r = *(JudgeVolumeWork **)(GetScriptAnimationClass(p) + 0x33C);
        break;
    default:
        r = 0;
        break;
    }
    return r;
}

static inline int *getObjectGroupByLabel(JudgeVolumeWork *w, int *label)
{
    int i;
    int n = w->count;
    int *p = w->labels;

    for (i = 0; i < n; i++, p++) {
        if (p == label) {
            return w->groups != 0 ? w->groups + i : 0;
        }
    }
    return 0;
}

int CheckPositionInsideOfJudgeVolumeObjectByLabel(void *pos, unsigned char *actor, int *label, void *arg)
{
    JudgeVolumeWork *w = getJudgeVolumeClass(actor);
    int found = 0;

    if (w != 0) {
        int *head = getObjectGroupByLabel(w, label);

        if (head != 0) {
            SysGroup *g;
            void *last = 0;

            for (g = isysGroupForFirst(head, 0); g != 0; g = isysGroupForNext(g, 0)) {
                last = g->obj;
                if (ScriptAnimationObjCheckPositionInsideOfJudgeVolumeObject(pos, last, arg)) {
                    found = 1;
                    break;
                }
            }
            if (last != 0)
                isysGroupForExit(last, 0);
        }
    }
    return found;
}
