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

typedef struct {
    char pad0[0x24];
    void *serve;
} SifClientData;

typedef struct { int v; char pad[0x10]; } RemoteDmaStatus;

typedef struct {
    int status;
    int previous;
    int serial;
    int vab;
    int mod;
    int seq;
    int flags;
    int pad1C;
    double tick;
    double time;
    double count;
    int unk38;
    int data;
    int *head;
    char pad44[0xC];
} Sep;

typedef struct {
    char pad0[0x8];
    unsigned int val;
    int a;
    int pad10;
    int b;
    int c;
    char pad1C[0x50 - 0x1C];
} SepEntry;

typedef struct {
    int idx;
    unsigned int val;
} Cand;

typedef struct { int mod; char pad[0x4C]; } Sg2Sep;

extern int B_000D9240;
extern int B_000D9244;
extern RemoteCommand B_000D9280[];
extern RemoteCommand B_000DB280[];
extern RemoteResult B_000DD280;
extern char B_000DD340[];
extern int B_000DD400;
extern char B_000DD408[];
extern SifClientData B_000DD440;
extern int B_000DD468;
extern int B_000DD46C;
extern RemoteRequest B_000DD480[];
extern RemoteDmaStatus B_000DD490[];
extern Sep B_000DD700[];
extern Sg2Sep B_000DD710[];
extern int B_000DE100;

extern int DIntr(void);
extern int EIntr(void);
extern void *memcpy(void *, const void *, unsigned int);
extern void *memset(void *, int, unsigned int);
extern int sceSifCallRpc(void *, int, int, void *, int, void *, int, void *, void *);
extern int sceSifCheckStatRpc(void *);
extern int sceSifBindRpc(SifClientData *, int, int);
extern void Sg2CtrlEntryTickProcById(int, void (*)(void));
/* The soft-double libcalls are called with 64-bit integer types: gcc 2.96 never puts a
   DFmode argument move in a call delay slot, and the Original fills the dpdiv slot. */
extern long litodp(long);
extern long dpdiv(long, long);
extern int vab_check_alive(int);
extern int *vab_get_seseq(int, int, int);
extern int Sg2ModOpenSe(int, int);
extern int Sg2CtrlGetTickMode(void);
extern void Sg2ModMidiout1(int, int);
extern int Sg2ModSetParam(int, int, int, int);
extern int Sg2ModCheckSndOn(int);

int Sg2RemoteSend(int command, int arg1, int arg2, int arg3);
void Sg2RemoteTickProc(void);
int Sg2SepPlaySelectCore(int vab, int seq, int flags, int limit, int mode);
static void func_00025B50(int a, int b, int c, unsigned int limit);
int Sg2SepStopSndOff(unsigned int id);
int Sg2SepSetParam(unsigned int id, int selector, int value, int extra);

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

int Sg2RemoteSendDmaCom(int command, int arg1, int arg2, int arg3)
{
    int index = B_000DD468;
    int intr;

    B_000DD480[index].state = -1;
    B_000DD480[index].cmd.command = command;
    B_000DD480[index].cmd.arg1 = arg1;
    B_000DD480[index].cmd.arg2 = arg2;
    B_000DD480[index].cmd.arg3 = arg3;
    intr = DIntr();
    B_000DD468 = (B_000DD468 + 1) % 32;
    if (intr) {
        EIntr();
    }
    return index;
}

int Sg2RemoteDmaTransStatus(int i)
{
    return B_000DD490[i].v;
}

int Sg2RemoteGetAdpStmAdr(int i)
{
    return ((int *)B_000DD340)[i];
}

int Sg2RemoteGetPcmStmTransOffset(void)
{
    return B_000DD400;
}

int Sg2RemoteGetSlotReleaseLv(int i)
{
    return ((int *)&B_000DD280)[i];
}

int Sg2RemoteGetDspChangeStatus(int i)
{
    return ((int *)B_000DD408)[i];
}

int Sg2RemoteSyncStatus(void)
{
    return sceSifCheckStatRpc(&B_000DD440);
}

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
    sceSifCallRpc(&B_000DD440, 0, 1, B_000DB280, (n + wrap) * sizeof(RemoteCommand), &B_000DD280,
                  0x190, 0, 0);
    B_000D9244 = B_000D9240;
    if (B_000DD480[B_000DD46C].state == -2 && B_000DD280.busy == 0) {
        B_000DD480[B_000DD46C].state = 0;
        B_000DD46C = (B_000DD46C + 1) % 32;
    }
}

int Sg2RemoteInit(void)
{
    int i;

    memset(B_000D9280, 0, 0x2000);
    B_000D9240 = 0;
    B_000D9244 = 0;
    memset(B_000DD480, 0, 0x280);
    B_000DD468 = B_000DD46C = 0;
    do {
        if (sceSifBindRpc(&B_000DD440, 0x11223344, 0) < 0)
            return -1;
        i = 10000;
        do {
            i -= 625;
            __asm__ volatile("nop");
        } while (i > 0);
    } while (B_000DD440.serve == 0);
    Sg2CtrlEntryTickProcById(4, Sg2RemoteTickProc);
    return 0;
}


static void func_00025B50(int a, int b, int c, unsigned int limit)
{
    Cand list[48];
    Cand best;
    Cand *p;
    SepEntry *tbl = (SepEntry *)B_000DD700;
    int *e = &tbl->pad10;
    unsigned int n = 0;
    unsigned int *v;
    int i;

    for (i = 0, p = list; i < 32; i++, e += 0x14) {
        if (e[-1] == a && e[1] == b && e[2] == c) {
            p->idx = i;
            p->val = e[-2];
            p++;
            n++;
        }
    }
    if (limit < n) {
        best.idx = list[0].idx;
        best.val = list[0].val;
        i = 1;
        if (i < n) {
            v = &list[1].val;
            do {
                if (*v < best.val) {
                    best.idx = v[-1];
                    best.val = v[0];
                }
                i++; v += 2;
            } while (i < n);
        }
        Sg2SepStopSndOff(best.idx);
        ((SepEntry *)B_000DD700)[best.idx].b = -1;
    }
}

int Sg2SepPlay(int a, int b, int c, int d)
{
    return Sg2SepPlaySelectCore(a, b, c, d, 2);
}

int Sg2SepPlaySelectCore(int vab, int seq, int flags, int limit, int mode)
{
    Sep *sep;
    int enabled;
    int ret;
    int id;
    int cnt;
    int i;
    int n;
    int mod;
    int *p;

    enabled = DIntr();
    if (vab_check_alive(vab) == 0) {
        ret = -4;
        goto end;
    }
    id = -1;
    p = &B_000DE100;
    cnt = *p;
    for (i = 0; i < 32; i++) {
        n = (cnt + i) % 32;
        if (B_000DD700[n].status == 0) {
            B_000DD700[n].serial = cnt;
            id = n;
            *p = cnt + 1;
            break;
        }
    }
    ret = -3;
    if (id == -1)
        goto end;
    ret = id;
    sep = &B_000DD700[id];
    if (flags & 0x10000) {
        flags &= ~0x10000;
        Sg2SepSetParam(id, 0x200, 1, 0);
    }
    sep->vab = vab;
    sep->head = vab_get_seseq(vab, seq, flags);
    if (sep->head == 0) {
        ret = -1;
        goto end;
    }
    mod = Sg2ModOpenSe(vab, mode);
    if (mod == -1) {
        ret = -2;
        goto end;
    }
    sep->mod = mod;
    sep->time = 0;
    sep->count = 0;
    sep->data = (int)sep->head;
    *(long *)&sep->tick = dpdiv(0x407E000000000000 /* 480.0 */, litodp(Sg2CtrlGetTickMode()));
    sep->unk38 = 0;
    sep->status = 1;
    sep->flags = flags;
    sep->previous = 0;
    sep->seq = seq;
    if (limit != 0)
        func_00025B50(vab, seq, flags, limit);
end:
    if (enabled)
        EIntr();
    return ret;
}

int Sg2SepStop(unsigned int id)
{
    Sep *sep;
    int enabled;

    if (id < 32) {
        sep = &B_000DD700[id];
        if (sep->status > 0) {
            enabled = DIntr();
            sep->status = 2;
            sep->vab = -1;
            Sg2ModMidiout1(B_000DD700[id].mod, 0xFF);
            Sg2ModMidiout1(B_000DD700[id].mod, 0x40);
            Sg2ModMidiout1(B_000DD700[id].mod, 0xF7);
        }
        if (enabled) {
            EIntr();
        }
    }
    return 0;
}

int Sg2SepStopSndOff(unsigned int id)
{
    Sep *sep;
    int enabled;
    if (id < 32) {
        sep = &B_000DD700[id];
        if (sep->status > 0) {
            enabled = DIntr();
            sep->status = 2;
            sep->vab = -1;
            Sg2ModMidiout1(B_000DD700[id].mod, 0xFF);
            Sg2ModMidiout1(B_000DD700[id].mod, 0x41);
            Sg2ModMidiout1(B_000DD700[id].mod, 0xF7);
            if (enabled) {
                EIntr();
            }
        }
    }
    return 0;
}

int Sg2SepPause(unsigned int id, int mode)
{
    Sep *sep;
    int enabled;
    if (id < 32) {
        sep = &B_000DD700[id];
        if ((unsigned int)(sep->status - 1) < 2) {
            enabled = DIntr();
            sep->previous = sep->status;
            Sg2ModSetParam(B_000DD700[id].mod, 0x80, 1, 0);
            Sg2ModSetParam(B_000DD700[id].mod, 0x10, mode, 0);
            if (mode != 0) {
                sep->status = 3;
            } else {
                sep->status = 4;
            }
            if (enabled) {
                EIntr();
            }
        }
    }
    return 0;
}


int Sg2SepCont(unsigned int id)
{
    Sep *sep;
    int enabled;
    if (id < 32) {
        sep = &B_000DD700[id];
        if ((unsigned int)(sep->status - 3) < 2) {
            enabled = DIntr();
            Sg2ModSetParam(B_000DD700[id].mod, 0x80, 0, 0);
            Sg2ModSetParam(B_000DD700[id].mod, 0x10, 0, 0);
            sep->status = sep->previous;
            if (enabled) {
                EIntr();
            }
        }
    }
    return 0;
}

int Sg2SepVabStopSndOff(int vab)
{
    int i;
    Sep *s;
    if (vab_check_alive(vab)) {
        s = B_000DD700;
        for (i = 0; i < 32; i++, s++) {
            if (s->vab == vab)
                Sg2SepStopSndOff(i);
        }
    }
    return 0;
}

int Sg2SepAllStopSndOff(void)
{
    int i;
    for (i = 0; i < 32; i++)
        Sg2SepStopSndOff(i);
    return 0;
}

int Sg2SepStatus(unsigned int id)
{
    if (id < 0x20) {
        return B_000DD700[id].status;
    }
    return 0;
}

int Sg2SepCheckSndOn(unsigned int i)
{
    if (i < 32)
        Sg2ModCheckSndOn(B_000DD710[i].mod);
    return 0;
}

int Sg2SepSetParam(unsigned int id, int selector, int value, int extra)
{
    if (id < 32) {
        switch (selector) {
        case 2:
            Sg2ModSetParam(B_000DD700[id].mod, 1, value, extra);
            break;
        case 0x400:
            Sg2ModSetParam(B_000DD700[id].mod, 0x10000, value, extra);
            break;
        case 4:
            Sg2ModSetParam(B_000DD700[id].mod, 4, value, extra);
            break;
        case 8:
            Sg2ModSetParam(B_000DD700[id].mod, 0x10, 1, 0);
            break;
        case 0x10:
            Sg2ModSetParam(B_000DD700[id].mod, 0x10, 0, 0);
            break;
        case 0x20:
            Sg2ModSetParam(B_000DD700[id].mod, 0x100, value, extra);
            break;
        case 0x40:
            Sg2ModSetParam(B_000DD700[id].mod, 0x200, value, 0);
            break;
        case 0x80:
            Sg2ModSetParam(B_000DD700[id].mod, 0x400, value, extra);
            break;
        case 0x100:
            Sg2ModSetParam(B_000DD700[id].mod, 0x800, value, extra);
            break;
        case 0x200:
            Sg2ModSetParam(B_000DD700[id].mod, 0x1000, value, extra);
            break;
        }
    }
    return 0;
}
