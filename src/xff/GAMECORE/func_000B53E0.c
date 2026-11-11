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
} Slot;

typedef struct {
    Slot *first;
    Slot *last;
    int count;
} List;

extern float RO_001800A0;

#ifdef NONMATCHING /* 79 diffs: the original keeps the first ten-entry loop as separate base+index streams (c+4+off, c+8+off, c+0xC+off, c+0x10+off) instead of one strength-reduced pointer */
static void func_000B53E0(char *c, int a1, int a2)
{
    List *list = (List *)(c + 0x244);
    int *b = (int *)(c + 0x238);
    int off;
    int n;
    int *p;
    Slot *s;
    int i;

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
    do {
        *(int *)(c + 4 + off) = -1;
        *(int *)(c + 8 + off) = -1;
        *(float *)(c + 0xC + off) = RO_001800A0;
        *(int *)(c + 0x10 + off) = 0;
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
        i = a1;
        do {
            if (s != 0) {
                Slot *t = (Slot *)list->count;

                if (t == 0)
                    list->last = s;
                else
                    t->next = s;
                s->next = 0;
                list->count = (int)s;
                *(int *)(c + 0x244) = *(int *)(c + 0x244) + 1;
            }
            i--;
            s->i0 = 0;
            s->i4 = 0;
            s->i8 = 0;
            s->iC = -1;
            s->i10 = 0;
            s->i54 = 0;
            s->s50 = -1;
            s->s52 = -1;
            s++;
        } while (i != 0);
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
