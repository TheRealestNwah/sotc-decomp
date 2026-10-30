typedef struct {
    int command;
    int args[2];
} StreamCommand;

typedef struct {
    int state;
    int unknown04;
    unsigned int flags;
    char unknown0C[0x9C];
    StreamCommand queue[32];
    int read;
    int write;
    char unknown230[0x10];
    int start;
    char unknown244[4];
    int position;
} Stream;
extern int Sg2ExStAdpcmStop(Stream *);
extern int Sg2ExStAdpcmPlay(Stream *);
extern void func_00020DE8(Stream *, int, int, int);

static inline void play(Stream *stream)
{
    Sg2ExStAdpcmPlay(stream);
}

static void func_00020E98(Stream *stream)
{
    int ready;
    int status;

    switch (stream->state & ~0x8000) {
    case 0x10:
        break;
    case 0x40:
        Sg2ExStAdpcmStop(stream);
        if (!(stream->flags & 2)) {
            func_00020DE8(stream, 4, 0, 0);
            stream->flags |= 2;
        }
        break;
    case 0x20:
        stream->state = 0x10;
        stream->position = stream->start;
        break;
    case 2:
        status = stream->queue[stream->read].command;
        ready = 0;
        if (stream->flags & 0x10) {
            if (status == 0x10)
                ready = 1;
        } else if (stream->flags & 8) {
            if (status == 8)
                ready = 1;
        } else {
            ready = status == 1;
        }
        if (ready) {
            stream->state = 8;
            if (stream->flags & 4)
                play(stream);
        }
        break;
    }
}
