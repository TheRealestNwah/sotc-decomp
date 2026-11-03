typedef struct { char pad[0x1C]; int x1C; } Obj;
typedef struct { Obj *obj; int *len; char pad[0x1C]; } Entry;
typedef struct { Entry e[4]; int n; char pad[4]; } Table;
typedef struct { char pad[0x3C50]; int x3C50; } Game;
extern Table B_001A57E8[];
static int func_000FA7E0(Game *g, int base, int id)
{
    Table *t = &B_001A57E8[g->x3C50];
    int sum = 0;
    int i;
    if (base >= 0 && id >= 0) {
        for (i = 0; i < t->n; i++) {
            if (id == t->e[i].obj->x1C) return sum + base;
            if (t->e[i].len != 0) sum += *t->e[i].len;
        }
    }
    return -1;
}
