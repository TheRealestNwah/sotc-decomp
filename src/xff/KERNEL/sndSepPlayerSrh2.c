typedef struct { int on; int a, b, c; int *owner; short id; char pad[0x5A]; } Sep;
extern Sep B_000C2910[];

Sep *sndSepPlayerSrh2(int p, int id)
{
    Sep *r = 0;
    int i;
    for (i = 0; i < 32; i++) {
        Sep *s = &B_000C2910[i];
        if (s->on != 0 && s->id == id && s->owner != 0 && s->owner[1] == p) {
            r = s;
            break;
        }
    }
    return r;
}
