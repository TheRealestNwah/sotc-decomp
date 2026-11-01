typedef struct Link { struct Link *next; struct Link *prev; } Link;
extern int DeleteTwoWayLink(Link *);

typedef struct {
    Link link;
    int unk8;
    void (*callback)(unsigned char *, int);
    int arg;
} SubLink;

static inline SubLink *getSubLink(unsigned char *p)
{
    if (p[0x8] != 0x15) {
        return 0;
    }
    return (SubLink *)(p + 0x1C);
}

static int func_00099470(unsigned char *p)
{
    SubLink *c = getSubLink(p);

    if (c->callback) {
        c->callback(p, c->arg);
        c->callback = 0;
    }
    return DeleteTwoWayLink((Link *)getSubLink(p));
}
