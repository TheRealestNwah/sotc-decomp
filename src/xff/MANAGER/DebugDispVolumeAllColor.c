typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;
typedef struct { Vec4 vectors[5]; int type; float values[3]; } JudgeVolume;
typedef struct {
    char pad0[9];
    unsigned char iterating;
    short flags;
} GroupObj;

typedef struct {
    GroupObj *obj;
    char pad4[8];
    unsigned char removed;
    char padD;
    unsigned short next;
    char pad10[8];
} SysGroup;

typedef struct {
    unsigned short first;
} GroupHead;

extern char *GetJudgeVolumeClass(unsigned char *);
extern void **GetJudgeVolumeClassObjectGroup(char *, unsigned int *);
extern int *GetGlDebugSw(void);
extern SysGroup *isysGroupForFirst(GroupHead *, int);
extern SysGroup *isysGroupForNext(SysGroup *, int);
extern void isysGroupForExit(void *, int);
extern int ScriptAnimationObjOfJudgeVolumeObject(int, int);
extern void DebugDispVolumeShapeColor(void *, float *);

void DebugDispVolumeAllColor(unsigned char *actor, unsigned int *attribute, float *color)
{
    void **head = GetJudgeVolumeClassObjectGroup(GetJudgeVolumeClass(actor), attribute);
    if (*GetGlDebugSw() != 0) {
        JudgeVolume volume;
        SysGroup *group = isysGroupForFirst((GroupHead *)head, 0);
        GroupObj *last = 0;
        while (group != 0) {
            last = group->obj;
            if (ScriptAnimationObjOfJudgeVolumeObject((int)&volume, (int)last))
                DebugDispVolumeShapeColor(&volume, color);
            group = isysGroupForNext(group, 0);
        }
        if (last != 0)
            isysGroupForExit(last, 0);
    }
}
