extern int getPathColiGroupByType(int);
extern int func_000FAEC8(void *);
extern int pathJudgeFunc();
extern int func_000FACB0(void *, void *, void *, int, int, int (*)());

static int func_000FAD10(char *w, void *from, void *to)
{
    char buf[0x50];
    int g = getPathColiGroupByType(*(int *)(w + 0x3C50));

    return func_000FACB0(buf, from, to, g, func_000FAEC8(w), pathJudgeFunc);
}
