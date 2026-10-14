void CopyCollisionEdge(void *arg0, void *arg1)
{
    (*(int *)((char *)(arg0) + 0)) = (int) (*(int *)((char *)(arg1) + 0));
    (*(int *)((char *)(arg0) + 4)) = (int) (*(int *)((char *)(arg1) + 4));
    (*(int *)((char *)(arg0) + 8)) = (int) (*(int *)((char *)(arg1) + 8));
    (*(int *)((char *)(arg0) + 0xC)) = (int) (*(int *)((char *)(arg1) + 0xC));
}
