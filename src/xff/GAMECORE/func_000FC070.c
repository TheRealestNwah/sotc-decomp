extern void *getSubPointDataByAreaIdx(char *, int, int);
extern void setAttainmentPos(char *, void *);
extern void setUserPathMode(char *, int);

static int func_000FC070(char *w)
{
    void *sp = getSubPointDataByAreaIdx(w, *(int *)(w + 0x3C9C), *(int *)(w + 0x3C8C));

    if (sp != 0) {
        setAttainmentPos(w, sp);
        setUserPathMode(w, 0);
    }
}
