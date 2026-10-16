extern void CallMotShiftCallBackElemEntryFunc(char *, char *, void *);

void callEntryFunc(char *a, void *b, char *c)
{
    void (**f)(void *) = (void (**)(void *))(c + 0x94);
    int i;

    for (i = 0; i < 5; i++, f++) {
        if (*f != 0)
            (*f)(b);
    }
    CallMotShiftCallBackElemEntryFunc(a + 0x2C8, c, b);
}
