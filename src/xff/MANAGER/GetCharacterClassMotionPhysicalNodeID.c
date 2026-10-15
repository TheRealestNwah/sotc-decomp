extern int GetOptionNodePhysicalNodeId(void *, void *, int);

int GetCharacterClassMotionPhysicalNodeID(char *c, int node)
{
    int r = -1;
    char *m = *(char **)(c + 0x1C0);
    void *o = *(void **)(c + 0x358);
    if (m != 0) {
        char *n = m + 0x50;
        if (n != 0)
            r = GetOptionNodePhysicalNodeId(o, n, node);
    }
    return r;
}
