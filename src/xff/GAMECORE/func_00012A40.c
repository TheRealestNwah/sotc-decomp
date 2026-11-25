/* Ending-flow ADPCM tick thread (created by endingflow_create_adpcm_tick_proc): clears the three ADPCM entries, then until the tick reaches -2 plays each standby entry once the tick passes its start time (advancing the request pointer), starts the release script for entries past their end time or flagged, queues the next request when nothing is pending, and tops up the player HP by the per-frame rate until full; on exit releases every remaining entry. */
typedef struct {
    int x;
    int y;
    int id;
} AdpcmReq;

typedef struct {
    int a;
    int b;
    int started;
    int valid;
    AdpcmReq req;
} AdpcmEntry;

extern AdpcmReq *D_0017A010;
extern float D_0017A00C;
extern AdpcmEntry B_00183E10[];
extern int B_00183E64;
extern char rootPtn[];
extern const char RO_0017CAB0[];
typedef struct { char pad[0x180]; float dt; } GcGlobal;
extern GcGlobal gcGlobalVar;
extern void func_00013AF0(void);
extern void func_00013B20(void);
extern int bgmStandby(int, int, void *, void *);
extern void bgmPlay(int, float);
extern void gcCreateScriptObj(void *, void *, void *, int, int, int, const char *);
extern int isysGetThisSubThread(void);
extern void scrInit(int);
extern void scrRun(void);
extern void *memset(void *, int, unsigned int);
extern void addPlayerHp(float);
extern float getPlayerMaxHp(void);
extern float getPlayerHp(void);

static inline AdpcmEntry *startEntry(AdpcmReq *req)
{
    AdpcmEntry *e;
    int i;

    for (i = 0; i < 3; i++) {
        if (B_00183E10[i].valid == 0)
            goto found;
    }
    return 0;
found:
    e = &B_00183E10[i];
    e->req = *req;
    if ((e->valid = bgmStandby(e->req.id, 0, func_00013AF0, e)) != 0)
        e->a = 1;
    return e;
}

static void func_00012A40(void)
{
    AdpcmEntry *e;
    int i;
    int t;
    int n;

    scrInit(isysGetThisSubThread());
    memset(B_00183E10, 0, 0x54);
    D_0017A010 = 0;
    B_00183E64 = 0;
    D_0017A00C = 0.0f;
    while (B_00183E64 != -2) {
        t = B_00183E64;
        n = 0;
        for (i = 0; i < 3; i++) {
            e = &B_00183E10[i];
            if (e->valid == 0)
                continue;
            if (e->a != 0) {
                n++;
                if (t >= e->req.x) {
                    bgmPlay(e->valid, 100.0f);
                    e->a = 0;
                    if (D_0017A010 != 0)
                        D_0017A010++;
                }
            } else if ((e->req.y < t || e->b != 0) && e->started == 0) {
                e->started = 1;
                gcCreateScriptObj(func_00013B20, e, rootPtn, 0x1000, 0, 4, RO_0017CAB0);
            }
        }
        if (D_0017A010 != 0 && n == 0 && D_0017A010->id != 0)
            startEntry(D_0017A010);
        if (D_0017A00C != 0.0f) {
            addPlayerHp(gcGlobalVar.dt * D_0017A00C);
            if (getPlayerMaxHp() == getPlayerHp())
                D_0017A00C = 0.0f;
        }
        scrRun();
    }
    for (i = 0; i < 3; i++) {
        e = &B_00183E10[i];
        if (e->valid != 0 && e->started == 0) {
            e->started = 1;
            gcCreateScriptObj(func_00013B20, e, rootPtn, 0x1000, 0, 4, RO_0017CAB0);
        }
    }
}
