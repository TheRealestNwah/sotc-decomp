int Kite_CmpPathPoint(char *a, char *b)
{
    if (*(int *)(a + 0x18) != *(int *)(b + 0x18)) {
        goto no;
    }
    if (*(int *)(a + 0x10) != *(int *)(b + 0x10)) {
        goto no;
    }
    return 1;
no:
    return 0;
}
