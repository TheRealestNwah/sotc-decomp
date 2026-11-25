struct AdpcmChannel {
    int active;
    char pad04[0x34];
    unsigned long flags;
    char pad40[0xC];
    float vol;
    float volStep;
    float lastMaster;
    float volTarget;
    float pitch;
    float pitchTarget;
    float pitchStep;
    float pan;
    float lastPan;
    char pad70[0x210];
    char handle[0x2E0];
};

extern int D_00139BE8;
extern float D_00139BF0;
extern struct AdpcmChannel B_0014E898[];
extern int B_0014F8B8;

extern int WaitSema(int);
extern int SignalSema(int);
extern void Sg2ExStAdpcmVolumePercent(void *, int);
extern void Sg2ExStAdpcmTrkVolumeDirect(void *, int, int, int);
extern void Sg2ExStAdpcmPitchPercent(void *, int);

static void func_000DBC88(void)
{
    int i;
    struct AdpcmChannel *c;
    float step, pan, t, v, l, r, p, d;
    int done;
    int li, ri;
    float *mp;

    if (D_00139BE8) {
        mp = &D_00139BF0;
        *mp = (*mp < 0.53f) ? 0.5f : *mp - 0.03f;
    } else {
        mp = &D_00139BF0;
        *mp = (0.97f < *mp) ? 1.0f : *mp + 0.03f;
    }

    WaitSema(B_0014F8B8);
    for (i = 0; i < 3; i++) {
        c = &B_0014E898[i];
        if (c->active == 0) {
            continue;
        }
        if (!((c->flags >> 33) & 1)) {
            continue;
        }
        step = c->volStep;
        pan = c->pan;
        if (step == 0.0f && c->lastMaster == D_00139BF0 && pan == c->lastPan) {
            continue;
        }
        done = 0;
        t = c->volTarget;
        t = (t > 100.0f) ? 100.0f : ((t < 0.0f) ? 0.0f : t);
        c->volTarget = t;
        c->lastMaster = D_00139BF0;
        if (c->vol < t) {
            c->vol = c->vol + step;
            if (t <= c->vol) {
                done = 1;
            }
        } else if (t < c->vol) {
            c->vol = c->vol - step;
            if (c->vol <= t) {
                done = 1;
            }
        } else {
            done = 1;
        }
        if (done) {
            c->volStep = 0.0f;
            c->vol = c->volTarget;
        }
        c->lastPan = pan;
        v = c->vol * D_00139BF0;
        if (pan == 0.0f) {
            Sg2ExStAdpcmVolumePercent(c->handle, (int)v);
        } else {
            v = v * 127.0f;
            l = v;
            r = v;
            if (0.0f < pan) {
                /* Keeps v in $f1 so left scales it rather than its copy in r. */
                __asm__("" : "+f"(v));
                l = v * (1.0f - pan);
            }
            if (pan < 0.0f) {
                r = r * (pan + 1.0f);
            }
            li = (int)l;
            ri = (int)r;
            Sg2ExStAdpcmTrkVolumeDirect(c->handle, 0, li, ri);
            Sg2ExStAdpcmTrkVolumeDirect(c->handle, 1, li, ri);
        }
        p = c->pitch;
        if (p == c->pitchTarget) {
            continue;
        }
        d = c->pitchTarget - p;
        if (0.0f < d && c->pitchStep < d) {
            d = c->pitchStep;
        } else if (d < 0.0f && d < -c->pitchStep) {
            d = -c->pitchStep;
        }
        c->pitch = p + d;
        Sg2ExStAdpcmPitchPercent(c->handle, (int)(p + d));
    }
    SignalSema(B_0014F8B8);
}
