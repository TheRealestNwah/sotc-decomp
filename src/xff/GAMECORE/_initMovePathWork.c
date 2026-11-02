typedef struct {
    char pad0[0xE];
    unsigned short type;
    char pad10[4];
        float speed;
} LineData;

typedef struct {
    char pad0[0x16];
    short line;
    char pad18[4];
    int idx;
} PathPoint;

typedef struct {
    int pad0;
    int area;
    int pad8;
    int start;
    int end;
} PathWork;

typedef union {
    struct {
        float speed;
        int startLine;
        int endLine;
    } s;
    float f;
} MovePathWork;

extern LineData *getLineDataByAreaIdx(int, short, int);

void _initMovePathWork(PathWork *pw, MovePathWork *mw, float speed)
{
    int area = pw->area;
    LineData *ld;
    float s;

    mw->s.speed = speed;
    mw->s.startLine = 0;
    mw->s.endLine = 0;
    if (pw->start != 0) {
        ld = getLineDataByAreaIdx(area, ((PathPoint *)pw->start)->line, ((PathPoint *)pw->start)->idx);
        if (ld != 0 && ld->type > 0x80) {
            mw->s.startLine = 1;
            mw->s.speed = ld->speed;
            if (mw->s.speed < 1.0f)
                mw->s.speed = 1.0f;
        }
    }
    if (pw->end != 0) {
        ld = getLineDataByAreaIdx(area, ((PathPoint *)pw->end)->line, ((PathPoint *)pw->end)->idx);
        if (ld != 0 && ld->type > 0x80) {
            s = ld->speed;
            mw->s.endLine = 1;
            if (s < 1.0f)
                s = 1.0f;
            if (s < mw->s.speed)
                mw->s.speed = s;
        }
    }
}
