typedef struct {
    char pad[0x380];
    int f380;
    char pad384[0x1C];
    int state;
    char pad3A4[0x64];
    int f408;
} PathWork;

int getPathStatus(PathWork *w)
{
    switch (w->state) {
    case 0:
        if (w->f380 != 0 || w->f408 != 0) {
            return 1;
        }
        break;
    case 1:
        if (w->f380 != 0) {
            return 1;
        }
        break;
    case -1:
        return 1;
    }
    return 0;
}
