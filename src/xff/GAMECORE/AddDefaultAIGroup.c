extern char B_0019B868[];
extern int isysAddGroupWithLinkParam(void *, void *, int, int);

int AddDefaultAIGroup(int a, int b, int c, int d)
{
    return isysAddGroupWithLinkParam((void *)a, B_0019B868, 0, 0);
}
