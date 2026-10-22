typedef struct {
    char prefix[0x10];
    unsigned int callback : 24;
    unsigned int callbackFlags : 8;
    unsigned int context : 24;
    unsigned int contextFlags : 8;
} AllocationHeader;

extern int B_0004F5F8;
extern void WaitSema(int);
extern void SignalSema(int);

void iosMallocSetExecGarbageCallback(void *allocation, int callback, int context)
{
    AllocationHeader *header;
    WaitSema(B_0004F5F8);
    header = ((AllocationHeader **)allocation)[-1];
    header->callback = callback >> 2;
    header->context = context >> 2;
    SignalSema(B_0004F5F8);
}
