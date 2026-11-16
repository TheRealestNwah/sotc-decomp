/* Turns script-animation access off (when menu flag 7 is set) or on for both linked objects. */
typedef struct {
    char pad0[0x60];
    void *obj0;
    void *obj1;
    int lock0;
    int lock1;
    char pad70[4];
    unsigned char force0;
    unsigned char force1;
} AccessWork;

extern void *isysGetThisSubThread(void);
extern int _omakeSelectFlagChk(int);
extern void SetScriptAnimationObjAccessSwitch(void *, int);

static inline void setAccess(AccessWork *w, int on)
{
    if (w->obj0 != 0) {
        if (!w->force0) {
            if (w->lock0 == 0)
                SetScriptAnimationObjAccessSwitch(w->obj0, on);
        } else
            SetScriptAnimationObjAccessSwitch(w->obj0, on);
    }
    if (w->obj1 != 0) {
        if (!w->force1) {
            if (w->lock1 == 0)
                SetScriptAnimationObjAccessSwitch(w->obj1, on);
        } else
            SetScriptAnimationObjAccessSwitch(w->obj1, on);
    }
}

static void func_00076698(AccessWork *w)
{
    isysGetThisSubThread();
    if (_omakeSelectFlagChk(7))
        setAccess(w, 0);
    else
        setAccess(w, 1);
}
