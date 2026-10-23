extern int execScriptGroup[];

int *GetScriptPriorityGroup(int priority)
{
    return &execScriptGroup[priority];
}
