extern void *isysGetThisSubThread(void);
extern char *GetLayoutClass(void *);
extern void *GetGeometryPointerObject(char *);
extern void SendCharaMotionSyncStartMsg(void *, void *);
extern void SCRSimpleExecCharaGeometry(void *);
extern void scrRun(void);

void nico_parentSync(void)
{
    void *t = isysGetThisSubThread();
    char *l = GetLayoutClass(t);
    void *g = GetGeometryPointerObject(l + 0xC0);
    if (g != 0)
        SendCharaMotionSyncStartMsg(t, g);
    if (*(int *)(l + 0x124) != 0) {
        SCRSimpleExecCharaGeometry(t);
        SCRSimpleExecCharaGeometry(t);
    }
    for (;;)
        scrRun();
}
