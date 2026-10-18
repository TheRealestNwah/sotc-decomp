extern int isysAddGroupWithLinkParam(void *, void *, int, int);
void isysAddGroupWithLinkParamNoWait(void *object, void *group, int unused, int data)
{
    isysAddGroupWithLinkParam(object, group, unused, data);
}
