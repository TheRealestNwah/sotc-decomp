typedef struct { char pad[0x18]; unsigned int flags; } ThreadWork;
extern void *iosMallocAlign(void *, int, int);
extern ThreadWork *iosCreateThread(void *, void *, int, int, int);
extern void iosFree(void *);
extern void iosJumpRecoverPoint(void *, ...);
extern char RO_000426F8[];
ThreadWork *iosCreateThreadS(void *entry, int unused, void *partition, int size, int priority, int flags)
{
    void *stack;
    ThreadWork *thread;
    stack = iosMallocAlign(partition, size, 16);
    thread = 0;
    if (!stack) {
        iosJumpRecoverPoint(RO_000426F8);
    } else {
        thread = iosCreateThread(entry, stack, size, priority, flags);
        if (thread)
            thread->flags |= 1;
        else
            iosFree(stack);
    }
    return thread;
}
