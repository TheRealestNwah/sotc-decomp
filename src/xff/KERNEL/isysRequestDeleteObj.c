typedef struct Object {
    int partition;
    int pc;
    union {
        unsigned int word;
        struct { unsigned char type; unsigned char mark; unsigned short flags; } bytes;
    } header;
    unsigned short first;
    unsigned short second;
    int next;
    int entry;
    int immediateDelete;
} Object;
extern int GetThreadId(void);
extern void WaitSema(int);
extern void SignalSema(int);
extern int D_00040D5C, D_00040D60;
extern int B_000BF6CC, B_000BF6C8;

static inline void unlockObjects(void)
{
    int *p = &D_00040D60;
    if (--*p == 0) {
        D_00040D5C = -1;
        SignalSema(B_000BF6CC);
    }
}

static inline void lockObjects(void)
{
    int thread = GetThreadId();
    if (thread == D_00040D5C) {
        D_00040D60++;
        return;
    }
    WaitSema(B_000BF6CC);
    D_00040D5C = thread;
    D_00040D60 = 1;
}

void isysRequestDeleteObj(Object *object)
{
    /* Preserve the caller PC used to tag the deletion request. */
    register void *ra __asm__("$31");
    int pc = (int)ra;
    if (object->immediateDelete) {
        ((void (*)(Object *))object->immediateDelete)(object);
        object->immediateDelete = 0;
    }
    lockObjects();
    object->pc = pc;
    object->header.word |= 0x10000;
    object->next = B_000BF6C8;
    B_000BF6C8 = (int)object;
    unlockObjects();
}
