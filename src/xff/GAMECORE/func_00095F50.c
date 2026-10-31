typedef struct {
    char pad0[0x190];
    float animStart;
    float animEnd;
} GcGlobal;

extern GcGlobal gcGlobalVar;
extern int B_0018B850[4];
extern int B_0019B860[2];
extern char B_0018B860[0x10000];
extern void *isysGetThisSubThread(void);
extern void *get_main_cameraman_camera_obj(void);
extern int ExecObjectAnimation(void *, void *, float, float);
extern void isysRequestDeleteObj(void *);

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

static void func_00095F50(void)
{
    void *thread;
    int done;

    SCR_STACK_ENTER();
    thread = isysGetThisSubThread();
    done = ExecObjectAnimation(thread, get_main_cameraman_camera_obj(), gcGlobalVar.animStart, gcGlobalVar.animEnd);
    B_0018B850[0] = done;
    if (done != 0)
        isysRequestDeleteObj(thread);
    SCR_STACK_LEAVE();
}
