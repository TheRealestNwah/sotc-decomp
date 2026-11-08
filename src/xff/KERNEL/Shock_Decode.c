typedef struct ShockNode {
    unsigned char active;
    char pad1[0x2F];
    struct ShockNode *prev;
    struct ShockNode *next;
} ShockNode;

typedef struct {
    ShockNode *head;
    int pad4;
    void (*done)(ShockNode *, int);
    int arg;
} Shock;

typedef struct { char pad0[8]; int time; } ShockTab;

extern ShockTab *D_000408F8;
extern int func_00006E28(ShockNode *, int);
extern int func_00006B98(ShockNode *, int);

void Shock_Decode(Shock *s, unsigned char *bits_out, unsigned char *level_out)
{
    ShockNode *n;
    ShockNode *next;
    ShockNode *m;
    int level = 0;
    int bits = 0;

    if (s == 0)
        return;
    for (n = s->head; n != 0; n = n->next) {
        level += func_00006E28(n, D_000408F8->time);
        bits |= func_00006B98(n, D_000408F8->time);
    }
    if (level >= 0x100)
        level = 0xFF;
    *level_out = level;
    *bits_out = bits;
    m = s->head;
    while (m != 0) {
        if (m->active == 0) {
            if (m->prev != 0)
                m->prev->next = m->next;
            else
                s->head = m->next;
            next = m->next;
            if (next != 0) {
                next->prev = m->prev;
                next = m->next;
            }
            if (s->done != 0)
                s->done(m, s->arg);
            m = next;
        } else {
            m = m->next;
        }
    }
}
