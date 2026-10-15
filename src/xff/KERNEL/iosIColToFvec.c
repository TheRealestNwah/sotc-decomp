extern void iosITOF0Vector(void *, int *);

void iosIColToFvec(void *v, unsigned int c)
{
    int t[4];
    t[0] = c & 0xFF;
    t[1] = (c >> 8) & 0xFF;
    t[2] = (c >> 16) & 0xFF;
    t[3] = c >> 24;
    iosITOF0Vector(v, t);
}
