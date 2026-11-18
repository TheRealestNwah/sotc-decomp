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
    char unknown24C[0x2CC - 0x24C];
    int volume;
    int volume_backup;
} Stream;

extern int (*B_000C5C00)(Stream *, int, int, int);
extern void ____VolPerBackup(Stream *, int);
extern void ____VolReflection(Stream *);
extern int Sg2ExStAdpcmPitchPercent(Stream *, int);
extern int Sg2ExStAdpcmVolumePercent(Stream *, int);
extern void func_00020E98(Stream *);

/* Parked: stream command queue pump. Control flow and switch tree match; 10 words
   differ: the original schedules `move a0` first in the paused block, so the
   assembler fills the preceding beqz delay slot with it. */
#ifdef NONMATCHING
static void func_00020FD0(Stream *stream)
{
    int done = 0;
    int paused = stream->state & 0x8000;
    int ret;
    int state;

    do {
        if (stream->read != stream->write) {
            ret = B_000C5C00(stream, stream->queue[stream->read].command,
                             stream->queue[stream->read].args[0],
                             stream->queue[stream->read].args[1]);
            if (ret >= 0) {
                switch (stream->queue[stream->read].command) {
                case 2:
                    ret = 0;
                    break;
                case 3:
                    ret = 1;
                    break;
                case 1:
                    stream->position += stream->queue[stream->read].args[1];
                    break;
                }
                if (paused) {
                    unsigned int st = stream->state;
                    ____VolPerBackup(stream, 0);
                    st &= ~0x8000;
                    ____VolReflection(stream);
                    Sg2ExStAdpcmPitchPercent(stream, stream->volume_backup);
                    stream->state = st;
                }
                func_00020E98(stream);
                stream->queue[stream->read].command = 0;
                stream->read = (stream->read + 1) % 32;
            } else {
                if (ret == -1 && !paused) {
                    ____VolPerBackup(stream, 1);
                    stream->volume_backup = stream->volume;
                    Sg2ExStAdpcmVolumePercent(stream, 0);
                    Sg2ExStAdpcmPitchPercent(stream, 0);
                    stream->state |= 0x8000;
                }
                done = 1;
            }
        } else {
            done = 1;
        }
    } while (!done);
}
#endif
