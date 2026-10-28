typedef struct {
    int command;
    int arg1;
    int arg2;
    int arg3;
    int status;
} RemoteDmaCommand;

extern int B_000DD468;
extern RemoteDmaCommand B_000DD480[];
extern int DIntr(void);
extern int EIntr(void);

int Sg2RemoteSendDmaCom(int command, int arg1, int arg2, int arg3)
{
    int index = B_000DD468;
    int intr;

    B_000DD480[index].status = -1;
    B_000DD480[index].command = command;
    B_000DD480[index].arg1 = arg1;
    B_000DD480[index].arg2 = arg2;
    B_000DD480[index].arg3 = arg3;
    intr = DIntr();
    B_000DD468 = (B_000DD468 + 1) % 32;
    if (intr) {
        EIntr();
    }
    return index;
}
