typedef struct Grp { char pad[0x20]; struct Grp *next; } Grp;
extern Grp *D_0017A310;
extern void iosFree(void *);

void DeleteLoadAreaGroupData(Grp *g)
{
    Grp **h = &D_0017A310;
    Grp *p = *h;
    if (p == g) {
        *h = g->next;
        iosFree(g);
        return;
    }
    while (p != 0) {
        if (p->next == g) {
            p->next = g->next;
            iosFree(g);
            g = 0;
            break;
        }
        p = p->next;
    }
}
