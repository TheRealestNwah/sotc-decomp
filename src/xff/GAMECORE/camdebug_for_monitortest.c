extern char padManagerData[];
extern void *get_main_cameraman(void);
extern void *get_cur_camera_target(void *);
extern void DebugSetHorsePositionWithTargetOfs(void *, const float *);

static const float RO_0017C6B0[4] = { 0.0f, 10.0f, 0.0f, 0.0f };

void camdebug_for_monitortest(void)
{
    void *t = get_cur_camera_target(get_main_cameraman());
    char *pd = padManagerData;

    if ((*(int *)(pd + 0xF98) & 2) && (*(int *)(pd + 0xFA0) & 0x40))
        DebugSetHorsePositionWithTargetOfs(t, RO_0017C6B0);
}
