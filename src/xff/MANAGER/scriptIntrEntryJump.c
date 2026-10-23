extern void isysInitGroup(void *);
extern int isysAddGroupWithLinkParam(void *, void *, int, void *);

void scriptIntrEntryJump(unsigned long *parent, void *thread, void *link)
{
    void *group = (char *)parent + 8;

    if (!((int)(*parent >> 32) & 1)) {
        isysInitGroup(group);
        *parent |= 1UL << 32;
    }
    isysAddGroupWithLinkParam(thread, group, 0, link);
}
