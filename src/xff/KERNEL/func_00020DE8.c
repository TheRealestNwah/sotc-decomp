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
} Stream;

static void func_00020DE8(Stream *stream, int command, int arg0, int arg1)
{
again:
    stream->queue[stream->write].command = command;
    stream->queue[stream->write].args[0] = arg0;
    arg0 = 0;
    stream->queue[stream->write++].args[1] = arg1;
    arg1 = 0;
    stream->write %= 32;
    if (command == 1 && (stream->flags & 8)) {
        command = 8;
        goto again;
    }
}
