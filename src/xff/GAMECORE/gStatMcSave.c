extern char B_001848B0[];
extern int vschedGameTime;
extern void iosGetClock(long *);
extern int getSavedPlaceId(void);
extern int mcWrite(int, void *, int);
extern void setSavedClock(void *);
extern void setSavedGameTime(int);

int gStatMcSave(int port)
{
    long clk;
    int t = vschedGameTime;
    int r;

    iosGetClock(&clk);
    B_001848B0[0x3C20] = getSavedPlaceId();
    *(long *)(B_001848B0 + 0x3C48) = clk;
    *(int *)(B_001848B0 + 0x3C34) = t;
    r = mcWrite(port, B_001848B0, 0x3C90);
    if (r == 0) {
        setSavedClock(&clk);
        setSavedGameTime(t);
    }
    return r;
}
