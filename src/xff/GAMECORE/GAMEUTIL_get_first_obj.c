extern int *isysGroupForFirst(void *, int);

extern void isysGroupForExit(void *, int);

void *GAMEUTIL_get_first_obj(void *group)
{
    void *found = 0;
    void *o = 0;
    int *g;

    for (g = isysGroupForFirst(group, 0); g != 0; ) {
        o = (void *)*g;
        found = o;
        break;
    }
    if (o != 0)
        isysGroupForExit(o, 0);
    return found;
}

