typedef struct {
    char pad0[0x380];
    int f380;
    char pad1[0x408 - 0x384];
    int f408;
} Way;

int getWayFinish(Way *way)
{
    int finished = 0;
    if (way->f408 != 0) {
        finished = way->f380 == 0;
    }
    return finished;
}
