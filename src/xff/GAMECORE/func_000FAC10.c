extern int getPathColiGroupByType(int);
extern int func_000FAEC8(void *);
extern int pathJudgeFunc();
extern int func_000FACB0(void *, void *, void *, int, int, int (*)());
extern int widePathCollisionDirect(void *, void *, void *, float, int, int, int);

static int func_000FAC10(char *w, void *from, void *to)
{
    char buf[0x50];

    if (*(int *)(w + 0xF4) == 0) {
        int g = getPathColiGroupByType(*(int *)(w + 0x3C50));

        return func_000FACB0(buf, from, to, g, func_000FAEC8(w), pathJudgeFunc);
    }
    return widePathCollisionDirect(w, from, to, *(float *)(w + 0x3C3C), *(int *)(w + 0x3C40), *(int *)(w + 0xF0), 0) != 0;
}
