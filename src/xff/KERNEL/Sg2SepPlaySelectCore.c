typedef struct {
    int status;
    int unk4;
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

extern Sep B_000DD700[];
extern int B_000DE100;
extern int DIntr(void);
/* The soft-double libcalls are called with 64-bit integer types: gcc 2.96 never puts a
   DFmode argument move in a call delay slot, and the Original fills the dpdiv slot. */
extern long litodp(long);
extern long dpdiv(long, long);
extern int EIntr(void);
extern int vab_check_alive(int);
extern int *vab_get_seseq(int, int, int);
extern int Sg2ModOpenSe(int, int);
extern int Sg2CtrlGetTickMode(void);
extern int Sg2SepSetParam(unsigned int, int, int, int);
extern void func_00025B50(int, int, int, unsigned int);

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
    sep->unk4 = 0;
    sep->seq = seq;
    if (limit != 0)
        func_00025B50(vab, seq, flags, limit);
end:
    if (enabled)
        EIntr();
    return ret;
}
