typedef struct { int on; int a, b, c; int *owner; short id, id2; char pad[0x58]; } Sep;
extern Sep B_000C2910[];

Sep *sndSepPlayerSrh(int p, int id, int id2)
{
    Sep *r = 0;
    int i;
    for (i = 0; i < 32; i++) {
        Sep *s = &B_000C2910[i];
        if (s->on != 0 && s->id == id && s->id2 == id2 && s->owner != 0 && s->owner[1] == p) {
            r = s;
            break;
        }
    }
    return r;
}

