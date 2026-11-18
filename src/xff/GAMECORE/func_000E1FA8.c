extern void *GAMEUTIL_get_boss_obj(void);
extern char *GetLayoutClass(void *);

static void func_000E1FA8(int *n, int *ids)
{
    void *boss = GAMEUTIL_get_boss_obj();
    char *p;

    *n = 0;
    if (boss != 0) {
        p = *(char **)(GetLayoutClass(boss) + 0x1A8);
        if (p != 0 && *(int *)(p + 4) != 0) {
            ids[*n] = (int)boss;
            (*n)++;
        }
    }
}
