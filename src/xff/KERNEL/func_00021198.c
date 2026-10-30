typedef struct {
    int state;
    int unknown04;
    unsigned int flags;
    char unknown0C[0x28];
    int loop;
    char unknown38[0x1F8];
    int buffer;
    int bufferSize;
    char unknown238[8];
    int start;
    int end;
    int position;
    char unknown24C[0x88];
    int readAddress;
} Stream;
extern int Sg2ExStAdpcmIopReadAdr(Stream *, int);
extern void func_00020DE8(Stream *, int, int, int);

static void func_00021198(Stream *stream)
{
    int address;
    int size;
    int over;

    if (stream->state != 0x10)
        return;
    address = Sg2ExStAdpcmIopReadAdr(stream, 0);
    if (address == stream->readAddress)
        return;
    if (stream->readAddress < address)
        size = address - stream->readAddress;
    else
        size = stream->bufferSize - stream->readAddress;
    over = stream->position + size - stream->end;
    if (over >= 0)
        size = stream->end - stream->position;
    if (size > 0)
        func_00020DE8(stream, 1, stream->buffer + stream->readAddress, size);
    if (over >= 0) {
        if (stream->loop) {
            stream->state = 0x20;
            if (!(stream->flags & 1))
                func_00020DE8(stream, 2, stream->start, 0);
            func_00020DE8(stream, 1, stream->buffer + stream->readAddress + size, over);
        } else {
            stream->state = 0x40;
        }
    }
    stream->readAddress = stream->readAddress < address ? address : 0;
}
