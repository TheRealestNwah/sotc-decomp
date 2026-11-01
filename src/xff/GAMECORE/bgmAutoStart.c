typedef struct BgmRequest {
    int field0;
    int attr;
    int active;
    float volume;
    char pad10[0x18];
    int arg28;
    int arg2C;
    int arg30;
} BgmRequest;

extern BgmRequest B_001888E8[3];
extern void *memset(void *, int, unsigned int);
extern void bgmMinPriorityForceClose(int);

static inline BgmRequest *allocBgmRequest(int a0, int attr, int a2, int a3)
{
    int i;
    BgmRequest *req;

    for (i = 0; i < 3; i++) {
        if (B_001888E8[i].active == 0) {
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
        req->active = 1;
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
    req->active = 1;
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
        req->active = 1;
        ret = req;
    }
    return ret;
}
