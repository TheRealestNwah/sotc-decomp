extern void *isysGetThisSubThread(void);
extern void func_00095428(void *);

void scrRunM(int n)
{
    void *t = isysGetThisSubThread();
    int i;
    for (i = 0; i < n; i++)
        func_00095428(t);
}
