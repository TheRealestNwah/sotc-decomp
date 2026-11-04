typedef struct {
    long long a;
    long long b;
    int idx;
    int pad14;
    long long d;
} PathPt;

typedef struct {
    PathPt cur;
    PathPt next;
    PathPt saveCur;
    PathPt saveNext;
    char pad80[0x18];
    int flag;
} PathWork;

typedef struct {
    int kind;
    char pad04[0xFC];
    char area[0x20];
    PathWork pw;
    char padBC[0x1F0 - 0x120 - sizeof(PathWork)];
    char special[1];
} Kite;

extern void KiteSpecial_SetNewPathPoint(PathPt *, void *, Kite *, void *);
extern void func_000ACDF0(PathPt *, void *, Kite *);

static PathPt *func_000AD410(Kite *k, int which)
{
    PathWork *pw = &k->pw;
    PathPt *p;

    if (which == 0) {
        pw->saveCur = pw->cur;
        if (pw->cur.idx == -1) {
            pw->cur.idx = 99;
            if (k->kind == 8)
                KiteSpecial_SetNewPathPoint(&pw->cur, k->special, k, k->area);
            else
                func_000ACDF0(&pw->cur, k->area, k);
        } else if (pw->flag != 0 && pw->next.idx != -1) {
            if (k->kind == 8)
                KiteSpecial_SetNewPathPoint(&pw->cur, k->special, k, &pw->saveCur);
            else
                pw->cur = pw->next;
        }
        return &pw->cur;
    }
    if (which == 1) {
        pw->saveNext = pw->next;
        if (pw->next.idx != -1) {
            p = &k->pw.next;
            if (pw->flag != 0)
                goto call;
            goto out;
        }
        pw->next.idx = 100;
    call:
        p = &pw->next;
        if (k->kind == 8)
            KiteSpecial_SetNewPathPoint(p, k->special, k, &pw->saveNext);
        else
            func_000ACDF0(p, k->area, k);
    out:
        return p;
    }
    return 0;
}
