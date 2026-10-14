extern void func_000AE858();
extern void DeleteAllTwoWayLink(void *, void *);
extern void iosMallocSetExecGarbageCallback(void *, int, int);

void FlushCollisionWorkImmediate(char *w)
{
    DeleteAllTwoWayLink(w + 0x10, func_000AE858);
    iosMallocSetExecGarbageCallback(w, -1, 0);
}
