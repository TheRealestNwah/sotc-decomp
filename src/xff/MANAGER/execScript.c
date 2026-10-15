extern int execScriptGroup[];
extern void func_000873A8(int *);

void execScript(void)
{
    int i;
    int *g = execScriptGroup;
    for (i = 15; i >= 0; i--)
        func_000873A8(g++);
}
