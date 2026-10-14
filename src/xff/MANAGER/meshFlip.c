void meshFlip(unsigned char *p)
{
    char *c = p[8] != 0x23 ? 0 : (char *)p + 0x20;

    *(int *)(c + 0x10) = *(int *)(c + 0x10) == 0;
}
