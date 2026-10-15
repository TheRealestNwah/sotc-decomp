typedef struct { int status; int a, b; } Keybd;
extern Keybd B_0014DC70[];

int usbdevKeybdGetStatus(int i, int mask, int mod)
{
    int r = 0;
    if (B_0014DC70[i].status & mask) {
        int m = ((int *)B_0014DC70)[-1];
        r = (m & mod) == m;
    }
    return r;
}
