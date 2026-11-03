typedef struct {
    char pad0[0x178];
    float geomCtx;
    char pad17C[0x188 - 0x17C];
    float clipDist;
} GcGlobal;

typedef struct {
    char pad0[0x370];
    short state;
    char pad372[0x534 - 0x372];
    signed char active;
    char pad535[0xD90 - 0x535];
    unsigned char riding;
    char padD91[0x1070 - 0xD91];
    int f1070;
    char pad1074[0x1170 - 0x1074];
    int f1170;
} ScrCharClass;

typedef struct {
    char pad0[0x8];
    unsigned char type;
} ScrObj;

extern GcGlobal gcGlobalVar;
extern int B_0019B860[2];
extern char B_0018B860[0x10000];
extern void *isysGetThisSubThread(void);
extern void *get_main_cameraman_camera_obj(void);
extern float ViewIntervalClip(void *, void *, float);
extern ScrCharClass *GetCharacterClass(void *);
extern char *GetLayoutClass(void *);
extern int StageManagerCheckAreaExist(int);
extern ScrObj *SCRGetGetGeometryPointerLegalParentObj(char *);
extern void ExecCharaGeometryPreprocess(void *, float, float, float);

#define SCR_STACK_ENTER()                                                                          __asm__ __volatile__("lui $2, %%hi(B_0019B860)
"                                                                   "nop
"                                                                                        "addiu $2, $2, %%lo(B_0019B860)
"                                                             "nop
"                                                                                        "sw $sp, 0($2)
"                                                                              "la $3, B_0018B860
"                                                                          "lui $2, %%hi(B_0019B860)
"                                                                   "nop
"                                                                                        "addiu $2, $2, %%lo(B_0019B860)
"                                                             "nop
"                                                                                        "move $sp, $2
"                                                                               : : "r"(_scr_in) : "$2", "$5", "memory")

#define SCR_STACK_LEAVE()                                                                          __asm__ __volatile__("lui $2, %%hi(B_0019B860)
"                                                                   "nop
"                                                                                        "addiu $2, $2, %%lo(B_0019B860)
"                                                             "nop
"                                                                                        "lw $sp, 0($2)
"                                                                              : : "r"(*(volatile int *)B_0019B860) : "$2", "memory")

static inline int isOnRideParent(char *lay)
{
    ScrObj *obj;
    int t;

    if (lay == 0 || *(int *)(lay + 0x124) == 0 || (obj = SCRGetGetGeometryPointerLegalParentObj(lay + 0xC0)) == 0) {
        t = 0;
    } else {
        switch (obj->type) {
        case 9:
        case 0xD:
        case 0x16:
            t = 1;
            break;
        default:
            t = 0;
            break;
        }
    }
    return t;
}

static void func_000956B0(void)
{
    void *thread;
    ScrCharClass *cc;
    float clip;

    {
        register int _scr_in asm("$4") = *(volatile int *)B_0019B860;
        SCR_STACK_ENTER();
    }
    thread = isysGetThisSubThread();
    cc = GetCharacterClass(thread);
    clip = ViewIntervalClip(thread, get_main_cameraman_camera_obj(), gcGlobalVar.clipDist);
    if (cc->active != 0) {
        if (GetCharacterClass(thread)->f1170 == 0 || StageManagerCheckAreaExist(*(int *)(GetLayoutClass(thread) + 0x134)) != 0 ||
            cc->state == 4 || isOnRideParent(GetLayoutClass(thread)) || cc->riding == 1 || cc->f1070 == 1 || cc->state == 0xB) {
            ExecCharaGeometryPreprocess(thread, gcGlobalVar.geomCtx, clip, 1.0f / clip);
        }
    }
    SCR_STACK_LEAVE();
}
