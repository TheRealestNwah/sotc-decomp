typedef struct { void *func; int arg; } ITask;
extern ITask B_000C0730[];

void iosAddISchedulerTaskList(void *func, int arg)
{
    int i;
    for (i = 0; i < 3; i++) {
        if (B_000C0730[i].func == 0) {
            B_000C0730[i].func = func;
            B_000C0730[i].arg = arg;
            return;
        }
    }
    __asm__ __volatile__("break 0");
}
