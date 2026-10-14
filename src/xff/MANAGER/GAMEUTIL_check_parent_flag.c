extern char *GetLayoutClass(void *);

int GAMEUTIL_check_parent_flag(void *actor)
{
    char *l = GetLayoutClass(actor);
    if (l == 0)
        goto no;
    if (*(int *)(l + 0x124) == 0)
        goto no;
    return 1;
no:
    return 0;
}
