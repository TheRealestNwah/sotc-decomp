typedef struct {
    int command;
    int arg1;
    int arg2;
    int arg3;
} RemoteCommand;

extern int B_000D9240;
extern RemoteCommand B_000D9280[];
extern int DIntr(void);
extern int EIntr(void);

int Sg2RemoteSend(int command, int arg1, int arg2, int arg3)
{
    int intr;

    B_000D9280[B_000D9240].command = command;
    B_000D9280[B_000D9240].arg1 = arg1;
    B_000D9280[B_000D9240].arg2 = arg2;
    B_000D9280[B_000D9240].arg3 = arg3;
    intr = DIntr();
    B_000D9240 = (B_000D9240 + 1) % 512;
    if (intr) {
        EIntr();
    }
    return 0;
}
