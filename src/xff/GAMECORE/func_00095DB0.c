typedef struct {
    char pad0[0x539];
    char inArea;
} ScrCharClass;

typedef struct {
    char pad0[0x134];
    int area;
} ScrLayoutClass;

extern char gcGlobalVar[];
extern int B_0019B860[2];
extern char B_0018B860[0x10000];
extern void *isysGetThisSubThread(void);
extern ScrCharClass *GetCharacterClass(void *);
extern void ExecCharaGeometry(void *, void *);
extern ScrLayoutClass *GetLayoutClass(void *);
extern char StageManagerCheckAreaExist(int);

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

static void func_00095DB0(void)
{
    void *thread;
    ScrCharClass *cc;

    SCR_STACK_ENTER();
    thread = isysGetThisSubThread();
    cc = GetCharacterClass(thread);
    ExecCharaGeometry(thread, gcGlobalVar + 0x370);
    cc->inArea = StageManagerCheckAreaExist(GetLayoutClass(thread)->area);
    SCR_STACK_LEAVE();
}
