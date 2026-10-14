void RelocateTwoWayLinkHeader(char **p)
{
    char **n = (char **)p[1];

    if (n != 0) {
        n[0] = (char *)p;
    }
}
