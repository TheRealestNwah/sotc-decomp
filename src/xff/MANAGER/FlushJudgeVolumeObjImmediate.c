extern char *GetCharacterClass(void *);
extern char *GetScriptAnimationClass(void *);
extern void isysDeleteGroupAllObj(void *);
extern void iosFree(void *);

typedef struct {
    int count;
    int *groups;
} JudgeVolumeWork;

void FlushJudgeVolumeObjImmediate(unsigned char *o)
{
    JudgeVolumeWork *w;
    int *g;
    int n;
    int i;

    switch (o[8]) {
    case 9:
    case 0x16:
        w = (JudgeVolumeWork *)(GetCharacterClass(o) + 0x2A0);
        break;
    case 0xD:
        w = *(JudgeVolumeWork **)(GetScriptAnimationClass(o) + 0x33C);
        break;
    default:
        w = 0;
        break;
    }
    g = w->groups;
    n = w->count;
    for (i = 0; i < n; i++) {
        isysDeleteGroupAllObj(g);
        g++;
    }
    if (w->groups) {
        iosFree(w->groups);
        w->groups = 0;
        w->count = 0;
    }
}
