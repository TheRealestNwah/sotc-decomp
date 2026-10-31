typedef struct {
    char pad0[0x178];
    float demoStart;
    char pad17C[0x180 - 0x17C];
    float demoEnd;
} GcGlobal;

extern GcGlobal gcGlobalVar;
extern int B_0019B860[2];
extern char B_0018B860[0x10000];
extern void *isysGetThisSubThread(void);
extern void ExecLwsDemoOrientManagerObj(void *, float, float);

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

static void func_00096010(void)
{
    SCR_STACK_ENTER();
    ExecLwsDemoOrientManagerObj(isysGetThisSubThread(), gcGlobalVar.demoStart, gcGlobalVar.demoEnd);
    SCR_STACK_LEAVE();
}
