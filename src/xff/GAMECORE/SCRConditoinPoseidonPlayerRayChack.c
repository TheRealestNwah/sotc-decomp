extern char gcGlobalVar[];
extern char *getSCRDataCtrlWork(void *);
extern char *GetLayoutClass(void *);
extern int ClipCollisionDirect(void *, float *, float *, void *);

int SCRConditoinPoseidonPlayerRayChack(void *actor, int interval)
{
    char *work = getSCRDataCtrlWork(actor);
    char hit[0x50];

    if ((int)*(float *)(work + 0x40A4) % interval > 0)
        return 0;
    return ClipCollisionDirect(hit, *(float **)(GetLayoutClass(actor) + 0x134),
                               *(float **)(*(char **)(work + 0x407C) + 0x134), gcGlobalVar + 0x244) == 0;
}
