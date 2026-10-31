typedef struct {
    char pad0[0x1AC];
    int mode;
} LayoutClass;

typedef struct {
    char pad0[0x409C];
    int status;
} SCRWork;

extern int SCRModeStatus_SNAKE_ROUTE_PATROL_MIDDLE;
extern int SCRModeStatus_SNAKE_ROUTE_PATROL_TAKE_OFF;
extern LayoutClass *GetLayoutClass(void);
extern SCRWork *getSCRDataCtrlWork(void *);

static void func_000BBED8(void *obj)
{
    LayoutClass *l = GetLayoutClass();
    SCRWork *w = getSCRDataCtrlWork(obj);

    l->mode = 0;
    if (w) {
        if (w->status == SCRModeStatus_SNAKE_ROUTE_PATROL_MIDDLE ||
            w->status == SCRModeStatus_SNAKE_ROUTE_PATROL_TAKE_OFF)
            l->mode = 10;
    }
}
