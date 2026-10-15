extern void *createScriptObj(void *, void *, int, int, int, int, int, int);

void *gcCreateScriptObj(void *a, void *b, int c, int d, int e, int f)
{
    return createScriptObj(a, b, c, d, e, f, 0, 0);
}
