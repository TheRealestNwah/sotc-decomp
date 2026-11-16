/* Runs func_00096688 on the script system's private stack. */
extern int B_0019B860[2];
extern char B_0018B860[0x10000];
extern void func_00096688(void);

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

static void func_00096610(void)
{
    {
        register int _scr_in asm("$4") = *(volatile int *)B_0019B860;
        SCR_STACK_ENTER();
    }
    func_00096688();
    SCR_STACK_LEAVE();
}
