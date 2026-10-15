typedef struct Ctl { char *win; char pad[0xC4]; struct Ctl *next; } Ctl;
extern void iosFree(void *);

void windowDeleteControl(Ctl *c)
{
    Ctl *p = *(Ctl **)(c->win + 0x3E4);
    if (p != 0) {
        while (p->next != c) {
            p = p->next;
            if (p == 0)
                goto end;
        }
        p->next = c->next;
    }
end:
    iosFree(c);
}
