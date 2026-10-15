typedef int s128 __attribute__((mode(TI)));
extern int ParentLayoutObj(void *, char *);
extern void func_00069B70(void *, char *, void *);

static inline void zero(s128 *v)
{
    __asm__ __volatile__("sq $0, 0(%0)" : : "r"(v) : "memory");
}

void motrootdyn_startchainhang(void *m, char *c, void *p)
{
    if (*(int *)(c + 0xDEC) != 0) {
        ParentLayoutObj(m, c + 0xDA0);
        zero((s128 *)(c + 0x6D0));
    }
    func_00069B70(m, c, p);
}
