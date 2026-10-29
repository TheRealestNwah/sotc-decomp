extern int *DldSysUndefSymbol;
typedef struct { char pad0[0x40]; int *track; char pad44[0xC]; } DemoTrack;
typedef struct { int unknown0; unsigned int tracks; } DemoPackage;
static inline int resourceCount(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    return t != 0 && t != DldSysUndefSymbol ? t[3] : 0;
}
static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    return t != 0 && t != DldSysUndefSymbol ? (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}
void bgmDemoPackagePlay(DemoPackage *package)
{
    int count = resourceCount(&package->tracks);
    DemoTrack *track = (DemoTrack *)dldResolve(&package->tracks);
    if (count > 0) {
        int remaining = count;
        do {
            track->track[2] = 0;
            track++;
        } while (--remaining != 0);
    }
}
