typedef struct Link { struct Link *next; struct Link *prev; } Link;
extern int DeleteTwoWayLink(Link *);

int DeleteSubLinkObjLink(unsigned char *p)
{
    char *c = p[8] != 0x15 ? 0 : (char *)p + 0x1C;

    return DeleteTwoWayLink((Link *)(c));
}
