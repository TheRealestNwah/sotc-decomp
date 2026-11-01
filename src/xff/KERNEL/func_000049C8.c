typedef struct Thr Thr;
extern void iosWakeupThread(Thr *t);

static void func_000049C8(Thr *t)
{
    iosWakeupThread(t);
}

typedef struct WaitNode {
    char pad[0x28];
    struct WaitNode *next;
} WaitNode;

static void T_000049E0(WaitNode *n)
{
    while (n != 0) {
        iosWakeupThread((Thr *)n);
        n = n->next;
    }
}
