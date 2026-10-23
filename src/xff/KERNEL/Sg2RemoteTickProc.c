typedef struct {
    int command;
    int arg1;
    int arg2;
    int arg3;
} RemoteCommand;

typedef struct {
    RemoteCommand cmd;
    int state;
} RemoteRequest;

typedef struct {
    char pad0[0x184];
    int busy;
    char pad188[8];
} RemoteResult;

extern int B_000D9240;
extern int B_000D9244;
extern RemoteCommand B_000D9280[];
extern RemoteCommand B_000DB280[];
extern RemoteResult B_000DD280;
extern char B_000DD440[];
extern int B_000DD46C;
extern RemoteRequest B_000DD480[];
extern int Sg2RemoteSend(int command, int arg1, int arg2, int arg3);
extern void *memcpy(void *, const void *, unsigned int);
extern int sceSifCallRpc(void *, int, int, void *, int, void *, int, void *, void *);

void Sg2RemoteTickProc(void)
{
    int n;
    int wrap = 0;

    if (B_000DD480[B_000DD46C].state == -1) {
        B_000DD480[B_000DD46C].state = -2;
        B_000DD280.busy = 1;
        Sg2RemoteSend(B_000DD480[B_000DD46C].cmd.command, B_000DD480[B_000DD46C].cmd.arg1,
                      B_000DD480[B_000DD46C].cmd.arg2, B_000DD480[B_000DD46C].cmd.arg3);
    }
    if (B_000D9244 > B_000D9240) {
        wrap = B_000D9240;
        n = 512 - B_000D9244;
    } else {
        n = B_000D9240 - B_000D9244;
    }
    if (n) {
        memcpy(B_000DB280, &B_000D9280[B_000D9244], n * sizeof(RemoteCommand));
    }
    if (wrap) {
        memcpy(&B_000DB280[n], B_000D9280, wrap * sizeof(RemoteCommand));
    }
    sceSifCallRpc(B_000DD440, 0, 1, B_000DB280, (n + wrap) * sizeof(RemoteCommand), &B_000DD280,
                  0x190, 0, 0);
    B_000D9244 = B_000D9240;
    if (B_000DD480[B_000DD46C].state == -2 && B_000DD280.busy == 0) {
        B_000DD480[B_000DD46C].state = 0;
        B_000DD46C = (B_000DD46C + 1) % 32;
    }
}
