typedef struct {
    int active;
    int cmd;
    int info[2];
    int changed;
    int mask;
    int pad18;
    int done;
    int loaded;
    int port;
    int idx;
    int x2C;
    int pad30[2];
    char buf[0x6C8];
    signed char *place;
} McWork;

extern int mcGetInfo(int, int);
extern int mcGetMainDataInfo(int, int, void *);
extern int mcGetLastSaveGameDataIndex(void *);
extern int mcLoadGameData(int, int, int, void *);
extern int mcLoadOptionData(int, int);
extern int mcSaveGameData(int, int, int, void *, void *);
extern int mcFormat(int, int);
extern int getSavedPlaceId(void);
extern void setSavedPlaceId(int);
extern void *gStatGetOmakeStatAdrs(void);
extern void gstatBootMcCurSetLastSaveOmakeStat(void);
extern void scrRun(void);
extern int (*B_0018B6A0)(void);

static inline int mcOk(int r)
{
    int ok;
    if (r == 0 || r == 2 || r == 3 || r == 5)
        ok = 1;
    else
        ok = 0;
    return ok;
}

static inline int mcNeedFormat(int r)
{
    int ok;
    if (r == 3 || r == 5)
        ok = 1;
    else
        ok = 0;
    return ok;
}

static void func_000650F0(McWork *w)
{
    int i;
    int old;

    int saved;

    while (w->active) {
        old = w->mask;
        switch (w->cmd) {
        case 1:
            for (i = 0; i < 2; i++) {
                if (mcOk(w->info[i] = mcGetInfo(i, 0)))
                    w->mask |= 1 << i;
                else
                    w->mask &= ~(1 << i);
            }
            if (old != w->mask)
                w->changed = 1;
            break;
        case 2:
            w->x2C = 0;
            for (i = 0; i < 2; i++) {
                if (mcOk(w->info[i] = mcGetInfo(i, 0)))
                    w->mask |= 1 << i;
                else
                    w->mask &= ~(1 << i);
            }
            goto done;
        case 3:
            w->x2C = 0;
            if (mcOk(w->info[w->port] = mcGetInfo(w->port, 0))) {
                if ((w->info[w->port] = mcGetMainDataInfo(w->port, 0, w->buf)) == 0) {
                    w->idx = mcGetLastSaveGameDataIndex(w->buf);
                    if ((unsigned int)w->idx >= 10)
                        w->idx = 0;
                }
            }
            goto done;
        case 4:
            w->x2C = 0;
            if (!mcOk(w->info[w->port] = mcGetInfo(w->port, 0)))
                goto fail;
            i = 0;
            if (B_0018B6A0 != 0)
                i = B_0018B6A0() == 0;
            if ((w->info[w->port] = mcLoadGameData(w->port, 0, w->idx, w->buf)) != 0)
                goto fail;
            if (i && mcLoadOptionData(w->port, 0) != 0)
                goto fail;
        loaded:
            w->loaded = 1;
            goto done;
        case 5:
            w->x2C = 0;
            if (!mcOk(w->info[w->port] = mcGetInfo(w->port, 0)))
                goto fail;
            saved = getSavedPlaceId();
            setSavedPlaceId(w->place != 0 ? w->place[1] : 99);
            if ((w->info[w->port] = mcSaveGameData(w->port, 0, w->idx, gStatGetOmakeStatAdrs(), w->buf)) != 0) {
                w->loaded = 0;
                w->idx = -1;
                setSavedPlaceId(saved);
                goto done;
            }
            gstatBootMcCurSetLastSaveOmakeStat();
            goto loaded;
        fail:
            w->loaded = 0;
            w->idx = -1;
            goto done;
        case 6:
            w->x2C = 0;
            if (mcNeedFormat(w->info[w->port] = mcGetInfo(w->port, 0)))
                w->info[w->port] = mcFormat(w->port, 0);
            goto done;
        done:
            w->cmd = 0;
            w->done = 1;
            break;
        }
        scrRun();
    }
}
