extern void isysDeleteGroupWithLinkParam(int, void *, int, int);

void scriptIntrDeleteJump(char *s, int a, int c)
{
    if (*(int *)(s + 4) & 1)
        isysDeleteGroupWithLinkParam(a, s + 8, c, 0);
}
