typedef struct { int id; int (*entry)(void *, int, int, int); int (*leave)(void *, int, int, int); int arg; } ShiftCB;
typedef struct { int n; ShiftCB *e; } ShiftList;

extern void *GetCharacterClass(void *);
extern int CallMotShiftCallBackElemLeaveFunc(ShiftList *, int, void *);
int DebugCallCharacterObjMotionLeaveFunc(void *object)
{
    int remaining = 1;
    char *character = GetCharacterClass(object);
    char *motion = *(char **)(character + 0x1C0);
    void (**callback)(void *) = (void (**)(void *))(motion + 0xA8);
    do {
        void (*leave)(void *) = *callback++;
        if (leave)
            leave(object);
    } while (--remaining >= 0);
    return CallMotShiftCallBackElemLeaveFunc((ShiftList *)(character + 0x2C8), (int)motion, object);
}
