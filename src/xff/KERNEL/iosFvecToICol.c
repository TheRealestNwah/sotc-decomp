extern void iosFTOI0Vector(int *, void *);

void iosFvecToICol(unsigned char *c, void *v)
{
    int t[4];
    iosFTOI0Vector(t, v);
    c[0] = t[0];
    c[1] = t[1];
    c[2] = t[2];
    c[3] = t[3];
}
