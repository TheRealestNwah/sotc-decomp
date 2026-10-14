void windowCloseRequest(char *p)
{
    if (p != 0) {
        *(int *)(p + 0x1CC) = 1;
    }
}
