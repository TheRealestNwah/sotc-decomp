extern void isysDeleteGroupWithLinkParam(int, void *, int, int);

void scriptIntrDeleteChildThread(unsigned long *s, int a, int c)
{
    if ((int)(*s >> 33) & 1) {
        isysDeleteGroupWithLinkParam(a, (char *)s + 0x10, c, 0);
    }
}
