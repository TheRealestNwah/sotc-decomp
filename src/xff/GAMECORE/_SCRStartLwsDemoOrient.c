extern void *StartLwsDemoManager(int, int, int);
extern void isysAddGroupWithLinkParam(void *, void *, int, int);

void *_SCRStartLwsDemoOrient(void *g, int a, int b, int c)
{
    void *o = StartLwsDemoManager(a, b, c);
    isysAddGroupWithLinkParam(o, g, 0, 0);
    return o;
}
