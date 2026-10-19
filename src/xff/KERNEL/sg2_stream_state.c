typedef struct {
    int state;
    int unknown04;
    unsigned int flags;
    char unknown0C[0x220];
    int phase;
    int start;
    int length;
} Stream;
extern void func_00020DE8(Stream *, int, int, int);
extern void func_00020FD0(Stream *);
extern void func_00021198(Stream *);
int Sg2ExStAdpcmPreLoad(Stream *stream)
{
    if (stream->state != 1)
        return -1;
    stream->state = 2;
    if (!(stream->flags & 1))
        func_00020DE8(stream, 2, 0, 0);
    func_00020DE8(stream, 1, stream->start, stream->length);
    if (stream->flags & 0x10)
        func_00020DE8(stream, 16, 0, 0);
    return 0;
}
void Sg2ExStAdpcmTickProc(Stream *stream)
{
    int previous = stream->phase;
    func_00020FD0(stream);
    func_00021198(stream);
    if (stream->phase != previous)
        func_00020FD0(stream);
}