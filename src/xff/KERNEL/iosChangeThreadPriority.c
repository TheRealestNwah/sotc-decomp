extern int GetThreadId(void);
extern char *B_000516E0[];
void iosChangeThreadPriority(char *thread, int priority)
{
    if (thread == 0) thread=B_000516E0[GetThreadId()];
    *(int *)(thread + 0x14)=priority;
}
