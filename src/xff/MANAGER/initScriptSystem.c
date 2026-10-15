extern int execScriptGroup[];
extern void isysInitGroup(int *);

void initScriptSystem(void)
{
    int i;
    int *g = execScriptGroup;
    for (i = 15; i >= 0; i--)
        isysInitGroup(g++);
}
