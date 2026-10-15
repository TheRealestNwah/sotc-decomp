extern char gcGlobalVar[];
typedef struct { void *obj; void *layout; } SScript;
extern SScript B_001A5B60;
extern void *SCRGetFirstObj(void *);
extern void *GetLayoutClass(void *);
extern void soundScriptTickProc(void *);

void updateSScriptSystem(void *a)
{
    SScript *s = &B_001A5B60;
    void *o = SCRGetFirstObj(gcGlobalVar + 0x2B0);
    s->obj = o;
    if (o != 0) {
        s->layout = GetLayoutClass(o);
        soundScriptTickProc(a);
    }
}
