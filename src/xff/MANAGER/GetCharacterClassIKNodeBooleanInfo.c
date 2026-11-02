typedef struct { char *resource; int unknown04; float f08; float f0C; } IkNode;
extern int GetMotionVersion(void *);
extern int GetMotionOptionNodePhysicalId(void *, int);
extern void GetMotionOptionNodeBooleanInfoFloatFrame(char *, void *, int, float, float);
int GetCharacterClassIKNodeBooleanInfo(char *info, char *cls, int node)
{
    IkNode *ik = (IkNode *)(cls + 0x1C0);
    int *options = *(int **)(cls + 0x358);
    char *motion = 0;
    int id;
    if (ik->resource != 0)
        motion = ik->resource + 0x50;
    info[2] = 0;
    info[1] = 0;
    info[0] = 0;
    if (motion == 0)
        return -1;
    if (*options <= 0 || GetMotionVersion(motion) < 5)
        return -1;
    id = GetMotionOptionNodePhysicalId(motion, node);
    if (id < 0)
        return -1;
    GetMotionOptionNodeBooleanInfoFloatFrame(info, motion, id, ik->f08, ik->f0C);
    return 0;
}
