typedef struct {
    char pad0[0x188];
    float clipDist;
    char pad18C[0x370 - 0x18C];
    char lwsCtx[1];
} GcGlobal;

extern GcGlobal gcGlobalVar;
extern int B_0019B860[2];
extern char B_0018B860[0x10000];
extern void *isysGetThisSubThread(void);
extern void *get_main_cameraman_camera_obj(void);
extern float ViewIntervalClip(void *, void *, float);
extern void ExecScriptLwsOrientClass(void *, void *, void *, float, float);

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
"                                                                               : : "r"(B_0019B860[0]) : "$2", "$3", "memory")

#define SCR_STACK_LEAVE()                                                                          __asm__ __volatile__("lui $2, %%hi(B_0019B860)
"                                                                   "nop
"                                                                                        "addiu $2, $2, %%lo(B_0019B860)
"                                                             "nop
"                                                                                        "lw $sp, 0($2)
"                                                                              : : "r"(B_0019B860[0]) : "$2", "memory")

static void func_00095E70(void)
{
    void *thread;
    float clip;

    SCR_STACK_ENTER();
    thread = isysGetThisSubThread();
    clip = ViewIntervalClip(thread, get_main_cameraman_camera_obj(), gcGlobalVar.clipDist);
    ExecScriptLwsOrientClass(thread, get_main_cameraman_camera_obj(), gcGlobalVar.lwsCtx, clip, 1.0f / clip);
    SCR_STACK_LEAVE();
}
