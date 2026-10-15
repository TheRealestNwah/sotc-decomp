extern char B_001848B0[];
extern int vschedGameTime;
extern int mcRead(int, void *, int);
extern void setSavedClock(void *);

int gStatMcLoad(int port)
{
    int r = mcRead(port, B_001848B0, 0x3C90);
    if (r == 0) {
        vschedGameTime = *(int *)(B_001848B0 + 0x3C34);
        setSavedClock(B_001848B0 + 0x3C48);
    }
    return r;
}
