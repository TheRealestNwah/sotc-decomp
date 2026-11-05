typedef struct { char pad[0x168]; float x168; } GV;
extern GV gcGlobalVar;
extern void _optionWorkSet(int, int);
extern void graphFrameBufferReInitializeRequest(void);
extern void setAspect(int);
extern int *getProgressiveMode(void);
extern void scrRun(void);
extern void SpriteMenuSetDispFlag(void *, int, int);
extern void SpriteMenuSetLayer(void *, int);
extern void SpriteMenuSetSelectMenuId(void *, int);

#define GF(o) (gcGlobalVar.x168)

static void func_00094FE0(void *menu, int *w, int flag, int act)
{
    if (!(flag & 1))
        return;
    switch (w[1]) {
    case 0:
        switch (act) {
        case 1:
            _optionWorkSet(6, 0);
            graphFrameBufferReInitializeRequest();
            setAspect(-1);
            w[0] = 0;
            break;
        case 0:
            if (*getProgressiveMode() != 1) {
                *getProgressiveMode() = 1;
                _optionWorkSet(6, 1);
                graphFrameBufferReInitializeRequest();
                scrRun();
                setAspect(-1);
            }
            SpriteMenuSetDispFlag(menu, 0, 0);
            SpriteMenuSetDispFlag(menu, 1, 1);
            SpriteMenuSetLayer(menu, 1);
            w[1] = 1;
            ((float *)w)[2] = GF(0x168);
            ((float *)w)[3] = GF(0x168);
            break;
        }
        break;
    case 1:
        switch (act) {
        case 0:
            if (*getProgressiveMode() != 0) {
                *getProgressiveMode() = 0;
                _optionWorkSet(6, 0);
                graphFrameBufferReInitializeRequest();
                scrRun();
                setAspect(-1);
            }
            SpriteMenuSetDispFlag(menu, 1, 0);
            SpriteMenuSetDispFlag(menu, 0, 1);
            SpriteMenuSetLayer(menu, 0);
            SpriteMenuSetSelectMenuId(menu, 1);
            w[1] = 0;
            ((float *)w)[3] = GF(0x168) - 3.0f + 1.0f;
            break;
        case 1:
            w[1] = 0;
            w[0] = 0;
            break;
        }
        break;
    }
}
