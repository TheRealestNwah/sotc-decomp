typedef struct {
    int unk0;
    int unk4;
    int unk8;
    int unkC;
    float scale;
    int unk14;
    char pad18[0x18];
    int unk30;
    char link[0xC];
    int linked;
} GazeCtrlWork;

typedef struct Link { struct Link *next; struct Link *prev; } Link;
extern int DeleteTwoWayLink(Link *);
extern void InitTwoWayLink(void *, int *);

void initGazeCtrlWork(GazeCtrlWork *w)
{
    InitTwoWayLink(w->link, &w->linked);
    w->linked = 0;
    w->unk4 = 1;
    w->unk0 = 0;
    w->unk8 = 0;
    w->unk14 = 0;
    if (w->linked != 0) {
        w->linked = 0;
        DeleteTwoWayLink((Link *)(w->link));
    }
    w->unk30 = 0;
    w->unkC = 0;
    w->scale = 1.0f;
}
