typedef struct {
    char pad0[0x40];
    float scale_y;
    float scale_x;
    float scale_z;
    char pad4C[0x14];
    float v60[4];
    float v70[4];
    char pad80[0x10];
    float v90[4];
    char padA0[0x94];
    int unk134;
    int *unk138;
    int unk13C;
} LayoutClass;

extern LayoutClass *GetLayoutClass(int);
extern void SetJudgeVolumeInfo(int, int, int, int, float *, float *, float *, float, float, float);

int ScriptAnimationObjOfJudgeVolumeObject(int arg0, int id)
{
    LayoutClass *layout = GetLayoutClass(id);

    if (layout == 0) {
        return 0;
    }
    SetJudgeVolumeInfo(arg0, *layout->unk138, layout->unk134, layout->unk13C, layout->v90, layout->v70,
                       layout->v60, layout->scale_x, layout->scale_y, layout->scale_z);
    return 1;
}
