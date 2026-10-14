extern int DeleteTwoWayLink();

int DeleteSubLinkObjLink(unsigned char *p)
{
    char *c = p[8] != 0x15 ? 0 : (char *)p + 0x1C;

    return DeleteTwoWayLink(c);
}
