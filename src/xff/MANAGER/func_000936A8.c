/* ~20 diffs (mostly shifted branch offsets), same size. Static (alabel) fade-item target update: for each 0x44-byte item and its 0x1C-byte entries, when the entry's target is live and the item's cfg word (+0x38) mode matches the object's ids and the group cursor, a ready target gets state 3 + flag, otherwise state 1 without the flag. Item pointer reloaded per iteration (volatile items), target shares the Item layout so the stores alias. Remaining: gcc picks t2/t3/t4 for the three mask constants and the counter differently, and orders the final and/or/sw slightly differently. */
typedef struct { int pad0[4]; int flags; int f14; int f18; } Obj2;
typedef struct { unsigned lo : 9; unsigned mode : 2; int f1 : 10; int f2 : 10; unsigned top : 1; } CfgBits;
struct Item;
typedef struct { Obj2 *o; struct Item *t; char pad[0x14]; } Ent;
typedef struct Item {
    int has;
    Ent *ents;
    unsigned pad8 : 4;
    unsigned cnt : 10;
    unsigned rest : 13;
    unsigned st : 4;
    unsigned fl : 1;
    int c;
    char pad10[0x34 - 0x10];
    int pad34;
    CfgBits cfg;
    char pad3C[0x44 - 0x3C];
} Item;
typedef struct { int pad0; Item *volatile items; int count; int cur; } Group;

#ifdef NONMATCHING
static void func_000936A8(Group *g)
{
    int i;
    for (i = 0; i < g->count; i++) {
        Item *it = (Item *)((char *)g->items + i * 0x44);
        struct { int pad; CfgBits b; } *c = (void *)&it->pad34;
        int j;
        for (j = 0; j < it->cnt; j++) {
            Ent *e = (Ent *)((char *)it->ents + j * 0x1C);
            Obj2 *o = e->o;
            Item *t = e->t;
            if (t == 0 || !(o->flags & 2)) {
                continue;
            }
            if ((*(int *)&c->b & 0x600) == 0) {
                if (c->b.f1 == o->f14 && o->f18 == -1 && i == g->cur) {
                    if (t->has != 0 && t->st == 0) {
                        t->c = 0;
                        t->st = 3;
                        t->fl = 1;
                    }
                } else {
                    t->st = 1;
                    t->fl = 0;
                }
            } else if ((*(int *)&c->b & 0x600) == 0x200) {
                if (c->b.f1 == o->f14 && c->b.f2 == o->f18 && i == g->cur) {
                    if (t->has != 0 && t->st == 0) {
                        t->c = 0;
                        t->st = 3;
                        t->fl = 1;
                    }
                } else {
                    t->st = 1;
                    t->fl = 0;
                }
            }
        }
    }
}
#endif
