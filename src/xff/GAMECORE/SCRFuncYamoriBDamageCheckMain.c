typedef struct {
    char pad0[0x180];
    float f180;
} GcGlobalVar;
extern GcGlobalVar gcGlobalVar;
extern char *GetSCRCharaAIWorkPtr(void *);
extern int nico_GetCharacterAttackedFlag(void *);
extern unsigned int nico_GetCharacterAttackedGPAttr(void *, int);
extern char *GetDamageClass(void *);
extern char *GetCharacterClass(void *);

typedef struct {
    char pad0[0x41B0];
    float t[4];
} YamoriWork;

void SCRFuncYamoriBDamageCheckMain(void *obj, float limit)
{
    YamoriWork *w = (YamoriWork *)GetSCRCharaAIWorkPtr(obj);
    int i;

    if (nico_GetCharacterAttackedFlag(obj)) {
        unsigned int attr = nico_GetCharacterAttackedGPAttr(obj, 0x3F0);
        char *dc = GetDamageClass(obj);
        char *cc = GetCharacterClass(obj);
        if (!(*(unsigned long *)(cc + 0x690) & 0x1E00000)) {
            for (i = 3; i >= 0; i--)
                w->t[i] = -1.0f;
        }
        if (*(int *)(dc + 0x60) != 3) {
            switch (attr) {
            case 0x120:
                w->t[0] = 0;
                break;
            case 0x130:
                w->t[1] = 0;
                break;
            case 0x140:
                w->t[2] = 0;
                break;
            case 0x150:
                w->t[3] = 0;
                break;
            }
        }
    }
    for (i = 0; i < 4; i++) {
        if (0.0f <= w->t[i]) {
            w->t[i] += gcGlobalVar.f180;
            if (limit < w->t[i])
                w->t[i] = -1.0f;
        }
    }
}
