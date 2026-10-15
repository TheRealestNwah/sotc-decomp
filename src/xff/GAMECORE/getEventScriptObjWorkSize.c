typedef struct { char pad[0x10]; int v; } Info;
extern Info D_0017B8D0;
extern int GetScriptObjWorkSize(Info *);

int getEventScriptObjWorkSize(int *p)
{
    int r;
    D_0017B8D0.v = *p;
    r = GetScriptObjWorkSize(&D_0017B8D0);
    p = 0;
    return r;
}
