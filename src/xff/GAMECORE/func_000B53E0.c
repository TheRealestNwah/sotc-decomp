typedef struct Slot {
    int i0;
    int i4;
    int i8;
    int iC;
    int i10;
    char pad14[0x3C];
    short s50;
    short s52;
    int i54;
    struct Slot *next;
    int pad5C;
} Slot;

typedef struct {
    Slot *first;
    Slot *last;
    int count;
} List;

extern float RO_001800A0;

#ifdef NONMATCHING /* 52 diffs, same size (was 75): Slot is 0x60 bytes (pad after next), the RO_001800A0 load is hoisted into a local, and the first loop counts down a separate counter so a1 stays live in t5 like the Original. Left: register numbering (the Original has c in t2 and list in t1, and the loop temporaries in the reverse order); declaration order does not move it. */
static void func_000B53E0(char *c, int a1, int a2)
{
    List *list = (List *)(c + 0x244);
    int *b = (int *)(c + 0x238);
    int off;
    int n;
    int *p;
    Slot *s;
    int i;
    int k;
    float f;
    char *b4 = c + 4, *b8 = c + 8, *bC = c + 0xC, *b10 = c + 0x10;

    *(int *)(c + 0x244) = 0;
    list->last = 0;
    list->count = 0;
    b[2] = 0;
    *(int *)(c + 0x238) = 0;
    b[1] = 0;
    *(int *)c = 0;
    p = (int *)(c + 0x14);
    off = 0;
    n = 9;
    f = RO_001800A0;
    do {
        *(int *)(b4 + off) = -1;
        *(int *)(b8 + off) = -1;
        *(float *)(bC + off) = f;
        *(int *)(b10 + off) = 0;
        n--;
        off += 0x1C;
        p[0] = 0;
        p[1] = 0;
        p[2] = 0;
        p += 7;
    } while (n >= 0);
    *(int *)(c + 0x9D4) = a2;
    *(int *)(c + 0x9D0) = a1;
    if (a1 > 0) {
        s = (Slot *)(c + 0x250);
        k = a1;
        do {
            if (s != 0) {
                Slot *t = (Slot *)list->count;

                if (t != 0)
                    t->next = s;
                else
                    list->last = s;
                s->next = 0;
                list->count = (int)s;
                *(int *)(c + 0x244) = *(int *)(c + 0x244) + 1;
            }
            k--;
            s->i0 = 0;
            s->i4 = 0;
            s->i8 = 0;
            s->iC = -1;
            s->i10 = 0;
            s->i54 = 0;
            s->s50 = -1;
            s->s52 = -1;
            s++;
        } while (k != 0);
    }
    i = a1;
    if (i < 0x14) {
        s = (Slot *)(c + 0x250) + i;
        do {
            i++;
            s->i0 = 0;
            s->i4 = 0;
            s->i8 = 0;
            s->iC = -1;
            s->i10 = 0;
            s->i54 = 0;
            s->s50 = -1;
            s->s52 = -1;
            s++;
        } while (i < 0x14);
    }
}
#endif
