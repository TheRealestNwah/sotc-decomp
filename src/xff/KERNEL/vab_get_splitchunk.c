char *vab_get_splitchunk(char *p)
{
    if (p != 0) {
        return p + 8;
    }
    return 0;
}
