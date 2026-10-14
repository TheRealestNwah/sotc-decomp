extern void *GetLayoutClass(void *);
extern int func_000FBF38(void *, void *, int, int);
int changedAPIndex(void *actor, char *work)
{
    return *(int *)(work + 0x3C98) != func_000FBF38(work, GetLayoutClass(actor), *(int *)(work + 0x3C90), *(int *)(work + 0x3C8C));
}
