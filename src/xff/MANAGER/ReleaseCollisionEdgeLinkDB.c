#define NULL ((void *)0)
extern void iosFree(void *);

void ReleaseCollisionEdgeLinkDB(void **arg0)
{
    void *temp_s0;

    temp_s0 = *arg0;
    if (temp_s0 != NULL) {
        iosFree((*(void **)((char *)(temp_s0) + 0x24)));
        iosFree(temp_s0);
        *arg0 = NULL;
    }
}
