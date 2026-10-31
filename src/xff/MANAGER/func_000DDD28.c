typedef struct SndSep {
    char pad0[0x18];
    float vol;
    float curVol;
    char pad20[0x3C - 0x20];
    void (*onStop)(struct SndSep *);
} SndSep;

extern void sndSepSetVol(SndSep *, float);

static int func_000DDD28(SndSep *s)
{
    if (s->onStop != 0)
        s->onStop(s);
    s->curVol = s->vol;
    sndSepSetVol(s, 1.0f);
    return 0;
}
