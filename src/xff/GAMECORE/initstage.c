extern int B_0019B860[2];
extern char B_0018B860[0x10000];
extern int *DldSysUndefSymbol;
extern int D_0017AF58;
extern int D_0017AF5C;
extern int D_0017AF60;
extern int D_0017AF64;
extern int D_0017AF68;
extern int D_0017AF6C;
extern char *gcGetStageData(int id);
extern void initlayout(int a0, void *a1, int a2, int a3, int t0, int t1);

/* Switches to the stage stack (B_0018B860, top saved in B_0019B860) around initlayout.
   The saved word is read into $a0 first; $3 is scratch the Original never declared.
   A bare block, not do/while(0): the loop form shifts every saved register. */
#define SCR_STACK_ENTER()                                                                          \
    {                                                                                              \
        register int top __asm__("$4") = *(volatile int *)B_0019B860;                              \
        __asm__ __volatile__("lui $2, %%hi(B_0019B860)\n"                                          \
                             "nop\n"                                                               \
                             "addiu $2, $2, %%lo(B_0019B860)\n"                                    \
                             "nop\n"                                                               \
                             "sw $sp, 0($2)\n"                                                     \
                             "la $3, B_0018B860\n"                                                 \
                             "lui $2, %%hi(B_0019B860)\n"                                          \
                             "nop\n"                                                               \
                             "addiu $2, $2, %%lo(B_0019B860)\n"                                    \
                             "nop\n"                                                               \
                             "move $sp, $2\n"                                                      \
                             :                                                                     \
                             : "r"(top)                                                            \
                             : "$2", "memory");                                                    \
    }

#define SCR_STACK_LEAVE()                                                                          \
    __asm__ __volatile__("lui $2, %%hi(B_0019B860)\n"                                              \
                         "nop\n"                                                                   \
                         "addiu $2, $2, %%lo(B_0019B860)\n"                                        \
                         "nop\n"                                                                   \
                         "lw $sp, 0($2)\n"                                                         \
                         :                                                                         \
                         : "r"(*(volatile int *)B_0019B860)                                        \
                         : "$2", "memory")

void initstage(int a0, int a1, int a2, int a3, int t0, int t1)
{
    unsigned int *ref;
    int off;
    int *t;
    char *p;

    D_0017AF5C = a1;
    D_0017AF58 = a0;
    D_0017AF60 = a2;
    D_0017AF68 = t0;
    D_0017AF6C = t1;
    D_0017AF64 = a3;
    SCR_STACK_ENTER()
    ref = (unsigned int *)(gcGetStageData(a1) + 4);
    off = *ref & 0x3FFFF;
    t = off != 0 ? *(int **)((char *)ref - off) : 0;
    p = (t != 0 && t != DldSysUndefSymbol)
            ? (char *)t[4] + ((*ref >> 18) & 0xFFF) * ((int *)t[2])[3]
            : 0;
    initlayout(D_0017AF58, p, D_0017AF60, D_0017AF64, D_0017AF68, D_0017AF6C);
    SCR_STACK_LEAVE();
}
