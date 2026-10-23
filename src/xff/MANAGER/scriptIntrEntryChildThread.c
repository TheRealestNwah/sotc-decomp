extern void isysInitGroup(void *);
extern int isysAddGroupWithLinkParam(void *, void *, int, void *);

void scriptIntrEntryChildThread(unsigned long *parent, void *thread,
                               char *link, void *parameter)
{
    void *group = (char *)parent + 0x10;

    if (!((int)(*parent >> 33) & 1)) {
        isysInitGroup(group);
        *parent |= 1UL << 33;
    }
    *(void **)(link + 8) = parameter;
    *(void **)(link + 0x10) = thread;
    isysAddGroupWithLinkParam(thread, group, 0, link);
}
