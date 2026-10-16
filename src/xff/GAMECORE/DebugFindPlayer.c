extern int *isysGroupForFirst(void *, int);
extern int *isysGroupForNext(int *, int);
extern void isysGroupForExit(void *, int);
extern int GAMEUTIL_is_player_obj(void *);

void *DebugFindPlayer(void *group)
{
    void *found = 0;
    void *o = 0;
    int *g;

    for (g = isysGroupForFirst(group, 0); g != 0; g = isysGroupForNext(g, 0)) {
        o = (void *)*g;
        if (GAMEUTIL_is_player_obj(o) == 1) {
            found = o;
            break;
        }
    }
    if (o != 0)
        isysGroupForExit(o, 0);
    return found;
}
