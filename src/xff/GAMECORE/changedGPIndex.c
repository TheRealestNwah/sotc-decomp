extern char *GetLayoutClass(void *);
static int func_000FBDF8(char *, char *, int, int, char *);
static int func_000FC4B8(char *, char *, char *, int, int);

int changedGPIndex(void *a, char *w, void *c)
{
    char *l1 = GetLayoutClass(a);
    char *l2 = GetLayoutClass(c);
    int r = func_000FBDF8(w, l1, *(int *)(w + 0x3C88), *(int *)(w + 0x3C8C), l2);
    return func_000FC4B8(w, l1, l2, *(int *)(w + 0x3C90), r);
}
