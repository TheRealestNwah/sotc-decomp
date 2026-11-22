typedef struct {
    char pad0[0x188];
    float clipDist;
    char pad18C[0x1AC - 0x18C];
    int busy;
} GcGlobal;

extern GcGlobal gcGlobalVar;
extern int B_0018B850[4];
extern void func_00095E70(void);
extern void func_00096010(void);
extern void func_00095DB0(void);
extern void func_00095F50(void);
extern void func_000956B0(void);
extern void isysLetterObjDiscardLetterAll(void *);
extern void isysSleepSubThread(void);
extern void FlushRequestViewIntervalClip(void *);
extern int get_main_cameraman_camera_obj(void);
extern void ViewIntervalClip(void *, int, float);
extern void ExecScriptLayoutObj(void *);
extern char *GetCharacterClass(void *);
extern void ExecCharaGeometryPostprocess(void *);

static void func_00095428(unsigned char *obj)
{
    switch (obj[8]) {
    case 22:
        func_00095E70();
        isysLetterObjDiscardLetterAll(obj);
        isysSleepSubThread();
        while (gcGlobalVar.busy) {
            FlushRequestViewIntervalClip(obj);
            ViewIntervalClip(obj, get_main_cameraman_camera_obj(), gcGlobalVar.clipDist);
            isysSleepSubThread();
        }
        break;
    case 6:
        isysLetterObjDiscardLetterAll(obj);
        isysSleepSubThread();
        return;
    case 29:
        isysLetterObjDiscardLetterAll(obj);
        isysSleepSubThread();
        func_00096010();
        while (gcGlobalVar.busy) {
            isysLetterObjDiscardLetterAll(obj);
            isysSleepSubThread();
        }
        break;
    case 11:
        isysLetterObjDiscardLetterAll(obj);
        isysSleepSubThread();
        ExecScriptLayoutObj(obj);
        return;
    case 9:
        if (GetCharacterClass(obj)[0xCEC])
            func_00095DB0();
        ExecCharaGeometryPostprocess(obj);
        isysLetterObjDiscardLetterAll(obj);
        isysSleepSubThread();
        while (gcGlobalVar.busy) {
            FlushRequestViewIntervalClip(obj);
            ViewIntervalClip(obj, get_main_cameraman_camera_obj(), gcGlobalVar.clipDist);
            isysSleepSubThread();
        }
        func_000956B0();
        return;
    case 13:
        func_00095F50();
        if (B_0018B850[0]) {
            for (;;) {
                isysLetterObjDiscardLetterAll(obj);
                isysSleepSubThread();
            }
        }
        isysLetterObjDiscardLetterAll(obj);
        isysSleepSubThread();
        while (gcGlobalVar.busy) {
            isysLetterObjDiscardLetterAll(obj);
            isysSleepSubThread();
        }
        break;
    default:
        isysLetterObjDiscardLetterAll(obj);
        isysSleepSubThread();
        break;
    }
}
