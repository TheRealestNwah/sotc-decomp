typedef struct {
    void *obj;
} SysGroup;

typedef struct {
    int count;
    int *groups;
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

static inline int *getObjectGroup(JudgeVolumeWork *w, unsigned int *attr)
{
    unsigned int index = (*attr >> 18) & 0xFFF;
    int *groups = w->groups;

    if (groups != 0)
        return groups + index;
    return 0;
}

int CheckPositionInsideOfJudgeVolumeObject(void *pos, unsigned char *actor, unsigned int *attr, void *arg)
{
    JudgeVolumeWork *w = getJudgeVolumeClass(actor);
    int found = 0;

    if (w != 0) {
        int *head = getObjectGroup(w, attr);
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
    return found;
}
