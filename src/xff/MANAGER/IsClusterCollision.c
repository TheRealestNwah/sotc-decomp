int IsClusterCollision(void *arg0)
{
    return (*(int *)((char *)(arg0) + 4)) >= 2;
}
