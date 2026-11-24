/* Parked: 21 diffs. The Original hoists only four of the five loop-invariant %hi loads, which this
   reproduces only with extra register pressure: r2 is never really assigned (its store sits before
   the first case label), so case 10 reads unk18 through an uninitialized pointer and this version
   is not behaviorally correct. The do/while(0) around the B_0014CAD0 stores is also needed.
   Remaining: port/slot and &B_0014CAD0 land in different callee-saved registers, and 0x400 is
   not kept in $s0 across the strcpy call. */
#ifdef NONMATCHING
typedef struct McStep {
    int arg;
    int (*fn)(void *);
} McStep;

typedef struct McReq {
    char name[0x20];
    int port;
    int slot;
    int unk28;
    int size;
    int unk30;
} McReq;

typedef struct McMsg {
    int type;
    int port;
    int slot;
    int name;
    int unk10;
    int unk14;
    int unk18;
    int unk1C;
    int unk20;
    int unk24;
    int unk28;
    int result;
} McMsg;

extern McStep *B_0014DB38;
extern McReq B_0014CAD0;
extern char B_0014DB10[];
extern char RO_0011AA90[];
extern char RO_0011AAB8[];
extern char RO_0011AAE8[];
extern void iosRecvMsg(void *, void *, int);
extern int iosMcGetInfo(int, int, void *);
extern int iosMcChDir(int, int, char *);
extern int iosMcFormat(int, int);
extern int iosMcUnformat(int, int);
extern int iosMcGetDir(int, int, int, int, int, int, int);
extern int iosMcDeleteFile(int, int, int);
extern int iosMcWriteFile(int, int, int, int, int, int);
extern int iosMcReadFile(int, int, int, int, int, int);
extern void LoaderSysPrintf(const char *, ...);
extern char *strcpy(char *, const char *);
extern void func_000CCCF0(McMsg *);
extern void func_000CD2B8(McMsg *);
extern void func_000CDAA8(McMsg *);
extern void func_000CDC38(McMsg *);
extern void func_000CDD98(McMsg *);

void mcManager(void)
{
    McMsg *msg;
    McMsg *r2;
    int info;
    for (;;) {
        McMsg *req;
        iosRecvMsg(B_0014DB10, &msg, 1);
        req = msg;
        switch (req->type) {
            r2 = req; /* unreachable: keeps r2 live across the loop */
        case 1:
            msg->result = iosMcGetInfo(req->port, req->slot, &info);
            break;
        case 2:
            func_000CCCF0(req);
            break;
        case 3:
            func_000CD2B8(req);
            break;
        case 4:
            func_000CDAA8(req);
            break;
        case 5:
            func_000CDC38(req);
            break;
        case 6: {
            int port = req->port;
            int slot = req->slot;
            McStep *s;
            if ((req->result = iosMcChDir(port, slot, RO_0011AA90)) != 0)
                break;
            strcpy(B_0014CAD0.name, RO_0011AAB8);
            B_0014CAD0.port = port;
            B_0014CAD0.slot = slot;
            do {
                B_0014CAD0.size = 0x400;
                B_0014CAD0.unk28 = 0x400;
                B_0014CAD0.unk30 = 0;
            } while (0);
            for (s = B_0014DB38; s->fn != 0; s++) {
                if ((req->result = s->fn(&B_0014CAD0)) != 0)
                    goto done;
            }
            req->result = 0;
            break;
        }
        case 7:
            req->result = iosMcFormat(req->port, req->slot);
            break;
        case 8:
            req->result = iosMcUnformat(req->port, req->slot);
            break;
        case 10:
            msg->result = iosMcGetDir(req->port, req->slot, req->name, r2->unk18, req->unk1C, req->unk20, req->unk24);
            break;
        case 11:
            func_000CDD98(req);
            break;
        case 12:
            req->result = iosMcDeleteFile(req->port, req->slot, req->name);
            break;
        case 14:
            req->result = iosMcWriteFile(req->port, req->slot, req->name, req->unk24, req->unk18, req->unk1C);
            break;
        case 13:
            req->result = iosMcReadFile(req->port, req->slot, req->name, req->unk24, req->unk18, req->unk1C);
            break;
        default:
            LoaderSysPrintf(RO_0011AAE8, msg->type);
            break;
        }
    done:
        msg->type = 0;
    }
}
#endif
