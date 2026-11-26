#include "gamecore/bgm.h"

extern BgmRequest B_001888E8[3];
extern char gcGlobalVar[];
extern void *adpcmScriptTickProc;
extern void *memset(void *, int, unsigned int);
extern void adpcmDeleteAdpcmSeq(int);
extern void initBgmScript(void);
extern void bgmScriptTickProc(void);
extern void adpcmSetVol(int, float, float);
extern int _adpcmOpenReq(int, unsigned char, int, int);
extern int adpcmOpenChkComplete(int);
extern void *SCRGetFirstObj(void *);
extern void adpcmPlay(int, float);
extern void adpcmCloseFadeReq(int, int *, float);
extern void adpcmCloseReq(int, int *);
extern int adpcmCloseChkComplete(int);
extern void bgmMinPriorityForceClose(int);

static inline void clearScriptFlags(AdpcmScriptWork *script)
{
    script->flags &= ~2;
    script->flags &= ~1;
}

void deleteAdpcmOrient(AdpcmOrient *orient)
{
    int remaining;
    AdpcmOrientEntry *entry = orient->entries;
    if (orient->count > 0) {
        remaining = orient->count;
        do {
            if (entry->slot != 0) {
                AdpcmSlot *slot;
                adpcmDeleteAdpcmSeq(entry->slot->fields.adpcm->handle);
                slot = entry->slot;
                if (slot->fields.state != 5 && slot->fields.state != 6) {
                    clearScriptFlags(slot->fields.script);
                    slot->fields.state = 5;
                    slot->fields.script->field40 = 0;
                }
                if (slot->fields.callback != 0)
                    slot->fields.callback(slot);
            }
            entry++;
            remaining--;
        } while (remaining != 0);
    }
}

static void func_000306C0(void)
{
    int i;
    BgmRequest *r;

    initBgmScript();
    bgmScriptTickProc();
    for (i = 0; i < 3; i++) {
        r = &B_001888E8[i];
        if (r->state == 0)
            continue;
        if (r->state != 1 && (r->flags >> 1) & 1) {
            adpcmSetVol(r->handle, r->volL, r->volR);
            r->flags &= ~2;
        }
        switch (r->state) {
        case 1:
            r->handle = _adpcmOpenReq(r->arg28, r->attr, r->arg2C, r->arg30);
            r->state = 2;
            break;
        case 2:
            if (adpcmOpenChkComplete(r->handle))
                r->state = (r->attr & 1) ? 4 : 3;
            break;
        case 3:
            if (r->flags & 1)
                r->state = 4;
            if (!((r->flags >> 2) & 1)) {
                if (!(r->attr & 0x100))
                    break;
                if (SCRGetFirstObj(gcGlobalVar + 0x2B8))
                    break;
            }
            r->state = 7;
            break;
        case 4:
            adpcmPlay(r->handle, r->volume);
            r->state = 5;
            break;
        case 5:
            if ((r->attr & 0x100) && !SCRGetFirstObj(gcGlobalVar + 0x2B8)) {
                r->fade = 0.2f;
                r->flags |= 4;
            }
            if ((r->flags >> 2) & 1)
                r->state = (r->fade != 0.0f) ? 6 : 7;
            break;
        case 6:
            adpcmCloseFadeReq(r->handle, &r->closeHandle, r->fade);
            r->state = 8;
            break;
        case 7:
            adpcmCloseReq(r->handle, &r->closeHandle);
            r->state = 8;
            break;
        case 8:
            if (!adpcmCloseChkComplete(r->closeHandle))
                break;
            r->state = 9;
        case 9:
            if (r->done)
                *r->done = 1;
            r->state = 0;
            break;
        }
    }
}

static inline BgmRequest *allocBgmRequest(int a0, int attr, int a2, int a3)
{
    int i;
    BgmRequest *req;

    for (i = 0; i < 3; i++) {
        if (B_001888E8[i].state == 0) {
            goto found;
        }
    }
    return 0;
found:
    req = &B_001888E8[i];
    memset(req, 0, sizeof(BgmRequest));
    req->arg28 = a0;
    req->attr = attr;
    req->arg2C = a2;
    req->arg30 = a3;
    return req;
}

BgmRequest *bgmAutoStart(int a0, int attr, int a2, int a3)
{
    BgmRequest *req = allocBgmRequest(a0, attr | 1, a2, a3);
    BgmRequest *ret = 0;

    if (req != 0) {
        req->state = 1;
        req->volume = 100.0f;
        ret = req;
    }
    return ret;
}

BgmRequest *bgmStandbyWithPri(int a0, int attr, int a2, int a3, int priority)
{
    BgmRequest *req = allocBgmRequest(a0, attr, a2, a3);

    if (req == 0) {
        bgmMinPriorityForceClose(priority);
        return 0;
    }
    req->state = 1;
    return req;
}

BgmRequest *bgmStandby(int a0, int attr, int a2, int a3)
{
    BgmRequest *req = allocBgmRequest(a0, attr, a2, a3);
    BgmRequest *ret;

    if (req == 0) {
        bgmMinPriorityForceClose(100);
        ret = 0;
    } else {
        req->state = 1;
        ret = req;
    }
    return ret;
}

int bgmChkStandbyComplete(BgmRequest *req)
{
    if (req->state == 1)
        return 0;
    return adpcmOpenChkComplete(req->handle);
}

void bgmPlay(BgmRequest *req, float volume)
{
    req->volume = volume;
    req->flags |= 1;
}

void bgmStop(BgmRequest *req, int *done, float time)
{
    req->fade = time;
    if (done != 0) {
        *done = 0;
    }
    req->done = done;
    req->flags |= 4;
}

int bgmStopChk(int done)
{
    return done;
}

void bgmStopAllAttr(int attr, int time)
{
    BgmRequest *req;
    int n;

    n = 2;
    req = B_001888E8;
    do {
        n -= 1;
        if (req->state != 0 && (req->attr & attr)) {
            req->done = 0;
            req->flags |= 4;
            req->fade = (float)time;
        }
        req++;
    } while (n >= 0);
}

void bgmChangeVol(BgmRequest *req, float volL, float volR)
{
    req->volR = volR;
    req->volL = volL;
    req->flags |= 2;
}

void bgmStartGameOver(void)
{
}

void bgmEndGameOver(void)
{
}

void bgmStageInit(void)
{
}

int CreateBgmThread(void)
{
    adpcmScriptTickProc = func_000306C0;
    memset(B_001888E8, 0, sizeof(B_001888E8));
    return 0;
}
