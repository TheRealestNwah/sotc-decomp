void ClearSortList(void *list)
{
    int *words = list;
    int i;
    for (i = 0; i < words[1]; i++) {
        ((int *)words[0])[i] = 0;
    }
    words[4] = 0;
}
