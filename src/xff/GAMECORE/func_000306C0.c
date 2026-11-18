typedef struct BgmRequest {
    int handle;
    int attr;
    int state;
    float volume;
    float volL;
    float volR;
    float fade;
    int closeHandle;
    int *done;
    unsigned int flags;
    int arg28;
    int arg2C;
    int arg30;
} BgmRequest;

extern BgmRequest B_001888E8[3];
extern char gcGlobalVar[];
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
