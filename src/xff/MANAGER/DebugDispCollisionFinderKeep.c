typedef struct {
    int found;
    int pad;
} FinderEntry;

typedef struct {
    int max;
    int count;
    int pad8;
    FinderEntry *entries;
} Finder;

extern void iosDlPushLayer(int);
extern void iosDlPopLayer(void);
extern void glBegin(int);
extern void glEnable(int);
extern void glBlendFunc(int, int);
extern void glEnd(void);
extern void triangleDispSetup(void);
extern void trianglePolyColor(int, float, float, float, float);
extern void func_000A5A28(void *, float, float, float, float, float, float, float, float, float, float, float);

void DebugDispCollisionFinderKeep(Finder *f, float t)
{
    int i;
    int n = f->count < f->max ? f->count : f->max;

    iosDlPushLayer(0x17);
    glBegin(8);
    glEnable(7);
    glBlendFunc(5, 1);
    glEnd();
    glEnable(3);
    triangleDispSetup();
    trianglePolyColor(1, -1.0f, -1.0f, -1.0f, -1.0f);
    for (i = 0; i < n; i++) {
        if (f->entries[i].found != 0)
            func_000A5A28(&f->entries[i], 0.5f, 0.7f, 0.5f, 0.5f, 0.7f, 0.5f, 0.5f, 0.7f, 0.7f, 0.099999996f, t);
    }
    iosDlPopLayer();
}
