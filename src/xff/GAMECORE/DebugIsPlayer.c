#define NULL ((void *)0)
extern void *GetLayoutClass(void *);
extern int strcmp(const char *, const char *);
extern const char RO_0017C110[];

int DebugIsPlayer(void *actor)
{
    void *temp_v0;

    temp_v0 = GetLayoutClass(actor);
    if ((temp_v0 != NULL) && (strcmp((*(const char **)((char *)(temp_v0) + 0x130)), RO_0017C110) == 0)) {
        return 1;
    }
    return 0;
}
