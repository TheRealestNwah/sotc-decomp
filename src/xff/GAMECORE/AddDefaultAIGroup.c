extern char B_0019B868[];
extern int isysAddGroupWithLinkParam();

int AddDefaultAIGroup(int a, int b, int c, int d)
{
    return isysAddGroupWithLinkParam(a, (int)B_0019B868, 0, 0);
}
