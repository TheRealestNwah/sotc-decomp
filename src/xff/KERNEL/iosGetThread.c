typedef struct Thread {
    char pad[0x28];
    struct Thread *next;
} Thread;
extern Thread *B_000516E0[];
extern int GetThreadId(void);
Thread *iosGetThread(void)
{
    return B_000516E0[GetThreadId()];
}
