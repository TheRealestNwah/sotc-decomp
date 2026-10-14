typedef struct {
    char pad0[0x180];
    float delta;
    float time;
} GlobalVar;

typedef struct {
    char pad0[0x124];
    int alias;
    char pad128[0x6C];
    int cloth;
} LayoutClass;

extern void FlushCollisionWork(int);
extern LayoutClass *GetLayoutClass(int);
extern void UpdateAliasLayoutObjClothGeometry(int);
extern void getClothGeometry(int, int, float, float);
extern int isysGetThisSubThread(void);
extern void scrRun(void);
extern GlobalVar gcGlobalVar;

void st_collisionalias(void)
{
    int thread = isysGetThisSubThread();

    for (;;) {
        LayoutClass *layout;

        FlushCollisionWork(thread);
        layout = GetLayoutClass(thread);
        if (layout->alias != 0) {
            UpdateAliasLayoutObjClothGeometry(thread);
            getClothGeometry(thread, layout->cloth, gcGlobalVar.delta, gcGlobalVar.time);
        }
        scrRun();
    }
}
