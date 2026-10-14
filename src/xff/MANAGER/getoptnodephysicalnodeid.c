extern int GetOptionNodePhysicalNodeId(void *, void *, int);
int getoptnodephysicalnodeid(void *a, void *b, char *c, int d)
{
    int r = -1;
    if (c != 0) {
        char *n = c + 0x50;
        if (n != 0)
            r = GetOptionNodePhysicalNodeId(b, n, d);
    }
    return r;
}
